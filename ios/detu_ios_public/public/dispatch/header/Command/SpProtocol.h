//
//  SpProtocol.h
//  spsdk
//
//  Created by qiruisun on 15/7/21.
//  Copyright (c) 2015年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProtocolData.h"
#import "RequestPotocol.h"



//照片尺寸
typedef NS_ENUM(NSInteger, WIFI_APP_PHOTO_SIZE)
{
    PHOTO_SIZE_12M,
    PHOTO_SIZE_10M,
    PHOTO_SIZE_8M,
    PHOTO_SIZE_5M,
    PHOTO_SIZE_3M,
    PHOTO_SIZE_2MHD,
    PHOTO_SIZE_VGA,
    PHOTO_SIZE_1M,
    PHOTO_SIZE_ID_MAX
};

////视频大小
//typedef NS_ENUM(NSInteger, WIFI_APP_MOVIE_RECORD_SIZE){
//    MOVIE_SIZE_1080P, // 1920 x 1080
//    MOVIE_SIZE_720P, // 1280 x 720
//    MOVIE_SIZE_WVGA, // 854 x 480
//    MOVIE_SIZE_VGA, // 640 x 480
//    MOVIE_SIZE_1440P, // 1440 x 1080 with DAR.
//};

//视频大小
typedef NS_ENUM(NSInteger, WIFI_APP_MOVIE_RECORD_SIZE){
    //    MOVIE_SIZE_1440_1080, // 1920 x 1080
    //    MOVIE_SIZE_848_636, // 1280 x 720
    //    MOVIE_SIZE_640_480 // 854 x 480
//    MOVIE_SIZE_FRONT_2880x2160P24, //UHD P24
//    MOVIE_SIZE_FRONT_2560x1440P30, //QHD P30
//    MOVIE_SIZE_FRONT_2304x1296P30, //3MHD P30
//    MOVIE_SIZE_FRONT_1920x1080P96, //FHD
//    MOVIE_SIZE_FRONT_1920x1080P60, //FHD
//    MOVIE_SIZE_FRONT_1920x1080P30, //FHD
//    MOVIE_SIZE_FRONT_1280x720P120, //HD
//    MOVIE_SIZE_FRONT_1280x720P60, //HD
//    MOVIE_SIZE_FRONT_1280x720P30,  //HD
//    MOVIE_SIZE_FRONT_848x480P30,   //WVGA
//    MOVIE_SIZE_FRONT_640x480P240,   //VGA
//    MOVIE_SIZE_FRONT_640x480P30,   //VGA
//    MOVIE_SIZE_FRONT_320x240P30,   //QVGA
//    MOVIE_SIZE_FRONT_TWIN_2880x1440=26,
//    MOVIE_SIZE_FRONT_TWIN_2160x1080=13,
//    MOVIE_SIZE_FRONT_TWIN_1440x7200=27,
//    MOVIE_SIZE_FRONT_960x720P120=100,  //HD
//    MOVIE_SIZE_FRONT_960x720P60,   //HD
//    MOVIE_SIZE_FRONT_960x720P30,   //HD
    
    
    /* Sps  012345678  UI显示正常 16:9(宽高比)
     MOVIE_SIZE_2880x2160P24,
     MOVIE_SIZE_1920x1440P30,
     MOVIE_SIZE_1728x1296P30,
     MOVIE_SIZE_1440x1080P96,
     MOVIE_SIZE_1440x1080P60,
     MOVIE_SIZE_1440x1080P30,
     MOVIE_SIZE_960x720P120,
     MOVIE_SIZE_960x720P60,
     MOVIE_SIZE_960x720P30,
     */
    /* TB401  13 26 27  UI显示 16:9(宽高比)
     MOVIE_SIZE_2880x1440P30, 26
     MOVIE_SIZE_2160x1080P30, 13
     MOVIE_SIZE_1440x720P30, 27
     */
    
    /* F4  0 1 4  UI显示 16:9(宽高比)
     MOVIE_SIZE_2880x2160P24,	0
     MOVIE_SIZE_1920x1440P30,	1
     MOVIE_SIZE_1440x1080P60,	4
     */
    
    
    /* F4  0 1 4  UI显示 16:9(宽高比)
     MOVIE_SIZE_2880x2160P24,	0
     MOVIE_SIZE_1920x1440P30,	1
     MOVIE_SIZE_1440x1080P60,	4
     */
    
    MOVIE_SIZE_FRONT_2880x2160P24 = 0, //UHD P24	0
    MOVIE_SIZE_FRONT_2560x1440P30 = 1, //QHD P30	1
    MOVIE_SIZE_FRONT_2304x1296P30 = 2, //3MHD P30	2
    MOVIE_SIZE_FRONT_1920x1080P96 = 3, //FHD	3
    MOVIE_SIZE_FRONT_1920x1080P60 = 4, //FHD	4
    MOVIE_SIZE_FRONT_1920x1080P30 = 5, //FHD	5
    MOVIE_SIZE_FRONT_1280x720P120 = 6, //HD	6
    MOVIE_SIZE_FRONT_1280x720P60 = 7, //HD	7
    MOVIE_SIZE_FRONT_1280x720P30 = 8,  //HD	8
    MOVIE_SIZE_FRONT_848x480P30 = 9,   //WVGA	9
    MOVIE_SIZE_FRONT_640x480P240 = 10,   //VGA	10
    MOVIE_SIZE_FRONT_640x480P30,   //VGA	11
    MOVIE_SIZE_FRONT_320x240P30,   //QVGA	12
    MOVIE_SIZE_DUAL_1920x1080P30_1920x1080P30, //FHD FHD	13
    MOVIE_SIZE_CLONE_1920x1080P30_1920x1080P30, //FHD FHD	14
    MOVIE_SIZE_CLONE_1920x1080P30_1280x720P30,  //FHD HD	15
    MOVIE_SIZE_CLONE_2560x1440P30_848x480P30, //QHD WVGA	16
    MOVIE_SIZE_CLONE_2304x1296P30_848x480P30, //3MHD WVGA	17
    MOVIE_SIZE_CLONE_1920x1080P60_848x480P30, //FHD WVGA	18
    MOVIE_SIZE_CLONE_1920x1080P60_640x360P30, //FHD VGA	19
    MOVIE_SIZE_CLONE_1920x1080P30_848x480P30, //FHD WVGA	20
    MOVIE_SIZE_CLONE_2048x2048P30_480x480P30 = 21,
    MOVIE_SIZE_CLONE_1280x720P30_1280x720P30, //HD HD	22
    MOVIE_SIZE_CLONE_848x480P30_848x480P30,   //WVGA WVGA	23
    MOVIE_SIZE_CLONE_640x480P30_640x480P30,   //VGA VGA	24
    MOVIE_SIZE_CLONE_320x240P30_320x240P30,   //QVGA QVGA	25
    
    
    MOVIE_SIZE_DUAL_2880x1440P30_2880x1440P30, //FHD FHD	26
    MOVIE_SIZE_DUAL_1440x720P30_1440x720P30, //FHD FHD	27
    MOVIE_SIZE_CLONE_2880x1440P30_848x480P30 = 28,
    MOVIE_SIZE_CLONE_1440x720P30_848x480P30 = 29,
    
    MOVIE_SIZE_ID_MAX = 8888,
};

