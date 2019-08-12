//
//  TwinaCommand.h
//  DeTuZZN
//
//  Created by Seth on 16/11/22.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import "MachineBaseCommand.h"

@interface TwinaCommand : MachineBaseCommand
@property (nonatomic, strong) AmbarellaSDK *ambsdk ;

- (void)shouldDone ;
- (void)cancel ;
// 连接SOCKET
- (BaseResponseBlock) connectSocket ;

// 视频质量
- (BaseResponseBlock) SetVideographicQuality;

// 获取相机的内置信息  型号 序列号
- (BaseResponseBlock) GetMachineInfo;

//获取视频分辨率合集
- (BaseResponseBlock) systemGetVideoResolutionOptions;

//获取视频质量合集
- (BaseResponseBlock) systemGetVideoQualityOptions;

//获取照片分辨率合集
- (BaseResponseBlock) systemDTPhotoSizeOptions;

//获取照片质量合集
- (BaseResponseBlock) systemPhotoQualityOptions;

//获取iso合集
- (BaseResponseBlock) systemGetISOOptions;

//获取光源频率合集
- (BaseResponseBlock) systemGetFreqOptions;

//获取蜂鸣器集合
- (BaseResponseBlock) systemSpkSwitchOptions;

//获取录像分段时长
- (BaseResponseBlock) systemdtVideoSplitTimeOptions;

//获取循环录影
- (BaseResponseBlock) systemLoopEncSwitchOptions;

//设置WIFI制式
- (BaseResponseBlock) setWiFiChannel;

// 分段时间
- (BaseResponseBlock) SetSegmentTime;

//查询VF状态
- (BaseResponseBlock) getVFState;

//stop VF
- (BaseResponseBlock) stopVF;

//start VF
- (BaseResponseBlock) startVF;

//stop session
- (BaseResponseBlock) stopSessionOrStopSocket:(BOOL)abool;

//读取文件缩略图数据
- (BaseResponseBlock) getThumb;

//相机关机
- (BaseResponseBlock)closeMachine ;

// 连接机器传输数据的接口并且设置平台信息:(固件升级之前的操作)
- (BaseResponseBlock)connectDataSocketAndSetClientInfo ;

// 停止固件升级的数据传输
- (void)stopUploadFireWare ;

// 设置国家码
- (BaseResponseBlock)setChannelWithCountry:(WIFI_CHANNEL)mode;

// 暂停缩略图下载
- (void)pauseLoadThumb;

// 设置待机休眠
- (BaseResponseBlock)powerSave;

// 固件升级
- (void)UpdateFW:(NSString *)filePath
             pro:(void(^)(int))progress
             res:(void(^)(BOOL))res ;

// 进入固件升级模式
- (BaseResponseBlock)setUpdateMode;

// 告诉相机传完数据了可以进行文件校验了
- (BaseResponseBlock)setCameraStartUpdateRes;
@end
