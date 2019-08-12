//
//  AmbarellaSDK.h
//  DeTuZZN
//
//  Created by lsq on 16/11/25.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AmbarellaCommand.h"

//相机数据变化，用通知获取
#define AMBARELLANOTIFY       @"AmbareLLA_Notify"

//三次连接socket失败，用通知获取
#define AMBARELLA_SOCKET_CONNECT_NOTIFY       @"AMBARELLA_SOCKET_CONNECT_NOTIFY"

#define NETCTRL_STR_DETU_EVBIAS             @"dt_evbias"
#define NETCTRL_STR_DETU_SHUTTER            @"dt_shutter"
#define NETCTRL_STR_DETU_BRIGHTNESS         @"dt_brightness"
#define NETCTRL_STR_DETU_SATURATION         @"dt_saturation"
#define NETCTRL_STR_DETU_CONTRAST           @"dt_contrast"
#define NETCTRL_STR_DETU_HUE                @"dt_hue"
#define NETCTRL_STR_DETU_SHARPNESS          @"dt_sharpness"
#define NETCTRL_STR_DETU_STOPRECORD         @"dt_long_time_record"      //  十分钟停止录影
#define NETCTRL_STR_DETU_WIFI_CHANNEL       @"dt_wifi_channel_country"  //  国家地区信道
#define NETCTRL_STR_DETU_POWER_SAVE         @"dt_power_save"            //  自动休眠
#define NETCTRL_STR_DETU_RTSP_INFO          @"dt_rtsp_info"             //  码率GOP 统计

// 固件版本1.0.2以上
#define AMBAREALLAHIGTPICTHUMBPATH      @"http://192.168.42.1:8989/get_thumb&type=jpg&format=jpg&filename=%@"
#define AMBAREALLHIGHMOVTHUMBPATH       @"http://192.168.42.1:8989/get_thumb&type=MP4&format=H264&filename=%@"

// 固件版本1.0.2以下
#define AMBAREALLAPICTHUMBPATH       @"http://192.168.42.1:8989/get_thumb&type=jpg&filename=%@"
#define AMBAREALLAMOVTHUMBPATH       @"http://192.168.42.1:8989/get_thumb&type=MP4&filename=%@"

#define GET_THUMB_TYPE_USE_SOCKET   0  // 缩略图使用SOCKET方式为1  HTTP为0

typedef void (^successBlock)(BOOL);
typedef void (^responseBlock)(BOOL,AmbarellaResponseModel *);
typedef void (^progressBlock)(int);

@interface AmbarellaSDK : NSObject
@property (nonatomic, assign) BOOL isCameraConnect;   // startSession连接状态
@property (nonatomic, assign) BOOL isCommandSocketConnect;   // 7878端口连接状态
@property (nonatomic, assign) BOOL isDataSocketConnect;      // 8787端口连接状态
@property (nonatomic, strong) NSString *ambarellaNotify;
@property (nonatomic, assign) int  cutSocket;

// 建立命令的socket连接
- (void)connectCommandSocket:(successBlock)block;
// 建立8787端口连接 接收缩略图数据或者上传大文件
- (void)connectDataSocketRes:(successBlock)block ;
// 连接直播
- (void)connectLiveSocket:(NSString *)host withHost:(successBlock)block;
// 关闭所有的socket连接
- (void)closeSocketConnect;
// 停止固件升级
- (void)stopUpFw;
// 页面退出时 清空buff
- (void)clearBuff;
// 获取当前录制时间
- (void)GetNowRecordingTime:(responseBlock)block;
// 获取标注数据
- (void)GetSensorData:(responseBlock)block;
// 设置客户端信息
- (void)setClntInfo:(responseBlock)block;
// 获取相机当前设置
- (void)systemGetAllCurrentSettings:(responseBlock)block;
// 获取相机信息
- (void)systemGetDeviceInfo:(responseBlock)block;
//获取WIFI信息
- (void)systemGetWiFiSetting:(responseBlock)block;
// 修改WIFI ssid和密码
- (void)setWiFiSSIDAndPassword:(NSString *)ssid andPassword:(NSString *)password result:(responseBlock)block;
// 关闭VF
- (void)stopVF:(responseBlock)block;
// 重置VF
- (void)resetVF:(responseBlock)block;
// 查询VF状态
- (void)getVFState:(responseBlock)block;
// 获取SD卡总内存
- (void)getSDTotalSpace:(responseBlock)block;
// 获取SD卡剩余内存
- (void)getSDFreeSpace:(responseBlock)block;
// SD卡初始化
- (void)formatSDCard:(responseBlock)block;
// 获取文件信息
- (void)getMediaInfofilePath:(NSString *)fileName result:(responseBlock)block;
// 获取电量
- (void)getBatteryLevel:(responseBlock)block;
// 获取温度
- (void)getTemperature:(responseBlock)block;
// 相机关机
- (void)closeMachine:(responseBlock)block;
// 开启会话
- (void)startSession:(responseBlock)block;
// 停止会话
- (void)stopSession:(responseBlock)block;
// 开启录像
- (void)startVideoRecord:(responseBlock)block;
// 停止录像
- (void)stopVideoRecord:(responseBlock)block;
// 拍照
- (void)takePhoto:(responseBlock)block;
// 获取sd卡中相册的数据列表
- (void)getMediaListing:(void(^)(NSMutableArray *arr))mediaListing;
// 列出文件列表
- (void)fileLs:(responseBlock)block;
// CD到目录
- (void)fileCd:(NSString *)param result:(responseBlock)block;
// 删除文件  param传数据格式:/tmp/SD0/DCIM/161202000/19475700.JPG
- (void)deleteFile:(NSString *)param result:(responseBlock)block;
// 获取文件缩略图信息
- (void)getThumb:(NSString *)filePath result:(responseBlock)block;
// 相机固件升级  fileUrl:文件路径  fileName:文件
- (void)updateAmbarellaFw:(NSString *)fileUrl pregressBlock:(progressBlock)pregressBlock success:(successBlock)success;
// 停止下载缩略图任务
- (void)pauseLoadThumb;
// 恢复下载缩略图任务
- (void)resumeLoadThumb;

