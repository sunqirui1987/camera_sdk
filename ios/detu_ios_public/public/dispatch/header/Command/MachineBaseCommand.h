//
//  MachineBaseCommand.h
//  DeTuZZN
//
//  Created by Seth on 16/11/22.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SpSdk.h"
#import "MainDispatcher.h"
#import "DispatchErrorHandle.h"


@interface MachineBaseCommand : NSObject
@property (nonatomic, copy) resultResponseBlock responseBlock;
@property (nonatomic) dispatch_semaphore_t dispatch_semaphore_sigal;
// import！ 记录链式命令的完成结果，如果链式命令中间失败、后续不在继续发送指令，dispatchDone 方法返回失败回调
@property (nonatomic, assign) Dispatch_Error_Type dispatch_Error_Type;
// import！ 记录链式命令的命令号
@property (nonatomic, assign) DispatchCommand dispatch_command_index;
// import！ 记录链式命令的时间戳 用来识别是否超时
@property (nonatomic, assign) long dispatchCurrentCommandtimeSample;

- (BaseResponseBlock) registerCallBack ;
- (BaseResponseBlock) dispatchDone ;
- (void) waitForRes:(NSTimeInterval)sec ;
- (void) noWaitjustContinue ;
- (void) isOpereationCancel ;

//TODO:-----------------------------------------------------------------------------
//TODO:预览部分
- (BaseResponseBlock) getSensor ;

- (BaseResponseBlock) setSensor ;

- (BaseResponseBlock) getCurrentMode ;

- (BaseResponseBlock) setCurrentMode ;

- (BaseResponseBlock) setDate ;

- (BaseResponseBlock) recordStartOrStop:(BOOL)abool ;

- (BaseResponseBlock) takePhoto ;

- (BaseResponseBlock) getCurrentStatus ;

- (BaseResponseBlock) getFileList ;

- (BaseResponseBlock) openOrCloseLiveshow:(BOOL)abool ;

//TODO:-----------------------------------------------------------------------------
//TODO: 设置部分

//TODO: 录制分辨率
- (BaseResponseBlock) MediaRecordSize ;
//TODO: 拍照分辨率
- (BaseResponseBlock) MediaCaptureSize ;
- (BaseResponseBlock) MediaMovieLiveViewSize;
//TODO: HDR
- (BaseResponseBlock) MediaHDR:(BOOL)abool ;
//TODO: WDR
- (BaseResponseBlock) MediaWDR:(BOOL)abool ;
//TODO: WB
- (BaseResponseBlock) SetWB ;
//TODO: EV
- (BaseResponseBlock) SetEV ;
//TODO: ISO
- (BaseResponseBlock) SetISO ;
//TODO: MIC
- (BaseResponseBlock) MediaMIC:(BOOL)abool ;
//TODO: 循环录像
- (BaseResponseBlock) SetCyclicRec ;
//TODO: 缩时录影
- (BaseResponseBlock) SetTimingRec;
//TODO: 照片质量
- (BaseResponseBlock) SetPhotographicQuality ;
//TODO: 默认模式
- (BaseResponseBlock) SetDefaultMode ;
//TODO: 蜂鸣器
- (BaseResponseBlock) SetBeep:(BOOL)abool ;
//TODO: 录音设置
- (BaseResponseBlock) SetSoundRecord:(BOOL)abool ;
//TODO: 获取机器型号
- (BaseResponseBlock) GetMachineVersion ;
//TODO: 设置连拍
- (BaseResponseBlock) SetPhotoButer ;
//TODO: 设置行车记录模式
- (BaseResponseBlock) SetTrafficMode:(BOOL)abool ;
//TODO: 录制码速
- (BaseResponseBlock) MediaMovieRecordBitrate ;
//TODO: 重力灵敏度
- (BaseResponseBlock) SetSensitityOfGravityInduction ;
//TODO: 行车视频预览
- (BaseResponseBlock) SetShowLiveWhenTraffic ;
//TODO: 运动侦测
- (BaseResponseBlock) SetMotionDetect ;
//TODO: 实时流码率
- (BaseResponseBlock) MediaMovieLiveViewBitrate ;
//TODO: 设置wifi密码
- (BaseResponseBlock) MediaSetWifiPassword ;
//TODO: POWEROFF_SETTING
- (BaseResponseBlock) MediaPowerOff ;
//TODO: 删除某个文件
- (BaseResponseBlock) DeleteOneFile ;
//TODO: 删除所有文件
- (BaseResponseBlock) DeleteAllFiles ;
//TODO: 获取电量
- (BaseResponseBlock) GetBattery ;
//TODO: 获取当前录制时间
- (BaseResponseBlock) GetNowRecordingTime ;
//TODO: 修改ssid 和密码
- (BaseResponseBlock) ModifySSIdAndPwd ;
//TODO: sd卡格式化
- (BaseResponseBlock) FormatDisk ;
//TODO: 恢复出厂设置
- (BaseResponseBlock) SystemReset ;
//TODO: 固件版本号
- (BaseResponseBlock) GetSystemVersion ;
//TODO: 剩余空间
- (BaseResponseBlock) GetFreeSpace ;
//TODO: 获取ssId和密码
- (BaseResponseBlock) GetSSIDAndPwd ;
//TODO: 获取固件的上传地址
- (BaseResponseBlock) GetFWUploadPath ;
//TODO: 更新固件
- (BaseResponseBlock) UpdateFW ;
//TODO: 获取sd卡状态
- (BaseResponseBlock) GetSDCardState ;
//TODO: 光学防抖
- (BaseResponseBlock) SetAntisShake:(BOOL)enable ;
//TODO: 日期水印
- (BaseResponseBlock) SetDateWaterMark:(BOOL)enable ;
//TODO: 设置光源频率 WIFI_APP_FREQUENCY
- (BaseResponseBlock) SetSystemFreq ;
//TODO: LED 开关
- (BaseResponseBlock) SetLEDSwitch:(BOOL)enable ;


