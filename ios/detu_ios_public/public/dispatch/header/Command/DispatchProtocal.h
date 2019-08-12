//
//  DispatchProtocal.h
//  dispatchlib
//
//  Created by Seth on 2017/7/9.
//  Copyright © 2017年 detu. All rights reserved.
//

/**
 *  @abstract camera error status‘s  type
 */
typedef NS_ENUM(NSInteger, CameraErrorType) {
    CameraErrorType_None                    = 0 ,  // 相机正常
    CameraErrorType_Command                 = 1 ,  // 相机命令连续失败，判断是相机异常，推送通知到业务
    CameraErrorType_Change                  = 2 ,  // 切换到其他的相机，推送通知到业务
    CameraErrorType_Others                  = 3 ,  // 其他异常
};

/**
 *  @abstract operation‘s  Type
 */
typedef NS_ENUM(NSInteger, DispatchOperationType) {
    DispatchOperationType_None              = 0 ,   // 调度器正常
    DispatchOperationType_Doing             = 1 ,   // 调度器繁忙
    DispatchOperationType_Cancel            = 2 ,   // 调度器取消
};

/**
 *  @abstract Application‘s  status
 */
typedef NS_ENUM(NSInteger, ApplicationStatus) {
    ApplicationStatus_None                 = 0 ,
    ApplicationStatus_enterForeground      = 1 ,
    ApplicationStatus_becomeActive         = 2 ,
    ApplicationStatus_resignActive         = 3 ,
    ApplicationStatus_enterBackground      = 4 ,
    ApplicationStatus_willTerminate        = 5
};

/**
 *  @abstract call‘s  status
 */
typedef NS_ENUM(NSInteger, CTCallStates) {
    CTCallStates_None              = 0 ,
    CTCallStates_Incoming          = 1 ,
    CTCallStates_Connected         = 2 ,
    CTCallStates_Disconnected      = 3
};

/**
 *  @abstract machine's  Type
 */
typedef NS_ENUM(NSInteger, Dispatch_MachineType) {
    
    DispatchMachine_None           = 0 ,
    DispatchMachine_Sphere800      = 1 ,
    DispatchMachine_SphereS        = 2 ,
    DispatchMachine_TwinN          = 3 ,
    DispatchMachine_Dokicam        = 4 ,
    DispatchMachine_TwinA          = 5 ,
    DispatchMachine_Outs           = 6 ,
    DispatchMachine_Thetas         = 7
};

/**
 *  @abstract Application's  Type
 */
typedef NS_ENUM(NSInteger, Dispatch_ApplicationType) {
    
    DispatchApplication_DETUCAMERA     = 0 ,
    DispatchApplication_VRCAMERA       = 1 ,
    DispatchApplication_DRAGON         = 2
};


/**
 *  @abstract Command parameter
 *  Used to identify scheduling methods
 */
