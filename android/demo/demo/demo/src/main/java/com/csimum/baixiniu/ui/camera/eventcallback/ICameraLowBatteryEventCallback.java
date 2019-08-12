package com.csimum.baixiniu.ui.camera.eventcallback;

/**
 * 相机低电量回调
 */
public interface ICameraLowBatteryEventCallback {
    /**
     * 相机当前电量过低
     *
     * @param percent 相机电量 %
     */
    void onCameraBatteryLowEventCallback(int percent);
}
