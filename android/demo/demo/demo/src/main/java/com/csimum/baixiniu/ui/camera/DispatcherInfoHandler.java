package com.csimum.baixiniu.ui.camera;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;

import com.csimum.baixiniu.ui.camera.eventcallback.ICameraLowBatteryEventCallback;
import com.csimum.baixiniu.ui.camera.eventcallback.ICameraTFSpaceChange;
import com.detu.dispatch.dispatcher.CameraInfo;
import com.detu.dispatch.dispatcher.CameraInfoType;
import com.detu.dispatch.dispatcher.entity.BatteryEntity;
import com.detu.dispatch.dispatcher.entity.BatteryStateEnum;
import com.detu.module.libs.LogUtil;

import java.text.DecimalFormat;

public class DispatcherInfoHandler extends Handler {
    private static final String TAG = "DispatcherInfoHandler";
    private ICameraLowBatteryEventCallback cameraLowBatteryEventCallback;
    private ICameraTFSpaceChange cameraTFSpaceChange;
    private Handler uiHandler = new Handler(Looper.getMainLooper());

    public void setCameraLowBatteryEventCallback(ICameraLowBatteryEventCallback cameraLowBatteryEventCallback) {
        this.cameraLowBatteryEventCallback = cameraLowBatteryEventCallback;
    }

    public void setCameraTFSpaceChange(ICameraTFSpaceChange cameraTFSpaceChange) {
        this.cameraTFSpaceChange = cameraTFSpaceChange;
    }

    @Override
    public void handleMessage(final Message msg) {
        if (msg != null) {
            resolveMessage(msg);
        }
    }

