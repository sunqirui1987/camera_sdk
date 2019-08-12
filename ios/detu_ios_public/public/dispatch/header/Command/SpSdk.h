//
//  SpSdk.h
//  spsdk
//
//  Created by qiruisun on 15/7/21.
//  Copyright (c) 2015年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SdkResponse.h"
#import "SpProtocol.h"


typedef void (^SdkResponseCallback)(SdkResponse *e);
typedef void (^SdkPathResponseCallback)(SdkPathResponse *e);
typedef void (^SdkValueResponseCallback)(SdkValueResponse *e);
typedef void (^SdkListResponseCallback)(SdkListResponse *e);
typedef void (^SdkSettingResponseCallback)(SdkSettingResponse *e);
typedef void (^SdkStringResponseCallback)(SdkStringResponse *e);
typedef void (^SdkSSIDAndPwdResponseCallback)(SdkSSIDAndPwdResponse *e);

@interface SpSdk : NSObject
//F4新添加切换模式  2016.7.11 如有冲突 
-(void)changeModePhotoOrMovie:(WIFI_APP_MODE_CMD)size withCallback:(SdkValueResponseCallback)callback;

/**
 *  连接或者关闭实时流
 *
 *  @param enable   able
 *  @param modeAble 预览之前设置为录制模式
 *  @param callback callback
 */
-(void)ConnectionOrCloseLiveShow:(BOOL)enable WithChangeMode:(BOOL)modeAble withCallback:(SdkPathResponseCallback)callback;
/**
 *  录制视频
 *
 *  @param enable   able
 *  @param modeAble 录制之前设置为录像模式
 *  @param callback callback
 */
-(void)MediaRecord:(BOOL)enable WithChangeMode:(BOOL)modeAble withCallback:(SdkPathResponseCallback)callback; 
/**
 *  拍照
 *
 *  @param modeAble 拍照之前设置为拍照模式
 *  @param callback callback
 */
-(void)MediaCaptureWithChangeMode:(BOOL)modeAble Call:(SdkPathResponseCallback)callback;
//拍照 设置尺寸
-(void)MediaCaptureSize:(WIFI_APP_PHOTO_SIZE)size withChangeMode:(BOOL)abool withCallback:(SdkValueResponseCallback)callback ;
//录制视频 设置尺寸
-(void)MediaRecordSize:(WIFI_APP_MOVIE_RECORD_SIZE)size withChangeMode:(BOOL)abool withCallback:(SdkPathResponseCallback)callback ;
//HDR设置
-(void)MediaHDR:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;
//WDR设置
-(void)MediaWDR:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;
//MIC设置
-(void)MediaMIC:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;
//音频开关
-(void)MediaAudio:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;
//实时预览的大小
-(void)MediaMovieLiveViewSize:(WIFI_APP_MOVIE_RECORD_SIZE)size withCallback:(SdkValueResponseCallback)callback;
//录制码速
-(void)MediaMovieRecordBitrate:(int)rate withCallback:(SdkValueResponseCallback)callback;
//实时流码率
-(void)MediaMovieLiveViewBitrate:(int)rate withCallback:(SdkValueResponseCallback)callback;
//设置wifi密码
-(void)MediaSetWifiPassword:(NSString*)password withCallback:(SdkValueResponseCallback)callback;
//POWEROFF_SETTING
-(void)MediaPowerOff:(POWEROFF_SETTING)setting withCallback:(SdkValueResponseCallback)callback;
//查询当前状态
-(void)MediaQueryCurrentStatus:(SdkSettingResponseCallback)callback;
//查询文件列表
-(void)MediaQueryFileList:(SdkListResponseCallback)callback;
//删除某个文件
-(void)DeleteOneFile:(NSString*)diskPath withCallback:(SdkValueResponseCallback)callback;
//删除所有文件
-(void)DeleteAllFiles:(SdkValueResponseCallback)callback;
//心跳包
-(void)HeartBeat:(SdkValueResponseCallback)callback;
//获取电量
-(void)GetBattery:(SdkValueResponseCallback)callback;
//设置时间戳
-(void)SetDateImPrint:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;
//获取当前录制时间
-(void)GetNowRecordingTime:(SdkValueResponseCallback)callback;
//tv制式
-(void)SetTVFormat:(int)format withCallback:(SdkValueResponseCallback)callback;
//修改ssid 和密码
-(void)ModifySSIdAndPwd:(NSString*)ssid pwd:(NSString*)pwd withCallback:(SdkValueResponseCallback)callback;
//sd卡格式化
-(void)FormatDisk:(SdkValueResponseCallback)callback;
//恢复出厂设置
-(void)SystemReset:(SdkValueResponseCallback)callback;
//固件版本号
-(void)GetSystemVersion:(SdkStringResponseCallback)callback;
//剩余空间
-(void)GetFreeSpace:(SdkStringResponseCallback)callback;
//设置曝光
-(void)SetEv:(int)ev withCallback:(SdkValueResponseCallback)callback;
//获取ssId和密码
-(void)GetSSIDAndPwd:(SdkSSIDAndPwdResponseCallback)callback;
//同步时间
-(void)SetDateAndTime:(NSDate*)date withCallback:(SdkValueResponseCallback)callback;
//获取固件的上传地址
-(void)GetFWUploadPath:(SdkStringResponseCallback)callback;
//更新固件
-(void)UpdateFW:(SdkValueResponseCallback)callback;
//获取sd卡状态
-(void)GetSDCardState:(SdkValueResponseCallback)callback;

