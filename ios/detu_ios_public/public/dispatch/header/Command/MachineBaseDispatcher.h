//
//  MachineBaseDispatcher.h
//  DeTuZZN
//
//  Created by Seth on 16/11/30.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MachineBaseCommand.h"
#import "DispatchErrorHandle.h"


@interface MachineBaseDispatcher : NSObject


/**
 这是s twin 系列设备的规则
 */
typedef enum {
    PREMODE_MOVIE_PRE_START  = 0,  // rtsp 流已经打开
    MOVIE_RECORDING ,              // rtsp 流已经打开
    MOVIE_PRE_STOP ,   //(Got 2015 preview stop command)  关闭 rtsp流
    PLAYBACK,          //     进行一些设置
    PHOTO  = 4         //     HTTP 流打开
} PREMODE;


@property (nonatomic, copy) resultResponseBlock boolResponse;
// 取消命令
- (void)cancel ;
- (void)free ;
- (void)shouldDone ;

// 机器是否死机或者，断开WiFi
- (void)isMechineDisconnet ;
// TODO: 获取电量和卡容量
- (void)getBatteryAndElectric:(resultResponseBlock)responseBlock ;
// TODO: 进入预览之前的操作：S 请求标定 获取模式等等 、 TB402 连接socket 开启会话 获取标定等等
- (void)pushInpreview:(resultResponseBlock)responseBlock ;
// TODO: 已经进入预览
- (void)previewDidAppear:(resultResponseBlock)responseBlock ;
// TODO: 开启直播之前的设置：WIFI账号 密码 推流地址
- (void)setPushStreamWithSSID:(NSString *)ssid PWD:(NSString *)pwd PSAdress:(NSString *)psadress Res:(resultResponseBlock)responseBlock ;
// TODO: 设置标定
- (void)setSensor:(NSString *)sensor callBack:(resultResponseBlock)responseBlock ;
// TODO: 修改模式
- (void)changeMode:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 拍照
- (void)takePhoto:(resultResponseBlock)responseBlock ;
// TODO: 录像
- (void)recordStartOrStop:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 获取文件列表
- (void)showFileList:(resultResponseBlock)responseBlock ;
// TODO: 开关预览
- (void)openOrCloseLiveShow:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 录像分辨率
- (void)MediaRecordSize:(WIFI_APP_MOVIE_RECORD_SIZE)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 预览分辨率
- (void)MediaMovieLiveViewSize:(WIFI_APP_MOVIE_RECORD_SIZE)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 拍照分辨率
- (void)MediaCaptureSize:(WIFI_APP_PHOTO_SIZE)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置EV
- (void)setEV:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置WB
- (void)setWB:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置ISO
- (void)setISO:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置HDR
- (void)setHDR:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置WDR
- (void)setWDR:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置MIC
- (void)MediaMIC:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置循环录像
- (void)SetCyclicRec:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置录像分段时间
- (void)SetSegmentRec:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置定时录像
- (void)SetTimingRec:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置拍照质量
- (void)SetPhotographicQuality:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置视频质量
- (void)setVideoQuality:(NSInteger)mode callBack:(resultResponseBlock)responseBlock;
// TODO: 设置开机默认模式
- (void)SetDefaultMode:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置蜂鸣器
- (void)SetBeep:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置按键音
- (void)SetSoundRecord:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 获取相机版本
- (void)GetMachineVersion:(resultResponseBlock)responseBlock ;
// TODO: 设置连拍
- (void)SetPhotoButer:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置行车模式
- (void)SetTrafficMode:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置录制码率
- (void)MediaMovieRecordBitrate:(NSInteger)Bitrate callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置重力灵敏度
- (void)SetSensitityOfGravityInduction:(NSInteger)Bitrate callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置行车预览
- (void)SetShowLiveWhenTraffic:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置运动侦测
- (void)SetMotionDetect:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置实时流码率
- (void)MediaMovieLiveViewBitrate:(NSInteger)Bitrate callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置WIFI密码
- (void)MediaSetWifiPassword:(NSString*)password callBack:(resultResponseBlock)responseBlock ;
// TODO: 设置关机时间
- (void)MediaPowerOff:(POWEROFF_SETTING)mode callBack:(resultResponseBlock)responseBlock ;
// TODO: 删除单个文件
- (void)DeleteOneFile:(NSString*)filePath callBack:(resultResponseBlock)responseBlock ;
// TODO: 删除所有文件
- (void)DeleteAllFiles:(resultResponseBlock)responseBlock ;
// TODO: 获取电量
- (void)GetBattery:(resultResponseBlock)responseBlock ;
// TODO: 获取当前录制时间
- (void)GetNowRecordingTime:(resultResponseBlock)responseBlock ;
// TODO: 修改WIFI账号密码
- (void)ModifySSId:(NSString*)ssid andPwd:(NSString *)pwd callBack:(resultResponseBlock)responseBlock ;
// TODO: 格式化SDK
- (void)FormatDisk:(resultResponseBlock)responseBlock ;
// TODO: 重启相机
- (void)SystemReset:(resultResponseBlock)responseBlock ;
// TODO: 获取系统版本
- (void)GetSystemVersion:(resultResponseBlock)responseBlock ;
// TODO: 获取剩余空间
- (void)GetFreeSpace:(resultResponseBlock)responseBlock ;
// TODO: 设置当前模式
- (void)setCurrentMode:(WIFI_APP_MODE_CMD)model callBack:(resultResponseBlock)responseBlock ;
// TODO: 获取当前模式
- (void)getCurrentModel:(resultResponseBlock)responseBlock ;
// TODO: 获取ssid 和 密码
- (void)GetSSIDAndPwd:(resultResponseBlock)responseBlock ;
// TODO: 获取升级的路径
- (void)GetFWUploadPath:(resultResponseBlock)responseBlock ;
// TODO: 固件升级
- (void)UpdateFW:(resultResponseBlock)responseBlock ;
// TODO: 获取SD卡状态
- (void)GetSDCardState:(resultResponseBlock)responseBlock ;
// TODO: 设置光学防抖
- (void)SetAntisShake:(BOOL )abool CallBack:(resultResponseBlock)responseBlock ;
// TODO: 设置水印时间
- (void)SetDateWaterMark:(BOOL )abool CallBack:(resultResponseBlock)responseBlock ;
// TODO: 设置光源频率
- (void)SetSystemFreq:(WIFI_APP_FREQUENCY)mode CallBack:(resultResponseBlock)responseBlock ;
// TODO: 设置LED开关
- (void)SetLEDSwitch:(BOOL)abool CallBack:(resultResponseBlock)responseBlock ;
// TODO: amba停止会话
- (void)stopSessionOrStopSocket:(BOOL)abool callBack:(resultResponseBlock)responseBlock;
// TODO: amba开始会话
- (void)startSession:(resultResponseBlock)responseBlock;
// TODO: stop VF
- (void)stopVF:(resultResponseBlock)responseBlock;
// TODO: start VF
- (void)startVF:(resultResponseBlock)responseBlock;
// TODO: 设置WIFI制式
- (void)setWiFiChannel:(NSString *)mode callBack:(resultResponseBlock)responseBlock;
// TODO: 读取文件缩略图数据
- (void)getThumb:(NSString *)filePath callBack:(resultResponseBlock)responseBlock;
// TODO:  重启相机
- (void)restartCamera:(resultResponseBlock)responseBlock;
// TODO: 相机关机
- (void)closeMachine:(resultResponseBlock)responseBlock ;
// TODO: 进入相机相册
- (void)connectSocketAndGetSensorCallBack:(resultResponseBlock)responseBlock ;

//2017.5.26 新加命令
// TODO: 十分钟自动停止录影
- (void)SetAutoStopRecord:(BOOL)abool CallBack:(resultResponseBlock)responseBlock;
// TODO: 设置国家码
- (void)setChannelWithCountry:(WIFI_CHANNEL)mode CallBack:(resultResponseBlock)responseBlock;
// TODO: 设置待机休眠
- (void)setPowerSave:(NSString *)ninutes CallBack:(resultResponseBlock)responseBlock;
// TODO: 设置码率、GOPSize
- (void)sendBitrateGOPSize:(NSString *)BitrateGOPSize CallBack:(resultResponseBlock)responseBlock;
// TODO: 获取当前的存储模式
- (void)getCameraStorgetype:(resultResponseBlock)responseBlock;
@end
