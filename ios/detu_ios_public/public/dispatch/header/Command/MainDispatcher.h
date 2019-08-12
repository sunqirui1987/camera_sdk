//
//  MainDispatcher.h
//  DeTuZZN
//
//  Created by Seth on 16/11/22.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CameraInfo.h"
#import "SpSdk.h"
#import "AmbarellaSDK.h"
#import "DTDeviceManager.h"
#import "DispatchErrorHandle.h"
#import "DispatchProtocal.h"
//#define DISPATCHSWTICH  100      //

//TODO: weak self and strong self
#define WeakSelf        __weak typeof(self) _weakSelf = self;
#define StrongSelf      __strong typeof(_weakSelf)_strongSelf = _weakSelf;

#define subWeakSelf     __weak typeof(_strongSelf)_subWeakSelf = _strongSelf;
#define subStrongSelf   __strong typeof(_subWeakSelf)_subStrongSelf = _subWeakSelf;

#define DISPATCH_VERSION            @"2.0.1"   // 版本号
#define COMMAND_SECOND              7       // 普通命令超时时间
#define LONG_COMMAND_SECOND         10      // 超长命令超时时间
#define LONG_LONG_COMMAND_SECOND    30      // 超超长命令超时时间
#define SAFERECONNECTCOUNT          2       // 命令重发次数

/**
 *  自定义Log，可配置开关（用于替换Dispatch_Log）
 */
#define Dispatch_Log(format,...) CustomLog(__FUNCTION__,__LINE__,format,##__VA_ARGS__)

//#define Dispatch_Log   Dispatch_Log

@class MachineBaseCommand;
@interface MainDispatcher : NSObject

/**
 *  @abstract  Dispatch  Status
 *  Structure of scheduling program
 */
typedef struct DispatchStatus {
    
    Dispatch_ApplicationType    dispatchApplicationType ;       // APP种类
    Dispatch_MachineType        dispatchMachineType ;           // 相机机器种类
    CTCallStates                cTCallStates ;                  // 电话机的状态
    ApplicationStatus           applicationStatus ;             // 应用的状态
    bool                        isSocketConnect ;               // socket的链接状态
    bool                        isCameraConnect ;               // camera的链接状态：会话的状态
    
}DispatchStatus;


typedef MachineBaseCommand *(^BaseResponseBlock)();
typedef void (^resultResponseBlock)(Dispatch_Error_Type, DispatchCommand);


// TODO: 相机的数据源
///<  相机的数据源
@property (atomic, strong) CameraInfo * cameraInfo ;



// TODO: 通知
///<  WIFI异常回调
@property (nonatomic, copy) void (^notifyBlock)(NSString *currentDevice, NSString * previousDevice) ;
///<  相机协议通知
@property (nonatomic, copy) void (^cmeraNotifyBlock)(NSDictionary *info) ;
///<  1.APP进入前后台 2.电话响应的 通知
@property (nonatomic, copy) void (^applicationStateNotifyBlock)() ;



// TODO: 相关记录、以及数据类型
@property (atomic, assign) struct DispatchStatus dispatchStatus ;
@property (atomic, assign) DispatchOperationType dispatchOperationType ;


// TODO: 相机命令同步线程
@property (atomic, strong, readwrite) dispatch_queue_t dispatchQueue_serial ;
@property (atomic, strong, readwrite) NSOperationQueue * operationQueue ;
@property (atomic, strong, readwrite) NSOperationQueue * operationThumbQueue ;



+ (instancetype)shareInstance ;
- (void)monitorWIFI ;           // 相机WI-FI 监控
- (void)config ;
- (void)reConfig ;              // 相机Wi-Fi 切换后重新config（自动调用）
- (void)cancel ;  // 取消命令（取消正在进行的命令时调用）
- (void)shouldDone ;            // 取消调度器里面所有的命令并且关闭socket（相机异常时调用->关闭socket）
- (void)suspendQueryThumbnial ; // 挂起获取缩略图的命令（场景：需要优先调用其他的命令时）
- (void)resumeQueryThumbnial ;  // 恢复获取缩略图的命令
- (void)pauseLoadThumb ;        // 暂停缩略图下载
//------------------------------------------------------------------
//------------------------------------------------------------------