//光源频率
typedef NS_ENUM(NSInteger, WIFI_APP_FREQUENCY){
    WIFI_APP_FREQUENCY_50HZ,
    WIFI_APP_FREQUENCY_60HZ
};

//延时拍照
typedef NS_ENUM(NSInteger, WIFI_APP_PHOTO_DELAYREC){
    PHOTO_TIMELAPSE_REC_OFF,
    PHOTO_TIMELAPSE_REC_1SEC,
    PHOTO_TIMELAPSE_REC_5SEC,
    PHOTO_TIMELAPSE_REC_10SEC
};

//循环录像
typedef NS_ENUM(NSInteger, WIFI_APP_MOVIE_CYCLICREC){
    MOVIE_CYCLICREC_OFF,
    MOVIE_CYCLICREC_3MIN,
    MOVIE_CYCLICREC_5MIN,
    MOVIE_CYCLICREC_10MIN,
    MOVIE_CYCLICREC_ID_MAX
};

//延时录像
typedef NS_ENUM(NSInteger, WIFI_APP_MOVIE_DELAYREC){
    MOVIE_TIMELAPSE_REC_OFF,
    MOVIE_TIMELAPSE_REC_1SEC,
    MOVIE_TIMELAPSE_REC_5SEC,
    MOVIE_TIMELAPSE_REC_10SEC,
    MOVIE_TIMELAPSE_REC_30SEC,
    MOVIE_TIMELAPSE_REC_1MIN,
    MOVIE_TIMELAPSE_REC_5MIN,
    MOVIE_TIMELAPSE_REC_10MIN,
    MOVIE_TIMELAPSE_REC_30MIN,
    MOVIE_TIMELAPSE_REC_1HOUR,
    MOVIE_TIMELAPSE_REC_2HOUR,
    MOVIE_TIMELAPSE_REC_3HOUR,
    MOVIE_TIMELAPSE_REC_1DAY
};

