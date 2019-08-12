package com.csimum.baixiniu.ui.camera;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.ColorStateList;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Typeface;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.text.Html;
import android.text.TextUtils;
import android.util.JsonReader;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import com.csimum.baixiniu.R;
import com.csimum.baixiniu.app.BxnConst;
import com.csimum.baixiniu.ui.camera.eventcallback.ICameraLowBatteryEventCallback;
import com.csimum.baixiniu.ui.camera.eventcallback.ICameraTFSpaceChange;

import com.csimum.baixiniu.ui.widget.HeaderAndFooterWrapper;
import com.csimum.baixiniu.util.NetworkUtils;
import com.detu.android_panoplayer.PanoPlayerImpl;
import com.detu.android_panoplayer.renderer.PanoPlayerSurfaceView;
import com.detu.dispatch.camera.ICamera;
import com.detu.dispatch.dispatcher.CameraInfo;
import com.detu.dispatch.dispatcher.DispatcherError;
import com.detu.dispatch.dispatcher.DispatcherException;
import com.detu.dispatch.dispatcher.MainDispatcher;
import com.detu.dispatch.dispatcher.NotificationListener;
import com.detu.dispatch.dispatcher.NotificationType;
import com.detu.dispatch.dispatcher.RequestBuilder;
import com.detu.dispatch.dispatcher.entity.BaseEntity;
import com.detu.dispatch.network.NetControl;
import com.detu.getmaskandweight.FileReadandWrite;
import com.detu.getmaskandweight.GetWeightAndMaskHelper;
import com.detu.module.app.ActivityWithTitleBar;
import com.detu.module.app.Constants;
import com.detu.module.libs.DTUtils;
import com.detu.module.libs.FileUtil;
import com.detu.module.libs.HtmlTagHandler;
import com.detu.module.libs.LogUtil;
import com.detu.module.net.player.FileInfo;
import com.detu.module.permission.DPermission;
import com.detu.module.permission.DTPermissionDialog;
import com.detu.module.ui.adapter.AdapterItemClickListener;
import com.detu.module.ui.adapter.AdapterItemLongClickListener;
import com.detu.module.ui.adapter.ViewHolderBase;
import com.detu.module.ui.divider.VerticalDividerItemDecoration;
import com.detu.module.widget.DTMenuItem;
import com.detu.playerui.PlayerListenerImpl;
import com.detu.playerui.pano.WorkSceneInfo;
import com.detu.remux.DeviceId;
import com.detu.remux.IVideoStitchListener;
import com.detu.remux.RetCode;
import com.player.panoplayer.GLGesture;
import com.player.panoplayer.enitity.PanoData;
import com.player.panoplayer.enitity.PanoDeviceId;
import com.player.panoplayer.enitity.PanoNodeImage;
import com.player.panoplayer.enitity.PanoNodeView;
import com.player.panoplayer.enitity.PanoOptionKey;
import com.player.panoplayer.enitity.PanoPlayerOption;
import com.player.panoplayer.enitity.PanoPlayerOptionType;
import com.player.panoplayer.enitity.PanoResourceType;
import com.player.panoplayer.enitity.PanoViewMode;

import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import io.reactivex.annotations.NonNull;
import io.reactivex.functions.Consumer;
import pl.droidsonroids.gif.GifDrawable;
import pl.droidsonroids.gif.GifImageView;

/**
 * Created by five on 2018/3/27.
 * <p>
 * 项目创建入口
 */

public abstract class ActivityCaptureBase extends ActivityWithTitleBar implements PlayerListenerImpl.WorkPlayerListener, PlayerListenerImpl.CalibrationCreateCallback, View.OnClickListener, DownloadPicCallback, IVideoStitchListener, GLGesture.ClickPanoViewListener, ICameraLowBatteryEventCallback, NotificationListener, ICameraTFSpaceChange {
    private static final String TAG = "ActivityCaptureBase";

    protected PanoPlayerSurfaceView playerSurfaceView;
    protected PanoPlayerImpl panoPlayer;
    protected PlayerListenerImpl playerListenerImpl;
    protected ImageButton btnCapture;
    private GifImageView loadingView;

    private GifDrawable animationDrawable;