- (BaseResponseBlock) getVFState ;


//TODO: TWIN-A
// 连接SOCKET
- (BaseResponseBlock) connectSocket ;

// 视频质量
- (BaseResponseBlock) SetVideographicQuality;

// 获取相机的内置信息  型号 序列号
- (BaseResponseBlock) GetMachineInfo;

//视频分辨率合集
- (BaseResponseBlock) systemGetVideoResolutionOptions;

//视频质量合集
- (BaseResponseBlock) systemGetVideoQualityOptions;

//照片分辨率合集
- (BaseResponseBlock) systemDTPhotoSizeOptions;

//照片质量合集
- (BaseResponseBlock) systemPhotoQualityOptions;

//iso合集
- (BaseResponseBlock) systemGetISOOptions;

//光源频率合集
- (BaseResponseBlock) systemGetFreqOptions;

//蜂鸣器集合
- (BaseResponseBlock) systemSpkSwitchOptions;

//录像分段时长
- (BaseResponseBlock) systemdtVideoSplitTimeOptions;

//循环录影
- (BaseResponseBlock) systemLoopEncSwitchOptions;

//设置WIFI制式
- (BaseResponseBlock) setWiFiChannel;

//stop VF
- (BaseResponseBlock) stopVF;

//start VF
- (BaseResponseBlock) startVF;

//stop session
- (BaseResponseBlock) stopSessionOrStopSocket:(BOOL)abool;

//start session
- (BaseResponseBlock) startSession;

//读取文件缩略图数据
- (BaseResponseBlock) getThumb;

//TODO:直播相关
//设置推流的WIFI账号 密码
- (BaseResponseBlock) setPushStreamWLan ;

//设置推流的地址
- (BaseResponseBlock) setPushStreamAdress ;

//重启相机
- (BaseResponseBlock) restartCamera ;

//设置相机的工作模式
- (BaseResponseBlock) setSystemWorkModel ;

//相机关机
- (BaseResponseBlock) closeMachine ;

// 分段时间
- (BaseResponseBlock) SetSegmentTime;

// TODO: 十分钟自动停止录影
- (BaseResponseBlock) SetAutoStopRecord:(BOOL)enable ;

// 设置国家码
- (BaseResponseBlock) channelWithCountry ;

// 设置待机休眠
- (BaseResponseBlock) powerSave;

// 发送码率 GOPSize
- (BaseResponseBlock) sendBiteratGOPSize;

// 获取当前的存储模式
-(BaseResponseBlock)getCameraStorgetypeRes;
- (void)free ;

@end