/**
 *  固件升级
 */


//------------------------------------------------------------------
//------------------------------------------------------------------

/**
 *  自定义Log
 *  外部可直接调用 Dispatch_Log
 *
 *  @param func         方法名
 *  @param lineNumber   行号
 *  @param format       Log内容
 *  @param ...          个数可变的Log参数
 */
void CustomLog(const char *func, int lineNumber, NSString *format, ...);

/**
 * Log 输出开关 (默认关闭)
 */
+ (void)openLog:(BOOL)enable;

#pragma mark ------------------------------------------------------------------------------------------------------------------------------------

/**
 * number  1.
 * do      连接机器并且获取标定
 * return: 设置结果 命令号
 */
- (void)connectMachineAndGetSensorCallBack:(resultResponseBlock)responseBlock;

/**
 * number  2.
 * do      判断是否能进入预览(设置时间 、获取硬件的相关信息 、获取模式 等等)
 * return: 设置结果 命令号
 */
- (void)pushInpreview:(resultResponseBlock)responseBlock ;

/**
 * number  75.
 * do      获取卡容量和电量
 * return: 设置结果 命令号
 */
- (void)getBatteryAndElectric:(resultResponseBlock)responseBlock ;

/**
 * number  3.
 * do      预览流将要出来
 *         获取相机的相关参数，获取流的过程中不建议再去发送命令获取参数，导致相机IO消耗过高。导致宕机
 * return: 设置结果 命令号
 */
- (void)previewDidAppear:(resultResponseBlock)responseBlock ;

/**
 * number  4.
 * do      开启直播之前的设置：WIFI账号 密码 推流地址 重启等等...（TB402：需要先运行方法 1）
 * param:  ssid:WIFI账号 pwd:WiFi密码 psadress:推流地址
 * return: 设置结果 命令号
 */
- (void)setPushStreamWithSSID:(NSString *)ssid PWD:(NSString *)pwd PSAdress:(NSString *)psadress Res:(resultResponseBlock)responseBlock ;


#pragma mark ------------------------------------------------------------------------------------------------------------------------------------

/**
 * number  5.
 * do      关闭相机：目前只支持安霸协议
 * return: 设置结果 命令号
 */
- (void)closeMachine:(resultResponseBlock)responseBlock ;

/**
 * number  6.
 * do      获取电量
 * return: 设置结果 命令号
 */
- (void)getBattery:(resultResponseBlock)responseBlock ;
/**
 * number  7.
 * do      展示相机列表
 * return: 设置结果 命令号
 */
- (void)showFileList:(resultResponseBlock)responseBlock ;

/**
 * number  8.
 * do      设置相机标定参数
 * param:  sensor
 * return: 设置结果 命令号
 */
- (void)setSensor:(NSString *)sensor callBack:(resultResponseBlock)responseBlock ;

/**
 * number  9.
 * do      切换相机模式 当前模式有：
 *         WIFI_APP_MODE_MOVIE,
 *         WIFI_APP_MODE_PHOTO,
 *         WIFI_APP_MODE_PLAYBACK
 * params: mode
 * return: 设置结果 命令号
 */
- (void)changeMode:(WIFI_APP_MODE_CMD)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  10.
 * do      拍摄照片
 * return: 设置结果 命令号
 */
- (void)takePhoto:(resultResponseBlock)responseBlock ;

/**
 * number  11.
 * do      录制视频
 * params: start or shut
 * return: 设置结果 命令号
 */
- (void)recordStartOrStop:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

/**
 * number  12.
 * do      开关预览流
 * params: open or close
 * return: 设置结果 命令号
 */
- (void)openOrCloseLiveShow:(BOOL)abool callBack:(resultResponseBlock)responseBlock;

/**
 * number  13.
 * do      设置录制分辨率
 * params: 分辨率视机型而定
 * return: 设置结果 命令号
 */
- (void)setRecordSize:(WIFI_APP_MOVIE_RECORD_SIZE)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  14.
 * do      设置预览分辨率
 * params: 视频分辨率视机型而定
 * return: 设置结果 命令号
 */
- (void)MediaMovieLiveViewSize:(WIFI_APP_MOVIE_RECORD_SIZE)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  15.
 * do      设置照片分辨率
 * params: 分辨率视机型而定
 * return: 设置结果 命令号
 */