//爆光
typedef NS_ENUM(NSInteger, WIFI_APP_EXPOSURE){
    EV_P20,
    EV_P16,
    EV_P13,
    EV_P10,
    EV_P06,
    EV_P03,
    EV_00,
    EV_N03,
    EV_N06,
    EV_N10,
    EV_N13,
    EV_N16,
    EV_N20,
    EV_SETTING_MAX,
};

//拍照模式
typedef NS_ENUM(NSInteger,WIFI_APP_MODE_CMD){
    WIFI_APP_MODE_PHOTO,
    WIFI_APP_MODE_MOVIE,
    WIFI_APP_MODE_PLAYBACK,
    ENUM_DUMMY4WORD
};

//重力感应
typedef NS_ENUM(NSInteger,WIFI_APP_GSENSOR){
    GSENSOR_OFF,
    GSENSOR_LOW,
    GSENSOR_MED,
    GSENSOR_HIGH,
    GSENSOR_ID_MAX,
};

//关机
typedef NS_ENUM(NSInteger,POWEROFF_SETTING){
    POWER_ON,
    POWER_3MIN,
    POWER_5MIN,
    POWER_10MIN,
    POWEROFF_SETTING_MAX
};

//电量
typedef NS_ENUM(NSInteger,BATTERY){
    BATTERY_FULL,
    BATTERY_MED,
    BATTERY_LOW,
    BATTERY_EMPTY,
    BATTERY_EXHAUSTED,
    BATTERY_CHARGE,
    BATTERY_STATUS_TOTAL_NUM
};

//tvFormat
typedef NS_ENUM(NSInteger,TV_MODE){
    TV_MODE_NTSC,
    TV_MODE_PAL,
    TV_MODE_ID_MAX
};

//sd卡状态
typedef NS_ENUM(NSInteger,SD_CARD_STATE){
    CARD_REMOVED = 0,
    CARD_INSERTED,
    CARD_LOCKED
};

//白平衡
typedef NS_ENUM(NSInteger,WB){
    AWB,
    WB_SUNNY,
    WB_CLOUDY,
    WB_TUNGSTEN_LAMP,
    WB_FLUORESCENT_LAMP
};

//ISO(感光度)
typedef NS_ENUM(NSInteger,ISO){
    AUTO,
    ISO_100,
    ISO_200,
    ISO_400,
    ISO_800,
    ISO_1600,
    ISO_3200
};

//Photographic quality(照片质量)
typedef NS_ENUM(NSInteger,PHOTO_QUALITY){
    PQ_LOW,
    ISO_MID,
    ISO_HIGH
};

//(默认开机模式)
typedef NS_ENUM(NSInteger,DEFAULT_MODE){
    MODE_MOVIE=0,
    MODE_PHOTO
};