//设置白平衡
-(void)SetWB:(int)wb withCallback:(SdkValueResponseCallback)callback;
//循环录像
- (void)SetCyclicRec:(int )cyclicRec withCallback:(SdkValueResponseCallback)callback;
//定时录像
- (void)SetTimingRec:(int )timingRec withCallback:(SdkValueResponseCallback)callback;
//设置ISO
-(void)SetISO:(int)iso withCallback:(SdkValueResponseCallback)callback;
//设置照片质量
-(void)SetPhotographicQuality:(int)pq withCallback:(SdkValueResponseCallback)callback;
//设置默认模式
-(void)SetDefaultMode:(int)mode withCallback:(SdkValueResponseCallback)callback;
//设置蜂鸣器
-(void)SetWarningtone:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;
//硬件型号序列号
-(void)GetMachineVersion:(SdkStringResponseCallback)callback;

//按键音
-(void)SetBeepMode:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;
//设置连拍
-(void)SetPhotoButer:(int)enable withCallback:(SdkValueResponseCallback)callback;
//获取model状态
-(void)GetCurrentModel:(SdkValueResponseCallback)callback;
//修改mode
-(void)ChangeMode:(int)mode withCallback:(SdkValueResponseCallback)callback;


//在使用sdk前，需要设置一下是否是sphere的协议，否表示设置为spheres的协议
-(void)SetIsSphere:(BOOL)isSphere;

//行车模式
-(void)SetTrafficMode:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;

//重力感应灵敏度
-(void)SetSensitityOfGravityInduction:(int)induction withCallback:(SdkValueResponseCallback)callback;

//光学防抖
-(void)SetAntisShake:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;

//日期水印
-(void)SetDateWaterMark:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;

//录音
-(void)SetSoundRecord:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;

//行车视频预览
-(void)SetShowLiveWhenTraffic:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;

//获取标注数据
-(void)GetSensorData:(SdkStringResponseCallback)callback;

// 设置标定数据
-(void)SetSensorData:(NSString *)sensor callback:(SdkValueResponseCallback)callback;

// -------------------------------- F4

// 获取电量
- (void)GetF4_Battery:(SdkValueResponseCallback)callback;

// 获取4 灯状态
- (void)GetF4_4sensorState:(SdkValueResponseCallback)callback;

// 获取已经拍摄的照片
- (void)GetHasTokenPhotoNum:(SdkValueResponseCallback)callback;

// 抓图
- (void)GetF4_Trigger_Rawenc:(SdkValueResponseCallback)callback;

// 设置光源频率
- (void)SetSystemFreq:(WIFI_APP_FREQUENCY)model :(SdkValueResponseCallback)callback;

// 获取卡总量
- (void)GetDiskSize:(SdkStringResponseCallback)callback;

// F4 设置照片的size
-(void)F4MediaCaptureSize:(WIFI_APP_PHOTO_SIZE)size withCallback:(SdkValueResponseCallback)callback;

// 关机
-(void)closeDevicewithCallback:(SdkValueResponseCallback)callback ;

// 同步
-(void)SetSystemSyn:(SYSTEM_SET_PREVIOUS_SYN_SWITCH)size withCallback:(SdkValueResponseCallback)callback;
//----------------------------------

// LED 开关 
-(void)SetLEDSwitch:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;

// 运动侦测
-(void)SetMotionDetect:(BOOL)enable withCallback:(SdkValueResponseCallback)callback;

@end


