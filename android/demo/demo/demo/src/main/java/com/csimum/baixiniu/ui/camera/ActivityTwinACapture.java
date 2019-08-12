package com.csimum.baixiniu.ui.camera;

import android.net.Uri;
import android.os.Bundle;
import android.util.JsonReader;
import android.view.View;

import com.csimum.baixiniu.R;
import com.csimum.baixiniu.ui.camera.eventcallback.ICameraLowBatteryEventCallback;
import com.csimum.baixiniu.ui.camera.eventcallback.ICameraTFSpaceChange;
import com.detu.dispatch.camera.CameraManager;
import com.detu.dispatch.camera.ICamera;
import com.detu.dispatch.camera.Twins360_ACamera;
import com.detu.dispatch.dispatcher.DispatcherException;
import com.detu.dispatch.dispatcher.MainDispatcher;
import com.detu.dispatch.dispatcher.NotificationListener;
import com.detu.dispatch.dispatcher.OnPreparedListener;
import com.detu.dispatch.dispatcher.RequestBuilder;
import com.detu.dispatch.dispatcher.entity.BaseEntity;
import com.detu.dispatch.network.NetControl;
import com.detu.module.libs.LogUtil;
import com.detu.module.net.player.FileInfo;
import com.detu.module.net.player.PlaySourceInfo;
import com.detu.module.net.player.PlayerData;
import com.detu.module.ui.adapter.AdapterItemClickListener;
import com.detu.module.ui.adapter.AdapterItemLongClickListener;
import com.detu.playerui.PlayerListenerImpl;
import com.detu.remux.DeviceId;
import com.detu.remux.IVideoStitchListener;
import com.detu.remux.RetCode;
import com.player.panoplayer.GLGesture;
import com.player.panoplayer.enitity.PanoOptionKey;
import com.player.panoplayer.enitity.PanoPlayerOption;
import com.player.panoplayer.enitity.PanoPlayerOptionType;

import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

import io.reactivex.functions.Action;
import io.reactivex.functions.Consumer;

import static com.detu.dispatch.dispatcher.DispatcherError.ErrorEnum.ANOTHER_CAMERA_CONNECTED;

/**
 * Created by five on 2018/3/27.
 * <p>
 * 项目创建入口
 */

public class ActivityTwinACapture extends ActivityCaptureBase implements PlayerListenerImpl.WorkPlayerListener, PlayerListenerImpl.CalibrationCreateCallback, View.OnClickListener,  DownloadPicCallback, IVideoStitchListener, GLGesture.ClickPanoViewListener, ICameraLowBatteryEventCallback, NotificationListener, ICameraTFSpaceChange {
    private static final String TAG = "ActivityTwinACapture";

    @Override
    protected void baseCameraOnResume() {
        MainDispatcher.getInstance().registerNotificationListener(this);
        //5分钟检测一次电量状态
        restartTimerTask();
    }

    @Override
    protected void baseCameraOnPause() {
        cancelTimerTask();
    }


    private int tryConnectCount = 0;
    private boolean maxTryConnectCount = false;

    @Override
    public void initCameraSocket(final boolean interruptFinish) {
        MainDispatcher.getInstance().registerHandler(cameraInfoHandler);
        if (!MainDispatcher.getInstance().isCameraConnected()) {
            LogUtil.i(TAG, "initCameraSocket()--> 相机未连接");
            tryConnectCount = 0;
            cameraSocketInit = false;
            tipConnectCamera();
            return;
        }
        LogUtil.i(TAG, "initCameraSocket()--> tryCount " + tryConnectCount);
        playerMode = null;
        MainDispatcher.getInstance().prepare(new OnPreparedListener() {
            @Override
            public void onPrepared() {
                LogUtil.i(TAG, "onPrepared() ");
                MainDispatcher.getInstance().previewWillAppear().doOnSuccess(new Consumer<BaseEntity>() {
                    @Override
                    public void accept(BaseEntity baseEntity) throws Exception {
                        LogUtil.i(TAG, "previewWillAppear()-->doOnSuccess() ");
                        tryConnectCount = 0;
                        cameraSocketInit = true;
                        MainDispatcher.getInstance().getCalibration().doFinally(new Action() {
                            @Override
                            public void run() throws Exception {
                                initPlay();
                            }
                        }).submit().previewWillAppear().submit();

                    }
                }).doOnError(new RequestBuilder.ErrorCallback() {
                    @Override
                    public void onError(DispatcherException dispatcherException) {
                        LogUtil.i(TAG, "previewWillAppear()-->onError() ");
                        cameraSocketInit = false;
                        tryConnectCamera(dispatcherException);
                    }
                }).submit();
            }

            @Override
            public void onPrepareFailed(DispatcherException dispatcherException) {
                LogUtil.i(TAG, "onPrepareFailed() ");
                cameraSocketInit = false;
                tryConnectCamera(dispatcherException);
            }
        });
    }