// 推流设置
-(void)pushStreamSetting:(NSString *)ssid withPassword:(NSString *)password result:(responseBlock)block;
// 重启
- (void)restarStream:(responseBlock)block;
// 设置相机推流地址
- (void)setDevicePushStream:(NSString *)streampath result:(responseBlock)block;
// 开启推流
- (void)startRtspPush:(responseBlock)block;
// 关闭推流
- (void)stopRtspPush:(responseBlock)block;
// WIFI重启
- (void)wifiRestart:(responseBlock)block;
// 视频分辨率集合
- (void)systemGetVideoResolutionOptions:(responseBlock)block;
// 视频质量集合
- (void)systemGetVideoQualityOptions:(responseBlock)block;
// 照片分辨率集合
- (void)systemDTPhotoSizeOptions:(responseBlock)block;
// iso集合
- (void)systemGetISOOptions:(responseBlock)block;
// 照片质量集合
- (void)systemPhotoQualityOptions:(responseBlock)block;
// HDR集合
- (void)systemHDROptions:(responseBlock)block;
// WB集合
- (void)systemWBOptions:(responseBlock)block;
// 录音集合
- (void)systemMicSwitchOptions:(responseBlock)block;
// 录像分段时长集合
- (void)systemdtVideoSplitTimeOptions:(responseBlock)block;
// 光源频率集合
- (void)systemPowerFreqOptions:(responseBlock)block;
// 按键音集合
- (void)systemSpkSwitchOptions:(responseBlock)block;
// 循环录影
- (void)systemLoopEncSwitchOptions:(responseBlock)block;
// WIFI开关集合
- (void)systemWiFiSwitchOptions:(responseBlock)block;
// 相机工作模式集合
- (void)systemWorkModelOptions:(responseBlock)block;
// 推流声音集合
- (void)systemLiveAudioOptions:(responseBlock)block;
// 测光集合
- (void)systemMeteringOptions:(responseBlock)block;
// 设置时间戳
- (void)SetDateImPrint:(NSString *)param result:(responseBlock)block;
// 设置视频分辨率
- (void)setSystemVideoResolution:(NSString *)param result:(responseBlock)block;
// 设置视频质量
- (void)setSystemVideoQuality:(NSString *)param result:(responseBlock)block;
// 设置照片分辨率
- (void)setSystemDTPhotoSize:(NSString *)param result:(responseBlock)block;
// 设置iso
- (void)setSystemISO:(NSString *)param result:(responseBlock)block;
// 设置照片质量
- (void)setSystemPhotoQuality:(NSString *)param result:(responseBlock)block;
// 设置HDR
- (void)setSystemHDR:(NSString *)param result:(responseBlock)block;
// 设置WB
- (void)setSystemWB:(NSString *)param result:(responseBlock)block;
// 设置录音
- (void)setSystemMicSwitch:(NSString *)param result:(responseBlock)block;
// 设置录像分段时长
- (void)setSystemdtVideoSplitTime:(NSString *)param result:(responseBlock)block;
// 设置按键音
- (void)setSystemSpkSwitch:(NSString *)param result:(responseBlock)block;
// 设置循环录影
- (void)setSystemLoopEncSwitch:(NSString *)param result:(responseBlock)block;
// 设置WIFI开关
- (void)setSystemWiFiSwitch:(NSString *)param result:(responseBlock)block;
// 设置相机工作模式
- (void)setSystemWorkModel:(NSString *)param result:(responseBlock)block;
// 设置推流声音
- (void)setSystemLiveAudio:(NSString *)param result:(responseBlock)block;
// 设置WiFi制式
- (void)setSystemWiFiModel:(NSString *)param result:(responseBlock)block;
// 设置测光模式
- (void)setMeteringModel:(NSString *)param result:(responseBlock)block;
// 设置光源频率
- (void)setPowerFreqModel:(NSString *)param result:(responseBlock)block;
//恢复出厂设置
- (void)SystemReset:(responseBlock)block;
// 10分钟自动停止录影
- (void)autoStopMachineRecordAfterTenMinuters:(BOOL)abool result:(responseBlock)block;
//设置国家码
- (void)setChannelWithCountry:(NSString *)param result:(responseBlock)block;
//待机自动休眠
- (void)setPowerSave:(NSString *)param result:(responseBlock)block;

//TODO: 新版固件升级
// 1. 进入固件升级模式
- (void)setUpdateMode:(NSString *)filename result:(responseBlock)block;

// 2. 告诉相机传完数据了可以进行文件校验了
- (void)setCameraStartUpdateRes:(responseBlock)block;

//设置码率、GOPSize
-(void)sendBitrateGOPSize:(NSString *)param result:(responseBlock)block;

// 获取当前的存储模式
-(void)getCameraStorgetypeRes:(responseBlock)block;
@end