    private void resolveMessage(Message msg) {
        if (msg == null || msg.obj == null) {
            LogUtil.i(TAG, "消息为空 !!!");
            return;
        }
        switch (msg.what) {
            case CameraInfoType.CurrentMode:
                if (msg.obj instanceof CameraInfo.CaptureMode) {
                    CameraInfo.CaptureMode mode = (CameraInfo.CaptureMode) msg.obj;
                }
                break;
            case CameraInfoType.CurrentTFSpace:
                LogUtil.i(TAG, "space :" + msg.obj);
                if (msg.obj instanceof Long) {
                    long space = (long) msg.obj;
                    if(cameraTFSpaceChange != null){
                        cameraTFSpaceChange.onCameraTFSpaceChangeCallback(space);
                    }
                    if (space == -1) {
                        LogUtil.i(TAG, "SDCardRemoved !!!");
                    } else if (space >= 0) {
                        space /= 1024;
                        if (space > 1024) {
                            float spaceFloat = space / 1024.00f;
                            DecimalFormat decimalFormat = new DecimalFormat(".00");//构造方法的字符格式这里如果小数不足2位,会以0补足.
                            String spaceFloatRes = decimalFormat.format(spaceFloat);//format 返回的是字符串
                            LogUtil.i(TAG, spaceFloatRes + "G");
                        } else {
                            LogUtil.i(TAG, space + "M");
                        }
                    }
                }
                break;
            case CameraInfoType.Calibration:
                LogUtil.i(TAG, "Calibration :" + msg.obj);
                break;
            case CameraInfoType.FreePicNum:
                LogUtil.i(TAG, "FreePicNum :" + msg.obj);
                break;
            case CameraInfoType.PhotoPath:
                String photoPath = (String) msg.obj;
                LogUtil.i(TAG, "PhotoPath :" + msg.obj);

                break;
            case CameraInfoType.PhotoName:
                LogUtil.i(TAG, "PhotoName :" + msg.obj);

                break;
            case CameraInfoType.PhotoThumb:
                LogUtil.i(TAG, "PhotoThumb :" + msg.obj);
                break;
            case CameraInfoType.FileList:
                LogUtil.i(TAG, "CameraInfoType.FileList");
                break;
            case CameraInfoType.FirmwareVersion:
                LogUtil.i(TAG, "FirmwareVersion :" + msg.obj);
                break;
            case CameraInfoType.Battery:
                LogUtil.i(TAG, "Battery :" + msg.obj);
                break;
            case CameraInfoType.RecordTime:
                LogUtil.i(TAG, "RecordTime :" + msg.obj);
                Long second = (long) msg.obj;
                break;
            case CameraInfoType.FirewareUploadPath:
                LogUtil.i(TAG, "FirewareUploadPath :" + msg.obj);
                break;
            case CameraInfoType.SdcardState:
                LogUtil.i(TAG, "SdcardState :" + msg.obj);
                break;
            case CameraInfoType.MachineId:
                LogUtil.i(TAG, "MachineId :" + msg.obj);
                break;
            case CameraInfoType.VideoResolution:
                LogUtil.i(TAG, "VideoResolution :" + msg.obj);
                break;
            case CameraInfoType.PhotoResolution:
                LogUtil.i(TAG, "PhotoResolution :" + msg.obj);
                break;
            case CameraInfoType.VfResolution:
                LogUtil.i(TAG, "VfResolution :" + msg.obj);
                break;
            case CameraInfoType.MicSwitch:
                LogUtil.i(TAG, "MicSwitch :" + msg.obj);
                break;
            case CameraInfoType.BeepSwitch:
                LogUtil.i(TAG, "BeepSwitch :" + msg.obj);
                break;
            case CameraInfoType.LoopSwitch:
                LogUtil.i(TAG, "LoopSwitch :" + msg.obj);
                break;
            case CameraInfoType.Frequency:
                LogUtil.i(TAG, "Frequency :" + msg.obj);
                break;
            case CameraInfoType.HdrSwitch:
                LogUtil.i(TAG, "HdrSwitch :" + msg.obj);
                break;
            case CameraInfoType.WdrSwitch:
                LogUtil.i(TAG, "WdrSwitch :" + msg.obj);
                break;
            case CameraInfoType.Exposure:
                LogUtil.i(TAG, "Exposure :" + msg.obj);
                break;
            case CameraInfoType.WB:
                LogUtil.i(TAG, "WB :" + msg.obj);
                break;
            case CameraInfoType.ISO:
                LogUtil.i(TAG, "ISO :" + msg.obj);
                break;
            case CameraInfoType.POWEROFF:
                LogUtil.i(TAG, "POWEROFF :" + msg.obj);
                break;
            case CameraInfoType.CyclicRec:
                LogUtil.i(TAG, "CyclicRec :" + msg.obj);
//                splitTime.setText(getString(R.string.pageEveryVideoTime) + ":" + ((MovieCyclicRecEnum) msg.obj).valueOf());
                break;
            case CameraInfoType.Gsensor:
                LogUtil.i(TAG, "Gsensor :" + msg.obj);
                break;
            case CameraInfoType.Timelapse:
                LogUtil.i(TAG, "Timelapse :" + msg.obj);
                break;
            case CameraInfoType.Motion:
                LogUtil.i(TAG, "Motion :" + msg.obj);
                break;
            case CameraInfoType.VideoQuality:
                LogUtil.i(TAG, "VideoQuality :" + msg.obj);
                break;
            case CameraInfoType.PhotoQuality:
                LogUtil.i(TAG, "PhotoQuality :" + msg.obj);
                break;
            case CameraInfoType.SplitTime:
                LogUtil.i(TAG, "SplitTime :" + msg.obj);
                break;
            case CameraInfoType.AntisShakeSwitch:
                LogUtil.i(TAG, "AntisShakeSwitch :" + msg.obj);
                break;
            case CameraInfoType.SSID:
                LogUtil.i(TAG, "SSID :" + msg.obj);
                break;
            case CameraInfoType.Password:
                LogUtil.i(TAG, "Password :" + msg.obj);
                break;
            case CameraInfoType.LiveBitrate:
                LogUtil.i(TAG, "LiveBitrate :" + msg.obj);
                break;
            case CameraInfoType.VideoBitrate:
                LogUtil.i(TAG, "VideoBitrate :" + msg.obj);
                break;
            case CameraInfoType.Battery_Entity:
                if (msg.obj instanceof BatteryEntity) {
                    BatteryEntity batteryEntity = (BatteryEntity) msg.obj;
                    LogUtil.i(TAG, "Battery_Entity : " + batteryEntity.stateEnum + "," + batteryEntity.batteryValue);
                    if (batteryEntity.stateEnum == BatteryStateEnum.BATTERY_CHARGE) {
                        LogUtil.i(TAG, "充电中.....");
                    } else {
                        LogUtil.i(TAG, "电量剩余 : " + batteryEntity.batteryValue + " %");
                        if (batteryEntity.batteryValue < 50) {
                            LogUtil.i(TAG, "电量低于50%");
                            if (cameraLowBatteryEventCallback != null) {
                                cameraLowBatteryEventCallback.onCameraBatteryLowEventCallback(batteryEntity.batteryValue);
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
    }


}