    /**
     * 尝试重新连接相机
     *
     * @param dispatcherException 异常信息
     */
    @Override
    protected void tryConnectCamera(DispatcherException dispatcherException) {
        LogUtil.i(TAG, "tryConnectCamera()--> tryCount " + tryConnectCount);
        tryConnectCount++;
        maxTryConnectCount = tryConnectCount == 3;
        if (dispatcherException != null && dispatcherException.getEntity() != null && ANOTHER_CAMERA_CONNECTED == dispatcherException.getEntity().errorEnum) {
            LogUtil.i(TAG, "previewWillAppear()-->onError() 请先断开其他相机连接 ");
            toast(R.string.camera_connect_disconnect_others);
            finish();
        } else {
            if (maxTryConnectCount) {
                if (dispatcherException != null) {
                    LogUtil.i(TAG, "previewWillAppear()-->onError() " + dispatcherException.getMessage());
                    toast(dispatcherException.getMessage());
                } else {
                    toast(R.string.camera_connect_error);
                }
                finish();
            } else {
                uiHandler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        initCameraSocket(true);
                    }
                }, 2000);
            }
        }
    }


    /**
     * 开始播放预览
     */
    @Override
    protected void startPlayerLive() {
        ICamera cameraConnected = CameraManager.isCameraDeviceBySSID(NetControl.getInstance().getSSID());
        if (cameraConnected != null && cameraConnected instanceof Twins360_ACamera) {
            ICamera camera = MainDispatcher.getInstance().getmCamera();
            String PLAYER_CONFIG =
                    "<DetuVr>\n" +
                            "   <settings init='pano1' initmode='default' enablevr='false' title=''/>\n" +
                            "   <scenes>\n" +
                            "       <scene name='pano1' title='' thumburl=''>\n" +
                            "           <preview url='' />\n" +
                            "           <image type='video' url='%s' device='%s'/>\n" +
                            "           <view viewmode='default'  hlookat ='180'/>\n" +
                            "       </scene>\n" +
                            "   </scenes>\n" +
                            "</DetuVr>";
            String previewUrl = camera.getPreviewUrl();
            Uri uri = Uri.parse(previewUrl);
            String ip = uri.getHost();
            LogUtil.i(TAG, "相机ip地址: " + ip);
            if (!"0.0.0.0".equals(ip)) {
                String xml = String.format(Locale.ENGLISH, PLAYER_CONFIG, previewUrl, camera.getPlayImageDevice());
                PlaySourceInfo playSourceInfo = new PlaySourceInfo();
                playSourceInfo.setSource(PlayerData.DataSource.Camera);
                playSourceInfo.setXmlContent(xml);
                LogUtil.i(TAG, "playPreview - xml :" + xml);
                playerListenerImpl.setGestureEnable(true);
                playerListenerImpl.startPlayWork(playSourceInfo);
                //新添加
                PanoPlayerOption optionTransPort = new PanoPlayerOption(PanoPlayerOptionType.OPT_CATEGORY_FORMAT, PanoOptionKey.RTSP_TRANSPORT, "tcp");
                playerListenerImpl.addOptionValue(optionTransPort);
                LogUtil.i(TAG, "playerListenerImpl startPlayWork");
            } else {
                LogUtil.i(TAG, "相机ip地址获取失败 !!!");
                if (camera.getDeviceIndex() == Twins360_ACamera.get().getDeviceIndex()) {
                    LogUtil.i(TAG, "当前是Twin相机付默认值 : 192.168.42.1 !!!");
                }
                initCameraSocket(false);
            }
        } else {
//            DialogProjectMessage dialogProjectMessage = new DialogProjectMessage(this);
//            dialogProjectMessage.updateMessage("请连接Twin相机");
//            dialogProjectMessage.setCanceledOnTouchOutside(true);
        }

    }


    @Override
    public void onPlayLoading() {
        super.onPlayLoading();
        LogUtil.i(TAG, "onPlayLoading()");
        btnCapture.setEnabled(false);
    }



    /**
     * 拍照完成
     */
    @Override
    protected void onCaptureSuccess() {
        String photoPathJson = MainDispatcher.getInstance().getCameraInfo().getPhotoPath();
        try {
            JsonReader reader = new JsonReader(new StringReader(photoPathJson));
            List<String> paths = new ArrayList<>();
            reader.beginArray();
            while (reader.hasNext()) {
                paths.add(reader.nextString());
            }
            reader.endArray();
            String photoDownloadUrl = paths.get(0);
            String savePath = generateSavePathDownload(photoDownloadUrl);
            FileInfo fileInfo = new FileInfo();
            fileInfo.setFilePath(savePath);
            Bundle bundle = new Bundle();
            bundle.putString("downloadUrl", photoDownloadUrl);
            fileInfo.setBundle(bundle);
            showProgress(R.string.downloading);
            new DownloadPicTask().setDownloadF4PicCallback(this).execute(fileInfo);
        } catch (IOException e) {
            e.printStackTrace();
            btnCapture.setEnabled(true);
        }
    }

    private String covertPhotoPath;

    @Override
    public void onDownloadFinish(int downloadState, ArrayList<FileInfo> downloadPath) {
        if (downloadState == STATE_SUCCESS) {
            FileInfo fileInfo = downloadPath.get(0);
            LogUtil.i(this, "文件下载完成:" + fileInfo.getFilePath());
            toast(R.string.downloadSuccess);
            covertPhotoPath = generateSavePathCovert(fileInfo.getFilePath());
            DownloadPicTask.covertPhoto(fileInfo.getFilePath(), covertPhotoPath, DeviceId.TWO_FISHEYE, this);
        } else {
            toast(R.string.downloadError);
            hideProgress();
            btnCapture.setEnabled(true);
        }

    }


    @Override
    public void onVideoStitchProgressChanged(int i) {

    }

    @Override
    public void onVideoStitchStateChanged(RetCode retCode) {
        hideProgress();
        if (retCode == RetCode.OK) {
            toast("转码成功");
            LogUtil.i(this, "文件地址:" + covertPhotoPath);
            insertImageToProject(covertPhotoPath);
        } else {
            toast("转码失败");
        }
        btnCapture.setEnabled(true);
        setProjectHasEdited();

    }
}