typedef NS_ENUM(int, DispatchCommand) {
    
    DispatchCommand_None                                = 0000 ,    // 空命令
    DispatchCommand_needUpdate                          = 0001 ,    // 升级固件
    DispatchCommand_getFilelist                         = 5000 ,    // 文件列表
    DispatchCommand_getThumbnail                        = 3000 ,    // 获取缩略图
    DispatchCommand_getSensor                           = 1008 ,    // 获取标定
    DispatchCommand_getVFStatus                         = 1009 ,    // 获取VF
    DispatchCommand_getMachineVersion                   = 2 ,       // 机器型号
    DispatchCommand_getStatus                           = 1003 ,    // 获取设备详情
    DispatchCommand_getMediaSize                        = 1002 ,    // 获取视频分辨率
    DispatchCommand_getCaptureSize                      = 1005 ,    // 获取照片分辨率
    DispatchCommand_getMediaQuality                     = 1004 ,    // 获取视频质量
    DispatchCommand_getCaptureQuality                   = 1006 ,    // 获取照片质量
    DispatchCommand_getISO                              = 1007 ,    // 获取IOS合集
    
    DispatchCommand_getFrep                             = 1010 ,    // 获取光源合集
    DispatchCommand_getBeep                             = 1011 ,    // 获取蜂鸣器合集
    DispatchCommand_getRecordSplitTime                  = 1012 ,    // 获取录像分段时长合集
    DispatchCommand_getLoopTime                         = 1013 ,    // 获取循环录像时长合集
    
    DispatchCommand_getCurrentMode                      = 4 ,       // 获取当前的模式
    DispatchCommand_getBattery                          = 5 ,       // 获取电量
    DispatchCommand_getRecordingTime                    = 6 ,       // 获取当前录制时间
    DispatchCommand_getSystemVersion                    = 7 ,       // 获取固件版本号
    DispatchCommand_getFreeSpace                        = 8 ,       // 剩余空间
    DispatchCommand_getSSIDAndPwd                       = 9 ,       // 获取ssId和密码
    DispatchCommand_getSDCardState                      = 10,       // 获取sd卡状态
    DispatchCommand_getStorgeState                      = 1014,     // 获取存储状态（rec：录像拍照模式，msc存储模式，fwupdate升级状态，other其他 ）
    
    DispatchCommand_mediaRecord                         = 11,       // 录制
    DispatchCommand_mediaCapture                        = 12,       // 拍照
    DispatchCommand_mediaCaptureSize                    = 13,       // 照片size
    DispatchCommand_mediaRecordSize                     = 14,       // 视频size
    DispatchCommand_liveShow                            = 15,       // 预览流
    DispatchCommand_changeMode                          = 16,       // 模式切换
    
    DispatchCommand_setClientInfo                       = 2003 ,    // 设置平台信息
    DispatchCommand_setMediaSize                        = 2002 ,    // 设置视频分辨率
    DispatchCommand_setDate                             = 17,       // 时间设置
    DispatchCommand_setSensor                           = 2008,     // 标定设置
    DispatchCommand_setVFStatus                         = 2009 ,    // 设置VF
    DispatchCommand_setWB                               = 19,       // WB设置
    DispatchCommand_setISO                              = 20,       // ISO设置
    DispatchCommand_setEV                               = 21,       // EV设置
    DispatchCommand_setHDR                              = 22,       // HDR设置
    DispatchCommand_setWDR                              = 23,       // WDR设置
    DispatchCommand_setTrafficMode                      = 24,       // 行车模式
    DispatchCommand_setTraffic_LiveShow                 = 240,      // 行车视频预览
    DispatchCommand_setMotionDetect                     = 241,      // 运动检测
    DispatchCommand_setMIC                              = 25,       // MIC设置
    DispatchCommand_setCyclerec                         = 26,       // 循环录像
    DispatchCommand_setSegment                          = 26 << 3,  // 分段时间
    DispatchCommand_setTimingRec                        = 27,       // 缩时录像
    DispatchCommand_setPhotoQuality                     = 2006,     // 照片质量
    DispatchCommand_setMediaQuality                     = 2004,     // 照片质量
    DispatchCommand_setDefMode                          = 29,       // 默认模式
    DispatchCommand_setPhotoButer                       = 30,       // 照片连拍
    DispatchCommand_setBeep                             = 2011,     // 蜂鸣器
    DispatchCommand_setSoundRecord                      = 2012,     // 录音开关
    DispatchCommand_setRecordBitrate                    = 32,       // 录制码速
    DispatchCommand_setSensitityOfGravity               = 322,      // 重力灵敏度
    DispatchCommand_setLiveViewBitrate                  = 33,       // 设置预览视频速率，kb/s
    DispatchCommand_setWifiPassword                     = 34,       // 设置wifi密码
    DispatchCommand_setPowerOff                         = 35,       // 设置设备关机时间
    DispatchCommand_setAntisShake                       = 36,       // 光学防抖
    DispatchCommand_setDateWaterMark                    = 37,       // 日期水印
    DispatchCommand_setSystemFreq                       = 2010,     // 设置光源频率
    DispatchCommand_setWiFiChanel                       = 2030,     // 设置WiFi制式
    DispatchCommand_setLEDSwitch                        = 39,       // LED 开关
    DispatchCommand_stopVFStatus                        = 3009 ,    // 停止VF
    
    DispatchCommand_setPushStreamWLan                   = 3010 ,    // 设置推流的WIFI
    DispatchCommand_setPushStreamAdress                 = 3011 ,    // 设置推流的地址
    DispatchCommand_cameraRest                          = 3012 ,    // 相机重启
    DispatchCommand_setSystemWorkModel                  = 3013 ,    // 设置相机工作模式
    DispatchCommand_closeMachine                        = 3014 ,    // 相机关机
    
    
    DispatchCommand_deleteOneFile                       = 40,       // 删除某个资源
    DispatchCommand_deleteAllFiles                      = 41,       // 删除所有资源
    DispatchCommand_modifySSIdAndPwd                    = 42,       // 修改ssid 和密码
    DispatchCommand_formatDisk                          = 43,       // sd卡格式化
    DispatchCommand_systemReset                         = 44,       // 还原出厂设置
    
    DispatchCommand_getFWUploadPath                     = 45,       // 获取固件的上传地址
    DispatchCommand_updateFW                            = 46,       // 更新固件
    
    DispatchCommand_connectSocket                       = 47,       // 连接相机SOCKET
    DispatchCommand_startSensionSocket                  = 48,       // 开启会话SOCKET
    DispatchCommand_stopSensionSocket                   = 49,       // 关闭SOCKET
    DispatchCommand_autoStopMachineRecord               = 50,       // 10分钟自动停止录影
    DispatchCommand_setChannelCountry                   = 51,       // 设置国家码
    DispatchCommand_setPowerSave                        = 52,       // 自动休眠
    DispatchCommand_sendBitrateGop                      = 53,       // 发送码率GOP Size
    
    DispatchCommand_setUpdateMode                       = 53,       // 设置TB402进入升级模式
    DispatchCommand_setUpdateFileComplete               = 54,       // 文件传输完成
    
};