// F4同步设置
typedef NS_ENUM(NSInteger, SYSTEM_SET_PREVIOUS_SYN_SWITCH)
{
    SYSTEM_SET_PREVIOUS_DEFUALT,    // 默认设置
    SYSTEM_SET_PREVIOUS_SYN,        // 同步设置
    SYSTEM_SET_PREVIOUS_ASYN        // 独立设置
};

// 国家码设置
typedef NS_ENUM(NSInteger, WIFI_CHANNEL)
{
    WIFI_CHANNEL_DEFUALT = 0,
    WIFI_CHANNEL_AMERICA,
    WIFI_CHANNEL_CANADA,
    WIFI_CHANNEL_TAIWAN,
    WIFI_CHANNEL_FRANCE,
    WIFI_CHANNEL_JAPAN,
    WIFI_CHANNEL_ISRAEL,
    WIFI_CHANNEL_OTHER
};
//自动休眠
typedef NS_ENUM(NSInteger, POWER_SAVE)
{
    DETU_POWER_SAVE_OFF = 0,
    DETU_POWER_SAVE_3MINS,
    DETU_POWER_SAVE_5MINS,
    DETU_POWER_SAVE_10MINS
    
};
#pragma mark - Sphere S 与 Sphere协议参数略有不同。



@interface SpProtocol : NSObject

//photo
+(ProtocolData*)Capture;//拍照
+(ProtocolData*)CaptureSize:(WIFI_APP_PHOTO_SIZE)size;//设置照片大小 WIFI_APP_PHOTO_SIZE

//movie
+(ProtocolData*)MovieRecord:(BOOL)enable;//录制
+(ProtocolData*)MovieRecordSize:(WIFI_APP_MOVIE_RECORD_SIZE)size;//视频大小 WIFI_APP_MOVIE_RECORD_SIZE
+(ProtocolData*)MovieHDR:(BOOL)enable;//HDR
+(ProtocolData*)MovieWDR:(BOOL)enable;//WDR
+(ProtocolData*)MovieAudio:(BOOL)enable;//音频开关 MIC
+(ProtocolData*)MovieLiveViewSize:(WIFI_APP_MOVIE_RECORD_SIZE)size;//实时预览的大小 WIFI_APP_MOVIE_RECORD_SIZE

+(ProtocolData*)MovieRecordBitrate:(int)rate;//录制码速
+(ProtocolData*)MovieLiveViewBitrate:(int)rate;//实时流码率
+(ProtocolData*)MovieLiveViewStart:(BOOL)enable;//开启实时预览

//settings
+(ProtocolData*)ModeChange:(WIFI_APP_MODE_CMD)model;//设置拍照模式 WIFI_APP_MODE_CMD
+(ProtocolData*)SetWifiPassword:(NSString*)password;//设置wifi密码
+(ProtocolData*)PowerOff:(POWEROFF_SETTING)setting;//拍照 POWEROFF_SETTING


+(ProtocolData*)QueryCurrentStatus;//查询当前状态
+(ProtocolData*)QueryFileList;//查询文件列表


+(ProtocolData*)DeleteOneFile:(NSString*)diskPath;//删除某个文件
+(ProtocolData*)DeleteAllFiles;//删除某个文件

+(ProtocolData*)HeartBeat;//心跳包

+(ProtocolData*)SetDataImPrint:(BOOL)enable;//设置时间戳

//获取电量
+(ProtocolData*)GetBattery;

//获取当前录制时间
+(ProtocolData*)GetNowRecordingTime;

//tvFormat设置
+(ProtocolData*)SetTvFormat:(int)tvMode;

//SSID设置
+(ProtocolData*)SetSSID:(NSString*)ssid;

//sd卡格式化
+(ProtocolData*)FormatDisk;

//恢复出厂设置
+(ProtocolData*)SystemReset;

//固件版本号
+(ProtocolData*)GetVersion;

//剩余空间
+(ProtocolData*)GetFreeSpace;

//设置曝光
+(ProtocolData*)SetEV:(int)ev;

// 按键音
+(ProtocolData*)SetSoundKey:(BOOL)enable;

//获取ssid和密码
+(ProtocolData*)GetSSIDAndPwd;