- (void)setCaptureSize:(WIFI_APP_PHOTO_SIZE)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  16.
 * do      设置EV
 * params: -2  -1  0  1  2
 * return: 设置结果 命令号
 */
- (void)setEV:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  17.
 * do      设置WB
 * params: auto sunnight cloudy tungsten Fluorscent
 * return: 设置结果 命令号
 */
- (void)setWB:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  18.
 * do      设置ISO
 * params: auto 100 200 400 800
 * return: 设置结果 命令号
 */
- (void)setISO:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  19.
 * do      设置HDR
 * params: open or close
 * return: 设置结果 命令号
 */
- (void)setHDR:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

/**
 * number  20.
 * do      设置WDR
 * params: open or close
 * return: 设置结果 命令号
 */
- (void)setWDR:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

/**
 * number  21.
 * do      设置MIC
 * params: open or close
 * return: 设置结果 命令号
 */
- (void)mediaMIC:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

/**
 * number  22.
 * do      循环录影
 * params: turn off   3min   5min   10min
 * return: 设置结果 命令号
 */
- (void)setCyclicRec:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  23.
 * do      设置录像分段时间
 * params: 3min   5min   10min
 * return: 设置结果 命令号
 */
- (void)SetSegmentRec:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;
/**
 * number  24.
 * do      设置缩时录影
 * params: 关闭、1S、5S、10S、30S、1MIN、5MIN、10MIN、30MIN，1H、2H、3H、1DAY
 * return: 设置结果 命令号
 */
- (void)setTimingRec:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  25.
 * do      设置照片质量
 * params: High     Medium     Low
 * return: 设置结果 命令号
 */
- (void)setPhotographicQuality:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  26.
 * do      设置视频质量
 * params: High     Medium     Low
 * return: 设置结果 命令号
 */
- (void)setVideoQuality:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  27.
 * do      开机默认模式
 * params: photo    video   playback
 * return: 设置结果 命令号
 */
- (void)setDefaultMode:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  28.
 * do      设置蜂鸣器
 * params: open or close
 * return: 设置结果 命令号
 */
- (void)setBeep:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

/**
 * number  29.
 * do      设置录音
 * params: open or close
 * return: 设置结果 命令号
 */
- (void)setSoundRecord:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

/**
 * number  30.
 * do      获取机器序列号（联永只能获取到序列号） (安霸可以获取固件版本、序列号)
 * return: 设置结果 命令号
 */
- (void)getMachineVersion:(resultResponseBlock)responseBlock ;

/**
 * number  31.
 * do      获取固件版本号（联永独用）
 * return: 设置结果 命令号
 */
- (void)GetSystemVersion:(resultResponseBlock)responseBlock ;

/**
 * number  32.
 * do      设置连拍
 * params: turn off     3min   5min    10min
 * return: 设置结果 命令号
 */
- (void)setPhotoButer:(NSInteger)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  33.
 * do      设置行车模式
 * params: open or close
 * return: 设置结果 命令号
 */
- (void)setTrafficMode:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;


/**
 * number  34.
 * do      amba停止会话and断开socket
 * return: 设置结果 命令号
 */
- (void)stopSessionOrStopSocket:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

/**
 * number  35.
 * do      amba停止VF
 * return: 设置结果 命令号
 */
- (void)stopVF:(resultResponseBlock)responseBlock ;

/**
 * number  36.
 * do      amba重置VF
 * return: 设置结果 命令号
 */
- (void)startVF:(resultResponseBlock)responseBlock ;

/**
 * number  37.
 * do      amba设置WIFI制式2.4G,5.8G
 * params: 2.4 == 0 or 5.8 == 61
 * return: 设置结果 命令号
 */
- (void) setWiFiChannel:(NSString *)mode callBack:(resultResponseBlock)responseBlock;

/**
 * number  38.
 * do      amba读取文件缩略图数据
 * params: filePath
 * return: 设置结果 命令号
 */
- (void) getThumb:(NSString *)filePath callBack:(resultResponseBlock)responseBlock;

/**
 * number  39.
 * do      关闭相机
 * return: 设置结果 命令号
 */
- (void)closeMachine:(resultResponseBlock)responseBlock;

