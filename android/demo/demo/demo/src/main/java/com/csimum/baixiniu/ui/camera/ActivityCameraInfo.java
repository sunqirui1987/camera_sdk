package com.csimum.baixiniu.ui.camera;

import android.graphics.Typeface;
import android.os.Handler;
import android.view.View;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.csimum.baixiniu.R;
import com.detu.dispatch.dispatcher.CameraInfo;
import com.detu.dispatch.dispatcher.DispatcherException;
import com.detu.dispatch.dispatcher.MainDispatcher;
import com.detu.dispatch.dispatcher.OnPreparedListener;
import com.detu.dispatch.dispatcher.entity.BaseEntity;
import com.detu.dispatch.dispatcher.entity.CameraTypeEnum;
import com.detu.module.app.ActivityWithTitleBar;
import com.detu.module.libs.LogUtil;

import java.text.DecimalFormat;

import static com.detu.dispatch.dispatcher.DispatcherError.ErrorEnum.ANOTHER_CAMERA_CONNECTED;

/**
 * 相机详情页
 */
public class ActivityCameraInfo extends ActivityWithTitleBar implements View.OnClickListener {
    private static final String TAG = "ActivityCameraInfo";
    private TextView textViewCameraSN;
    private TextView textViewCameraStorage;
    private ProgressBar progressBarView;

    @Override
    public int getViewContentLayoutId() {
        return R.layout.activity_camera_info;
    }

    @Override
    public void initViews() {
        setTitle(R.string.camera_info_title);
        getTitleMenuItem().getLabelView().setTypeface(Typeface.DEFAULT_BOLD);
        findViewById(R.id.btnClearSDCard).setOnClickListener(this);
        //相机编号
        textViewCameraSN = findViewById(R.id.textViewCameraSN);
        textViewCameraStorage = findViewById(R.id.textViewCameraStorage);
        progressBarView = findViewById(R.id.progressBarView);
        if (MainDispatcher.getInstance().isCameraConnected()) {
            showProgress(R.string.camera_info_storage_loading);
            initCameraSocket(false);
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btnClearSDCard:
                clearSdCard();
                break;
        }
    }

    /**
     * 更新相机信息
     */
    private void updateCameraInfo() {
        //相机图片
        ImageView imageViewCameraIC = findViewById(R.id.imageViewCameraIC);
        //相机型号
        TextView textViewCameraModel = findViewById(R.id.textViewCameraModel);
        CameraTypeEnum cameraTypeEnum = MainDispatcher.getInstance().getmCameraType();
        if (CameraTypeEnum.DispatchMachine_TwinA == cameraTypeEnum) {
            textViewCameraModel.setText("Twin");
            imageViewCameraIC.setImageResource(R.mipmap.camera_ic_twin);
        } else if (CameraTypeEnum.DispatchMachine_F4Plus == cameraTypeEnum) {
            textViewCameraModel.setText("F4 Plus");
            imageViewCameraIC.setImageResource(R.mipmap.camera_ic_fplus);
        }
        getCameraSpaceInfo();
    }

    public void initCameraSocket(final boolean interruptFinish) {
        MainDispatcher.getInstance().prepare(new OnPreparedListener() {
            @Override
            public void onPrepared() {
                LogUtil.i(TAG, "onPrepared() ");
                updateCameraInfo();
            }

            @Override
            public void onPrepareFailed(DispatcherException dispatcherException) {
                LogUtil.i(TAG, "onPrepareFailed() ");
                if (dispatcherException != null && dispatcherException.getEntity() != null) {
                    BaseEntity entity = dispatcherException.getEntity();
                    if (entity != null && ANOTHER_CAMERA_CONNECTED == entity.errorEnum) {
                        if (interruptFinish) {
                            toast("请先断开其他相机连接");
                            finish();
                        }
                    }
                }
            }
        });

    }

    private void getCameraSpaceInfo() {
        LogUtil.i(TAG, "getCameraSpaceInfo()");
        MainDispatcher.getInstance().getFreeSpace().doOnSuccess(baseEntity -> {
            LogUtil.i(TAG, "getFreeSpace().doOnSuccess()");
            CameraInfo cameraInfo = MainDispatcher.getInstance().getCameraInfo();
            if (cameraInfo != null && textViewCameraStorage != null && progressBarView != null) {
                String sn = cameraInfo.getMachineId();
                textViewCameraSN.setText(sn);
                //相机存储容量
                long tfSpaceFreeKB = cameraInfo.getCurrentTFSpace();
                LogUtil.i(TAG, "SpaceFreeKB :" + tfSpaceFreeKB);
            }
            getTotalSpace();
        })
                .doOnError(e -> {
                    LogUtil.i(TAG, "getFreeSpace().doOnError()");
                    toast(R.string.camera_info_get_error);
                    if (textViewCameraStorage != null) {
                        textViewCameraStorage.setText(R.string.camera_info_storage_tf_error);
                    }
                    if (progressBarView != null) {
                        progressBarView.setProgress(0);
                    }
                }).submit();
    }