//设置日期
+(ProtocolData*)SetDate:(NSDate*)date;

//设置时间
+(ProtocolData*)SetTime:(NSDate*)date;

//获取固件升级上传地址
+(ProtocolData*)GetFWUploadPath;

//更新固件
+(ProtocolData*)UpdateFW;

//获取sd卡状态
+(ProtocolData*)GetSDCardState;


//设置白平衡
+(ProtocolData*)SetWB:(int)wb;
// 循环录像
+ (ProtocolData *)setCyclicRec:(int)cyclicRec;
// 延时录像
+ (ProtocolData *)setDelayRec:(int)setDelayRec;
//设置ISO
+(ProtocolData*)SetISO:(int)iso;
//设置照片质量
+(ProtocolData*)SetPhotographicQuality:(int)qa;
//设置默认模式
+(ProtocolData*)SetDefaultMode:(int)mode;
//设置蜂鸣器
+(ProtocolData*)SetWarningtone:(BOOL)enable;
// 光学防抖
+(ProtocolData*)SetAntisShake:(BOOL)enable;
//硬件型号序列号
+(ProtocolData*)GetMachineVersion;

//保存设置
+(ProtocolData*)SaveSetting;

//设置连拍
+(ProtocolData*)ContinuousCapture:(int)model;

//修改mode
+(ProtocolData*)ChangeMode:(int)mode;

//重连wifi
+(ProtocolData*)ReConnectWifi;


//行车模式
+(ProtocolData*)SetTrafficMode:(BOOL)enable;

//重力感应灵敏度
+(ProtocolData*)SetSensitityOfGravityInduction:(int)induction;

//日期水印
+(ProtocolData*)SetDateWaterMark:(BOOL)enable;

//录音
+(ProtocolData*)SetSoundRecord:(BOOL)enable;

//行车视频预览
+(ProtocolData*)SetShowLiveWhenTraffic:(BOOL)enable;

//获取标注数据
+(ProtocolData*)GetSensorData;

//设置标注数据
+(ProtocolData*)SetSensorData:(NSString *)sensor;

//sphere和spheres某些协议不一致，需要转化一下
+(int)GetCmdInSphereOrSpheres:(int)spid spsid:(int)spsid;

//是否开启按键音
+(ProtocolData*)SetBeepMode:(BOOL)enable;

//获取mode状态
+(ProtocolData*)GetCurrentModel;

//行车模式
+(ProtocolData*)setTrafficMode:(BOOL)enable;

//重力感应灵敏度
+(ProtocolData*)setSensitityOfGravityInduction:(int)induction;

//日期水印
+(ProtocolData*)setDateWaterMark:(BOOL)enable;

//录音
+(ProtocolData*)setSoundRecord:(BOOL)enable;

//行车视频预览
+(ProtocolData*)setShowLiveWhenTraffic:(BOOL)enable;

//sphere和spheres某些协议不一致，需要转化一下
+(int)getCmdInSphereOrSpheres:(int)spid spsid:(int)spsid;

/**
 *  @param f4 获取电量
 */
+(ProtocolData*)getF4_Battery;

/**
 *  @param 获取已经拍摄的张数
 */
+(ProtocolData*)getFreePhotoNum;

/**
 *
 *  @return // 获取已拍摄的照片张数
 */
+(ProtocolData*)getHasTokenPhotoNum ;

/**
 *  @param f4 4灯的状态
 */
+(ProtocolData*)getF4_4sensorState;

// F4 抓图
+(ProtocolData*)getF4_Trigger_Rawenc;

// 设置光源频率
+(ProtocolData*)setSystemFreq:(int)mode;

// disk 总量
+(ProtocolData*)getDiskSize;

// 关机 指令
+(ProtocolData*)closeDevice;

// f4 新增接口 主A  WIFI是否同步控制BCD
+(ProtocolData*)setSystemsyn:(int)model;

// LED Switch 新增led开关 11.16
+(ProtocolData*)SetLEDSwitch:(BOOL)enable;

//运动侦测开关
+(ProtocolData*)SetMotionDetect:(BOOL)enable;


@end