/**
 * number  40.
 * do      重启
 * return: 设置结果 命令号
 */
- (void)restartCamera:(resultResponseBlock)responseBlock ;

/**
 * number  41.
 * do      录制码率
 * params: Bitrate ?????（参数待收集）
 * return: 设置结果 命令号
 */
- (void)MediaMovieRecordBitrate:(NSInteger)Bitrate callBack:(resultResponseBlock)responseBlock ;

/**
 * number  42.
 * do      重力灵敏度
 * params: induction ?????（参数待收集）
 * return: 设置结果 命令号
 */
- (void)SetSensitityOfGravityInduction:(NSInteger)induction callBack:(resultResponseBlock)responseBlock ;

/**
 * number  43.
 * do      行车开启预览
 * params: yer or no
 * return: 设置结果 命令号
 */
- (void)SetShowLiveWhenTraffic:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

/**
 * number  44.
 * do      运动侦测
 * params: yer or no
 * return: 设置结果 命令号
 */
- (void)SetMotionDetect:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

/**
 * number  45.
 * do      实时流码率
 * return: 设置结果 命令号
 */
- (void)MediaMovieLiveViewBitrate:(NSInteger)Bitrate callBack:(resultResponseBlock)responseBlock ;

/**
 * number  46.
 * do      设置WIFI密码
 * params: password
 * return: 设置结果 命令号
 */
- (void)MediaSetWifiPassword:(NSString*)password callBack:(resultResponseBlock)responseBlock ;

/**
 * number  47.
 * do      关机时间（联永可以设置关机时间，安霸是立即关机）
 * params: mode POWER_ON, POWER_3MIN, POWER_5MIN, POWER_10MIN, POWEROFF_SETTING_MAX
 * return: 设置结果 命令号
 */
- (void)MediaPowerOff:(POWEROFF_SETTING)mode callBack:(resultResponseBlock)responseBlock ;

/**
 * number  48.
 * do      删除单个文件
 * params: mode filePath（文件名）
 * return: 设置结果 命令号
 */
- (void)DeleteOneFile:(NSString*)filePath callBack:(resultResponseBlock)responseBlock ;

/**
 * number  49.
 * do      删除所有文件
 * return: 设置结果 命令号
 */
- (void)DeleteAllFiles:(resultResponseBlock)responseBlock ;

/**
 * do      获取电量
 * return: 设置结果 命令号
 */
- (void)GetBattery:(resultResponseBlock)responseBlock ;

/**
 * number  50.
 * do      获取当前录制的时间
 * return: 设置结果 命令号
 */
- (void)GetNowRecordingTime:(resultResponseBlock)responseBlock ;

/**
 * number  51.
 * do      修改ssid以及密码
 * params: ssid pwd
 * return: 设置结果 命令号
 */
- (void)ModifySSId:(NSString*)ssid andPwd:(NSString *)pwd callBack:(resultResponseBlock)responseBlock ;

/**
 * number  52.
 * do      格式化SD卡
 * return: 设置结果 命令号
 */
- (void)FormatDisk:(resultResponseBlock)responseBlock ;

/**
 * number  53.
 * do      系统重置（恢复出厂设置）
 * return: 设置结果 命令号
 */
- (void)SystemReset:(resultResponseBlock)responseBlock ;

/**
 * number  54.
 * do      获取卡剩余容量
 * return: 设置结果 命令号
 */
- (void)GetFreeSpace:(resultResponseBlock)responseBlock ;

/**
 * number  55.
 * do      设置当前的模式
 * return: 设置结果 命令号
 */
- (void)setCurrentMode:(WIFI_APP_MODE_CMD)model callBack:(resultResponseBlock)responseBlock ;

/**
 * number  56.
 * do      获取当前的模式
 * return: 设置结果 命令号
 */
- (void)getCurrentMode:(resultResponseBlock)responseBlock ;

/**
 * number  57.
 * do      获取ssid以及密码
 * return: 设置结果 命令号
 */
- (void)GetSSIDAndPwd:(resultResponseBlock)responseBlock ;

/**
 * number  58.
 * do      获取获取卡状态
 * return: 设置结果 命令号
 */
- (void)GetSDCardState:(resultResponseBlock)responseBlock ;