    private void getTotalSpace() {
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                LogUtil.i(TAG, "getTotalSpace() :");
                MainDispatcher.getInstance().getTotalSpace().successThen().getMachineVersion().doOnSuccess(baseEntity2 -> {
                    LogUtil.i(TAG, "getTotalSpace()--> doOnSuccess()");
                    CameraInfo cameraInfo = MainDispatcher.getInstance().getCameraInfo();
                    if (cameraInfo != null && textViewCameraStorage != null && progressBarView != null) {
                        String sn = cameraInfo.getMachineId();
                        textViewCameraSN.setText(sn);
                        //相机存储容量
                        long tfSpaceFreeKB = cameraInfo.getCurrentTFSpace();
                        long tfSpaceTotalKB = cameraInfo.getTotalTFSpace();
                        long tfSpaceUseKB = tfSpaceTotalKB - tfSpaceFreeKB;
                        LogUtil.i(TAG, "SpaceFreeKB :" + tfSpaceFreeKB);
                        LogUtil.i(TAG, "tfSpaceTotalKB :" + tfSpaceTotalKB);
                        LogUtil.i(TAG, "tfSpaceUseKB :" + tfSpaceUseKB);
                        String useSpace = "";
                        String totalSpace = "";
                        if (tfSpaceTotalKB > 0) {
                            float spaceFloatTotalGB = tfSpaceTotalKB / 1024.00f / 1024.00f;
                            DecimalFormat decimalFormatTotal = new DecimalFormat("0.00");
                            totalSpace = decimalFormatTotal.format(spaceFloatTotalGB) + "G";
                            float spaceFloatUseGB = tfSpaceUseKB / 1024.00f / 1024.00f;
                            DecimalFormat decimalFormatUse = new DecimalFormat("0.00");
                            if (spaceFloatUseGB > 1024) {
                                useSpace = decimalFormatUse.format(spaceFloatUseGB) + "G";
                            } else {
                                useSpace = decimalFormatUse.format((tfSpaceUseKB / 1024.00f)) + "M";
                            }
                            textViewCameraStorage.setText(getString(R.string.camera_info_storage_format, useSpace, totalSpace));
                            int usePercent = (int) (tfSpaceUseKB * 1f / tfSpaceTotalKB * 100);
                            progressBarView.setProgress(usePercent < 1 ? 1 : usePercent);
                        } else {
                            textViewCameraStorage.setText(R.string.camera_info_storage_tf_error);
                            progressBarView.setProgress(0);
                        }
                    } else {
                        toast(R.string.camera_info_get_error);
                        if (textViewCameraStorage != null) {
                            textViewCameraStorage.setText(R.string.camera_info_storage_tf_error);
                        }
                        if (progressBarView != null) {
                            progressBarView.setProgress(0);
                        }
                    }
                }).doOnError(e -> {
                    toast(R.string.camera_info_get_error);
                    if (textViewCameraStorage != null) {
                        textViewCameraStorage.setText(R.string.camera_info_storage_tf_error);
                    }
                    if (progressBarView != null) {
                        progressBarView.setProgress(0);
                    }
                }).doFinally(() -> hideProgress()).submit();
            }
        }, 1000);
    }

    /**
     * 格式化SD卡
     */
    private void clearSdCard() {
//        final DialogReCheck dialogReCheck = new DialogReCheck(getContext());
//        dialogReCheck.updateMessage(R.string.camera_info_storage_check)
//                .setOnPositiveClickListener(v -> {
//                    dialogReCheck.dismiss();
//                    MainDispatcher.getInstance().formatSdcard().doOnSuccess(baseEntity -> {
//                        toast(R.string.camera_info_storage_clear_success);
//                        showProgress(R.string.camera_info_storage_loading);
//                        getCameraSpaceInfo();
//                    }).doOnError(e -> {
//                        toast(R.string.camera_info_storage_clear_error);
//                    }).submit();
//                }).setOnNegativeClickListener(v -> dialogReCheck.dismiss()).show();
    }

}