    protected DispatcherInfoHandler cameraInfoHandler = new DispatcherInfoHandler();
    protected Handler uiHandler = new Handler(Looper.getMainLooper());
    protected Handler childHandler;
    protected HandlerThread handlerThreadChild;
    private int indexChecked = 0;
    //是否编辑过
    private boolean isProjectHasEdited = false;
    //相机是否初始化
    protected boolean cameraSocketInit = false;
    protected PlayerMode playerMode;
    //sdcard是否移除
    private boolean isSdcardRemove = false;



    @Override
    public View getViewContent(LayoutInflater layoutInflater, ViewGroup viewGroup, boolean b) {
        return layoutInflater.inflate(R.layout.activity_project_capture, viewGroup, b);
    }

    @Override
    public void initViews() {
        keepScreenOn();
        handlerThreadChild = new HandlerThread("CaptureTaskChild");
        handlerThreadChild.start();
        childHandler = new Handler(handlerThreadChild.getLooper());
        curNetState = getNetState();
        registerBroadcastReceiver(new String[]{WifiManager.NETWORK_STATE_CHANGED_ACTION, WifiManager.WIFI_STATE_CHANGED_ACTION});
        getBackMemuItem().setImageResource(R.mipmap.public_back_black);
        getTitleMenuItem().getLabelView().setTypeface(Typeface.DEFAULT_BOLD);
        setTitle(R.string.project_photo);

        //菜单项

        loadingView = findViewById(R.id.iv_loading);
        animationDrawable = (GifDrawable) loadingView.getDrawable();
        btnCapture = findViewById(R.id.btnCapture);
        //重拍
        View reTakePhoto = findViewById(R.id.reAction);
        reTakePhoto.setOnClickListener(this);

        btnCapture.setOnClickListener(this);
        playerSurfaceView = findViewById(R.id.player_view);
        cameraInfoHandler.setCameraLowBatteryEventCallback(this);
        cameraInfoHandler.setCameraTFSpaceChange(this);
        initPlayerImpl();

        if(DPermission.isGranted(this,DPermission.PERMISSION_STORAGE)){
            if (PlayerMode.PlayBack == playerMode) {
                initPlay();
            } else {
                initCameraSocket(true);
            }
        }else{
            DPermission.requestPermission(this,DPermission.PERMISSION_STORAGE,0);

        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @android.support.annotation.NonNull String[] permissions, @android.support.annotation.NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if(DPermission.isGranted(this,DPermission.PERMISSION_STORAGE)){
            if (PlayerMode.PlayBack == playerMode) {
                initPlay();
            } else {
                initCameraSocket(true);
            }
        }else{
            DPermission.requestPermission(this,DPermission.PERMISSION_STORAGE,0);

        }
    }

    protected void baseCameraOnResume() {

    }

    protected void baseCameraOnPause() {
        cancelTimerTask();
    }

    @Override
    protected void onResume() {
        super.onResume();
        baseCameraOnResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        baseCameraOnPause();
    }

    //设置项目已被编辑过
    protected void setProjectHasEdited() {
        isProjectHasEdited = true;
    }





    public void initCameraSocket(final boolean interruptFinish) {

    }

    /**
     * 尝试重新连接相机
     *
     * @param dispatcherException 异常信息
     */
    protected void tryConnectCamera(DispatcherException dispatcherException) {

    }

    private void initPlayerImpl() {
        playerListenerImpl = new PlayerListenerImpl(this, playerSurfaceView, this);
        panoPlayer = playerSurfaceView.getRender();
        playerListenerImpl.setCalibrationCreateCallback(this);
        playerListenerImpl.setFixMode(false);
        playerSurfaceView.setOnClickPanoViewListener(this);
    }

    /**
     * 获取初始化时播放模式
     */
    private void initPlayerCheckItemMode() {
        playerMode = PlayerMode.PlayBack;

        changePlayerUiModule();
    }

    protected void initPlay() {

        changePlayerToLiveMode();

    }

    @Override
    protected boolean configIsShowBackArrow(DTMenuItem dtmiBack) {
        dtmiBack.setImageResource(R.mipmap.public_back_black);
        return true;
    }


    @Override
    protected void onRightMenuItemClicked(DTMenuItem dtmiRight) {
        super.onRightMenuItemClicked(dtmiRight);
        checkProjectPerfect();
    }

    @Override
    protected void onPriorRightMenuItemClicked(DTMenuItem dtmiPriorRight) {
        super.onPriorRightMenuItemClicked(dtmiPriorRight);
    }

    /**
     * 断开相机连接
     */
    public void disConnectCamera() {
        MainDispatcher.getInstance().stopSession();
        MainDispatcher.getInstance().closeStreamSocket();
        MainDispatcher.getInstance().destroy();
    }



    @Override
    public String getCalibrationFilePath() {
        String pathCameraRoot = FileUtil.getRootDir().getAbsolutePath() + File.separator + NetControl.getInstance().getSSID();
        File fileCameraRoot = new File(pathCameraRoot);
        if (!fileCameraRoot.exists()) {
            fileCameraRoot.mkdir();
        }
        File calibrationFile = new File(pathCameraRoot + File.separator + "calibration.txt");
        if (!calibrationFile.exists()) {
            if (!calibrationFile.exists()) {
                String calibration = getCalibration();
                if (!TextUtils.isEmpty(calibration)) {
                    FileReadandWrite.writetxt(calibrationFile.getAbsolutePath(), calibration);
                } else {
                    if (playerMode == PlayerMode.Preview) {
                        toast("标定数据为空");
                    }
                }
            }
        }
        return calibrationFile.getAbsolutePath();
    }




    /**
     * 提示用户连接相机网络
     */
    public void tipConnectCamera() {
//        final DialogReCheck dialogReCheck = new DialogReCheck(getContext());
//        dialogReCheck.updateMessage(R.string.support_open_camera_wifi)
//                .setPositiveText(R.string.support_action_setting)
//                .setNegativeText(R.string.support_action_cancel)
//                .setOnPositiveClickListener(new View.OnClickListener() {
//                    @Override
//                    public void onClick(View v) {
//                        dialogReCheck.dismiss();
//                        NetworkUtils.openWiFiSetting(ActivityCaptureBase.this, 0);
//                    }
//                }).setOnNegativeClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                dialogReCheck.dismiss();
//            }
//        }).show();
    }

    /**
     * 切换到预览模式
     */
    protected void changePlayerToLiveMode() {
        if (playerMode != PlayerMode.Preview) {
            playerMode = PlayerMode.Preview;
            changePlayerUiModule();
        }
        if (!MainDispatcher.getInstance().isCameraConnected()) {
            tipConnectCamera();
            return;
        }
        toggleLoading(true);
        LogUtil.i(TAG, "changePlayerToLiveMode()");
        ICamera camera = MainDispatcher.getInstance().getmCamera();
        if (cameraSocketInit && camera != null) {
            startPlayerLive();
        } else {
            initCameraSocket(false);
        }
    }

    /**
     * 开始播放预览
     */
    protected void startPlayerLive() {


    }

    /**
     * 开启回放
     *
     * @param filePath
     */
    protected void startPlayBack(String filePath) {
        LogUtil.i(TAG, "startPlayBack()");
        playerMode = PlayerMode.PlayBack;
        PanoData panoData = new PanoData();
        PanoNodeImage panoNodeImage = new PanoNodeImage();
        panoNodeImage.panoDeviceId = PanoDeviceId.PanoDeviceId_2_1;
        panoNodeImage.panoResourceType = PanoResourceType.SPHERE;
        panoNodeImage.urls = new String[]{filePath};
        panoData.nodeImage = panoNodeImage;
        PanoNodeView panoNodeView = new PanoNodeView();
        panoData.nodeView = panoNodeView;
        panoPlayer.play(panoData);
        LogUtil.i(TAG, "playerListenerImpl startPlayBack");
        changePlayerUiModule();

    }

    public void startPlayBack(Bitmap bitmap) {
        List<PanoPlayerOption> options = new ArrayList<>(1);
        PanoPlayerOption optionCodec = new PanoPlayerOption(PanoPlayerOptionType.OPT_CATEGORY_CODEC, PanoOptionKey.DETU_HW_DECODER, String.valueOf(true));
        options.add(optionCodec);
        PanoData panoData = new PanoData();
        PanoNodeImage panoNodeImage = new PanoNodeImage();
        panoNodeImage.panoDeviceId = PanoDeviceId.PanoDeviceId_2_1;
        panoNodeImage.panoResourceType = PanoResourceType.SPHERE;
        panoNodeImage.bitmap = bitmap;
        panoData.nodeImage = panoNodeImage;
        PanoNodeView panoNodeView = new PanoNodeView();
        panoData.nodeView = panoNodeView;
        panoPlayer.play(panoData, options);
        LogUtil.i(TAG, "playerListenerImpl startPlayBack");
    }

    protected void captureButtonClick() {
        if (!MainDispatcher.getInstance().isCameraConnected()) {
            tipConnectCamera();
            return;
        }
        showProgress("正在拍摄中，请勿移动相机");
        btnCapture.setEnabled(false);
        MainDispatcher.getInstance().getMachineVersion().doOnSuccess(new Consumer<BaseEntity>() {
            @Override
            public void accept(BaseEntity baseEntity) throws Exception {
                LogUtil.i(TAG, "相机信息获取成功");
                CameraInfo cameraInfo = MainDispatcher.getInstance().getCameraInfo();
                if (cameraInfo != null) {
                    LogUtil.i(TAG, "相机序列号:" + cameraInfo.getMachineId());
                }
            }
        }).doOnError(new RequestBuilder.ErrorCallback() {
            @Override
            public void onError(DispatcherException e) {
                LogUtil.i(TAG, "相机信息获取失败 !!!");
                toast("相机编号获取失败");
            }
        }).successThen().takePhoto().doOnSuccess(new Consumer<BaseEntity>() {
            @Override
            public void accept(@NonNull BaseEntity baseEntity) throws Exception {
                LogUtil.i(TAG, "拍照成功");
                onCaptureSuccess();
                MainDispatcher.getInstance().getFreeSpace().submit();

            }
        }).doOnError(new RequestBuilder.ErrorCallback() {
            @Override
            public void onError(DispatcherException dispatcherException) {
                LogUtil.i(TAG, "拍照失败:");
                onCaptureError(dispatcherException);
            }
        }).submit();
        changePlayerUiModule();
    }

    /**
     * 拍照完成
     *
     * @param dispatcherException 照片在相机中的路径
     */
    protected void onCaptureError(DispatcherException dispatcherException) {
        LogUtil.i(TAG, "onCaptureError() ");
        hideProgress();
        btnCapture.setEnabled(true);
        if (dispatcherException != null) {
            LogUtil.i(TAG, "takephoto failure cause by " + dispatcherException.getEntity().errorEnum.name());
            if (!isSdcardRemove && dispatcherException.getEntity().errorEnum == DispatcherError.ErrorEnum.NO_MORE_SPACE) {
                toast(R.string.infoSDCardFull);
            } else if (dispatcherException.getEntity().errorEnum == DispatcherError.ErrorEnum.INVALID_OPERATION) {
                //操作失败
                toast(R.string.infoOperationFailed);
            } else if (dispatcherException.getEntity().errorEnum == DispatcherError.ErrorEnum.SYSTEM_BUSY) {
                //相机繁忙
                toast(R.string.infoCameraBusy);
            } else if (dispatcherException.getEntity().errorEnum == DispatcherError.ErrorEnum.SDCARD_SLOW_ERROR) {
                //低速卡
                toast(R.string.infoSDCardLowSpeed);
            } else if (isSdcardRemove || dispatcherException.getEntity().errorEnum == DispatcherError.ErrorEnum.CARD_REMOVED_ERROR) {
                //无卡
                toast(R.string.infoSDCardRemove);
            } else if (dispatcherException.getEntity().errorEnum == DispatcherError.ErrorEnum.CARD_PROTECTED) {
                //卡写保护
                toast(R.string.infoSDCardProtected);
            } else if (dispatcherException.getEntity().errorEnum == DispatcherError.ErrorEnum.SDCARD_ERROR) {
                //卡错误
                toast(R.string.infoSDCardError);
            } else {
                toast(R.string.infoTakePhotoFailed);
            }
        } else {
            toast(R.string.infoTakePhotoFailed);
        }
    }

    /**
     * 拍照完成
     */
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
            LogUtil.i(TAG, "文件下载完成:" + fileInfo.getFilePath());
            toast(R.string.downloadSuccess);
            covertPhotoPath = generateSavePathCovert(fileInfo.getFilePath());
            DownloadPicTask.covertPhoto(fileInfo.getFilePath(), covertPhotoPath, DeviceId.TWO_FISHEYE, this);
        } else {
            toast(R.string.downloadError);
            hideProgress();
        }
        btnCapture.setEnabled(true);
    }

    @Override
    public void onVideoStitchProgressChanged(int i) {

    }

    @Override
    public void onVideoStitchStateChanged(RetCode retCode) {
        hideProgress();
        if (retCode == RetCode.OK) {
            toast("转码成功");
            LogUtil.i(TAG, "文件地址:" + covertPhotoPath);
            insertImageToProject(covertPhotoPath);
        } else {
            toast("转码失败");
        }
        setProjectHasEdited();
    }

    /**
     * 保存当前拍摄完成的项目
     *
     * @param filePath 文件地址
     */
    protected void insertImageToProject(String filePath) {
        isProjectHasEdited = true;

        //相机编号
        CameraInfo cameraInfo = MainDispatcher.getInstance().getCameraInfo();
        if (cameraInfo != null) {
            LogUtil.i(TAG, "相机序列号:" + cameraInfo.getMachineId());
        }
        String cameraSn = cameraInfo != null ? cameraInfo.getMachineId() : null;
        if (!TextUtils.isEmpty(cameraSn)) {

            startPlayBack(filePath);
        } else {
            toast("相机编号获取失败");
        }
    }


    /**
     * 生成文件保存地址
     *
     * @param fileUrl
     * @return
     */
    protected String generateSavePathDownload(String fileUrl) {
        File folder = new File(FileUtil.getRootDir(), "photo");
        if (!folder.exists()) {
            folder.mkdirs();
        }
        return folder.getAbsolutePath() + "/" + fileUrl.substring(fileUrl.lastIndexOf("/") + 1, fileUrl.length()).replaceAll("\\\\", "/");
    }

    /**
     * 生成文件保存地址
     *
     * @param fileUrl
     * @return
     */
    protected String generateSavePathCovert(String fileUrl) {
        File folder = new File(FileUtil.getRootDir(), "photo");
        if (!folder.exists()) {
            folder.mkdirs();
        }
        return folder.getAbsolutePath() + "/" + "pano-" + fileUrl.substring(fileUrl.lastIndexOf("/") + 1, fileUrl.length()).replaceAll("\\\\", "/");
    }


    /**
     * @return 获取标定
     */
    protected String getCalibration() {
        GetWeightAndMaskHelper helper = new GetWeightAndMaskHelper();
        ICamera camera = MainDispatcher.getInstance().getmCamera();
        String calibrationText = MainDispatcher.getInstance().getCameraInfo().getCalibration();

        if (camera != null) {
            int cameraIndex = camera.getDeviceIndex();
            switch (cameraIndex) {
                case ICamera.UPLOAD_INDEX_TWIN_A:
                    //不用转换
                    if (TextUtils.isEmpty(calibrationText)) {
                        LogUtil.e(TAG, "相机标定获取失败 !!!");
                        calibrationText = "6_713_763_771_-180_0_0_742.5_2280.5_769.5_1.45069_-0.249857_-1.42378_3040_1520_-1.08282_-1.41421_0_0_0_0_-0.531259_0_0_-0.627377_205_187";
                    }
                    break;
                case ICamera.UPLOAD_INDEX_F4PLUS:
                    //需要转换
                    calibrationText = helper.GetWgetWeightAndMaskInfo(calibrationText, new int[]{1024, 512}, getWeightPaths());
                    break;
            }
        }
        LogUtil.i(TAG, "getCalibration() --->" + calibrationText);
        return calibrationText;
    }

    @Override
    public String[] getWeightPaths() {
        return new String[0];
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.reAction:
                //此按钮有--完成/ 重拍 / 重新编辑功能
                if (playerMode == PlayerMode.Capture || playerMode == PlayerMode.ReCapture) {
                    captureButtonClick();
                } else if (playerMode == PlayerMode.PlayBack) {
                    playerMode = PlayerMode.Capture;
                    changePlayerToLiveMode();
                    changePlayerUiModule();
                }
                break;
            case R.id.btnCapture:
                captureButtonClick();
                break;
        }
    }



    private void changePlayerUiModule() {
        TextView reAction = findViewById(R.id.reAction);
        View btnCapture = findViewById(R.id.btnCapture);
        if (playerMode == null) {
            //不显示重拍
            reAction.setVisibility(View.GONE);
            //显示拍照按钮
            btnCapture.setVisibility(View.VISIBLE);
            btnCapture.setEnabled(false);
        }else if (playerMode == PlayerMode.Capture) {
            //模式切换,模型编辑模式,不显示
            reAction.setVisibility(View.GONE);
            //显示拍照按钮
            btnCapture.setVisibility(View.VISIBLE);
        } else if (playerMode == PlayerMode.ReCapture) {
            //模式切换,模型编辑模式,不显示
            reAction.setText(R.string.reTakePhoto);
            reAction.setBackgroundResource(R.drawable.project_background_recapture);
            reAction.setTextColor(Color.parseColor("#FFFFFF"));
            //不显示拍照按钮
            btnCapture.setVisibility(View.VISIBLE);
        }else if (playerMode == PlayerMode.PlayBack) {
            //显示从新拍摄
            reAction.setText(R.string.reTakePhoto);
            reAction.setBackgroundResource(R.drawable.project_background_recapture);
            reAction.setTextColor(Color.parseColor("#FFFFFF"));
            reAction.setVisibility(View.VISIBLE);
            //不显示拍照按钮
            btnCapture.setVisibility(View.GONE);
        } else if (playerMode == PlayerMode.Preview) {
            //预览,没拍摄--只显示拍照按钮
            //模式切换,模型编辑模式,不显示
            reAction.setVisibility(View.GONE);
            //显示拍照按钮
            btnCapture.setVisibility(View.VISIBLE);
        }

    }

    /**
     * @return 检查项目是否完成
     */
    public void checkProjectPerfect() {

        disConnectCamera();
        setResult(RESULT_OK);
        finish();
    }

    @Override
    public void onClickPanoView(MotionEvent event) {

    }


    @Override
    public void onPlayLoading() {
        LogUtil.i(TAG, "onPlayLoading()");
        toggleLoading(true);
    }

    @Override
    public void onPlayLoaded() {
        LogUtil.i(TAG, "onPlayLoaded()");
        toggleLoading(false);
        btnCapture.setEnabled(true);
    }

    @Override
    public void onPlayError(PlayerListenerImpl.PlayError playError) {
        LogUtil.i(TAG, "onPlayError()");

    }

    @Override
    public void onPlaySurfaceViewClicked() {

    }

    @Override
    public void onWorkSceneInfosLoaded(List<WorkSceneInfo> list) {

    }

    @Override
    public void onBeginPlayScene(int i, WorkSceneInfo workSceneInfo, int i1) {

    }

    @Override
    public void onVideoPlayProgressChanged(int i, int i1, int i2) {

    }

    @Override
    public void onVideoPlayStatusChanged(PlayerListenerImpl.VideoPlayStatus videoPlayStatus) {

    }

    @Override
    public void onViewModelChange(PanoViewMode panoViewMode) {

    }

    @Override
    public void onVideoQualityChanged(int i) {

    }

    @Override
    public void onGyroStateChange(boolean b) {

    }

    @Override
    public void onBackPressed() {
        if (!isProjectHasEdited) {
            //项目没有被编辑过就直接退出
            disConnectCamera();
            setResult(RESULT_OK);
            finish();
            return;
        }

    }

    //没有网络链接
    private static final int STATE_NET_NO = -1;
    //WiFi网络
    private static final int STATE_NET_WIFI = 1;
    //手机网络
    private static final int STATE_NET_MOBILE = 2;
    private int curNetState;

    @Override
    public void onReceiveBroadcast(Context context, Intent intent) {
        super.onReceiveBroadcast(context, intent);
        String action = intent.getAction();
        LogUtil.i(TAG, "onReceiveBroadcast()" + action);
        if (WifiManager.NETWORK_STATE_CHANGED_ACTION.equals(action) || WifiManager.WIFI_STATE_CHANGED_ACTION.equals(action)) {
            int netState = getNetState();
            if (curNetState != netState) {
                curNetState = netState;
                if (MainDispatcher.getInstance().isCameraConnected()) {
                    if (PlayerMode.Preview == playerMode) {
                        initCameraSocket(false);
                    }
                } else {
                    cameraSocketInit = false;
                    if (btnCapture != null) {
                        btnCapture.setEnabled(false);
                    }
                    disConnectCamera();
                    toast("相机已断开连接");
                }
            }
        }
    }

    private int getNetState() {
        int netState = STATE_NET_NO;
        ConnectivityManager connectMgr = (ConnectivityManager) getSystemService(CONNECTIVITY_SERVICE);
        if (connectMgr != null) {
            NetworkInfo networkInfo = connectMgr.getActiveNetworkInfo();
            if (networkInfo != null) {
                int nType = networkInfo.getType();
                if (nType == ConnectivityManager.TYPE_MOBILE) {
                    LogUtil.e(TAG, "移动网络链接 !!! ");
                    netState = STATE_NET_MOBILE;
                } else if (nType == ConnectivityManager.TYPE_WIFI) {
                    LogUtil.e(TAG, "WiFi已连接 !!! ");
                    netState = STATE_NET_WIFI;
                } else {
                    LogUtil.e(TAG, "未网络链接,当WiFi网络处理");
                    netState = STATE_NET_WIFI;
                }
            }
        }
        return netState;
    }

    @Override
    protected void onDestroy() {
        cancelTimerTask();
        disConnectCamera();
        MainDispatcher.getInstance().destroy();
//        if (playerSurfaceView != null) {
//            playerSurfaceView.onDestroy();
//        }
        super.onDestroy();
    }

    //是否显示菊花
    protected void toggleLoading(boolean isShow) {
        if (isShow) {
            loadingView.setVisibility(View.VISIBLE);
            animationDrawable.start();
        } else {
            animationDrawable.stop();
            loadingView.setVisibility(View.GONE);
        }

    }



    /**
     * 相机当前电量过低
     *
     * @param percent 相机电量 %
     */
    int lastTipCameraBatteryLevel;

    @Override
    public void onCameraBatteryLowEventCallback(int percent) {
        if (percent == 5 || percent - lastTipCameraBatteryLevel >= 5) {
            //每过5 提示一次
            lastTipCameraBatteryLevel = percent;
            String message = "相机电量过低,剩余电量";

        }
    }

    @Override
    public void onReceive(NotificationType type, int param) {
        LogUtil.i(TAG, "Camera Notification type :" + type);
        if (type == NotificationType.BATTERY_VALUE) {
            LogUtil.i(TAG, "BATTERY_VALUE:" + param);
        } else if (type == NotificationType.POWER_OFF) {
            LogUtil.i(TAG, "相机已关机 !!!");
            if (getContext() != null) {

            }
        } else if (type == NotificationType.SD_FULL) {
            toast(R.string.infoSDCardFull);
        } else if (type == NotificationType.LOW_STORAGE_WARNING) {
            toast(R.string.infoSDCardFull);
        } else if (type == NotificationType.USB_MSC_ENTER) {

        } else if (type == NotificationType.HDMI_IN) {

        } else if (type == NotificationType.DC_OUT) {
            LogUtil.i(TAG, "未充电 !!!");
            MainDispatcher.getInstance().getBattery().submit();
            lastTipCameraBatteryLevel = 0;
        } else if (type == NotificationType.DC_IN) {
            LogUtil.i(TAG, "充电中 !!!");
            lastTipCameraBatteryLevel = 0;
        } else if (type == NotificationType.SESSTION_STOP) {

        }
    }

    @Override
    public boolean toggleInteractionDispatchTouchEvent() {
        return super.toggleInteractionDispatchTouchEvent();
    }

    private int checkBatteryCount = 0;

    @Override
    public void onCameraTFSpaceChangeCallback(long space) {
        isSdcardRemove = space == -1;
    }

    private class CheckTimerTask extends TimerTask {
        @Override
        public void run() {
            LogUtil.i(TAG, "CheckTimerTask - getBattery");
            MainDispatcher.getInstance().getBattery().doFinally(() -> {
                checkBatteryCount++;
            }).submit();
        }
    }

    private boolean isCancelTimer = true;
    private Timer timer;

    protected void cancelTimerTask() {
        synchronized (this) {
            if (isCancelTimer) {
                return;
            }
            LogUtil.i(TAG, "cancelTimerTask");
            if (timer != null) {
                timer.cancel();
            }
            isCancelTimer = true;
        }
    }

    protected void restartTimerTask() {
        synchronized (this) {
            if (!isCancelTimer) {
                return;
            }
            LogUtil.i(TAG, "restartTimerTask");
            timer = new Timer();
            timer.schedule(new CheckTimerTask(), 5000, 5 * 1000);
            isCancelTimer = false;
        }
    }


    /**
     * 播放器当前模式
     */
    public enum PlayerMode {
        //预览模式
        Preview,
        //拍照模式
        Capture,
        //重拍模式
        ReCapture,
        //标记模式
        //回放
        PlayBack
    }

}