/**
 * number  59.
 * do      光学防抖
 * params: YES NO
 * return: 设置结果 命令号
 */
- (void)SetAntisShake:(BOOL )abool CallBack:(resultResponseBlock)responseBlock ;

/**
 * number  60.
 * do      设置日期水印
 * params: YES NO
 * return: 设置结果 命令号
 */
- (void)SetDateWaterMark:(BOOL )abool CallBack:(resultResponseBlock)responseBlock ;

/**
 * number  61.
 * do      设置光源频率
 * params: YES NO
 * return: 设置结果 命令号
 */
- (void)SetSystemFreq:(WIFI_APP_FREQUENCY)mode CallBack:(resultResponseBlock)responseBlock ;

/**
 * number  62.
 * do      设置LED灯
 * params: YES NO
 * return: 设置结果 命令号
 */
- (void)SetLEDSwitch:(BOOL)abool CallBack:(resultResponseBlock)responseBlock ;

/**
 * number  63.
 * type    sphere
 * do      获取固件升级路径
 * return: 设置结果 命令号
 */
- (void)GetFWUploadPath:(resultResponseBlock)responseBlock ;

/**
 * number  64.
 * type    sphere
 * do      固件升级路径
 * return: 设置结果 命令号
 */
- (void)UpdateFW:(resultResponseBlock)responseBlock ;


// TODO: 2017.5.26新加命令

/**
 * number  65.
 * type    amba
 * do      设置10分钟自动停止录影
 * params: YES NO
 * return: 设置结果 命令号
 * time    2017.5.26
 */
- (void)SetAutoStopRecord:(BOOL)abool CallBack:(resultResponseBlock)responseBlock ;


/**
 * number  66.
 * do      amba开始会话
 * return: 设置结果 命令号
 * tips:   补充命令
 */
- (void)startSession:(resultResponseBlock)responseBlock;

/**
 * number  67.
 * type    amba
 * do      国家码信道设置
 * return: 设置结果 命令号
 * time    2017.6.20
 */
-(void)setChannelWithCountry:(NSInteger)mode callBack:(resultResponseBlock)responseBlock;


#pragma mark - 固件升级 ----------------------
#pragma mark - 固件升级 ----------------------
/**
 * number  68.
 * type    amba
 * do      固件升级路径
 * return: 设置结果 命令号
 */
- (void)UpdateFW:(NSString *)filePath
             pro:(void(^)(int))progress
             res:(void(^)(BOOL))res ;

/**
 * number  69.
 * do      连接机器传输数据的接口并且设置平台信息:(固件升级之前的操作)
 * return: 设置结果 命令号
 */
- (void)connectDataSocketAndSetClientInfoCallBack:(resultResponseBlock)responseBlock;


/**
 * number  70.
 * do      停止固件升级的数据传输
 * return: 设置结果 命令号
 */
- (void)stopUploadFireWare;

/**
 * number  71.
 * type    amba
 * do      设置进入待机休眠时间
 * return: 设置结果 命令号
 * time    2017.6.20
 */
- (void)setPowerSave:(NSString *)minutes callBack:(resultResponseBlock)responseBlock;

/**
 * number  72.
 * type    amba
 * do      进入固件升级模式
 * @prama  filename : 文件名
 * return: 设置结果 命令号
 * time    2017.6.27
 */

- (void)setUpdateMode:(NSString *)filename callBack:(resultResponseBlock)responseBlock;

/**
 * number  73.
 * type    amba
 * do      告诉相机传完数据了可以进行文件校验
 * return: 设置结果 命令号
 * time    2017.6.27
 */
- (void)setCameraStartUpdateRes:(resultResponseBlock)responseBlock;

/**
 * number  74.
 * type    amba
 * do      收到播放器bitrate GopSize,发送给相机
 * return: 设置结果 命令号
 * time    2017.6.27
 */
- (void)sendBitrateAndGOPSize:(NSString *)Bitrate  GOPSize:(NSString *)gop callBack:(resultResponseBlock)responseBlock;

/**
 * number  75.
 * type    amba
 * do      获取当前相机的存储模式
 * return: 设置结果 命令号
 * time    2017.8.17
 */
- (void)getCameraStorgetypeRes:(resultResponseBlock)responseBlock;
@end
