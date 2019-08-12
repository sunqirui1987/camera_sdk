//
//  CameraInfo.h
//  DeTuZZN
//
//  Created by shenxing on 15/8/4.
//  Copyright (c) 2015年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
//相机相关数据
@interface CameraInfo : NSObject

// 相机文件列表(联永 安霸通用)
@property (nonatomic, strong) NSMutableArray * fileList;

// 相机文件列表(联永 安霸通用)
@property (nonatomic, assign) BOOL isTakingMovie;

//现在拍摄模式，1为照片，2为视频, APP用来记录的模式 (联永 安霸通用)
@property (nonatomic, assign) int nowRecordMode;

/**
 设备返回的模式 (联永)
 */

/*
 PREMODE_MOVIE_PRE_START  = 0,  // rtsp 流已经打开
 MOVIE_RECORDING ,              // rtsp 流已经打开
 MOVIE_PRE_STOP ,               // (Got 2015 preview stop command)  关闭 rtsp流
 PLAYBACK,                      // 进行一些设置
 PHOTO  = 4                     // HTTP 流打开
 */

@property (nonatomic, assign) int mechineCurrentMode;

//是否在录屏 (联永)
@property (nonatomic, assign) BOOL isRecordingScreen;

//最新的照片缩略图路径 (联永 安霸通用)
@property (nonatomic, copy) NSString *newestPicThumPath;

//上一张最新的照片缩略图image (联永 安霸通用)
@property (nonatomic, strong) UIImage *lastNewestPicThumImage;

//最新的视频缩略图路径 (联永 安霸通用)
@property (nonatomic, copy) NSString *newestMovThumPath;

//上一张最新的视频缩略图image (联永 安霸通用)
@property (nonatomic, strong) UIImage *lastNewestMovThumImage;

// 是否显示实时预览 (联永 安霸通用)
@property (nonatomic, assign) BOOL isOpenedLiveStream;

// 图片分辨率 (联永 安霸通用)
@property (nonatomic, assign) int picSize;

// 视频分辨率 (联永 安霸通用)
@property (nonatomic, assign) int movSize;

// 正在录制的时间,为0表示没有在录制 (联永 安霸通用)
@property (nonatomic, assign) int nowMovieRecordingTime;

// 联永下面循环录制状态(对应安霸的分段时间)
@property (nonatomic, assign) int cycleRec;

// 循环录制状态（安霸）
@property (nonatomic, assign) BOOL cycleRecBool;

// 定时录像状态 (联永 安霸通用)
@property (nonatomic, assign) int timingRec;

// 拍照状态 (联永 安霸通用)
@property (nonatomic, assign) int timingPhoto;

// 循环拍照状态 (联永 安霸通用)
@property (nonatomic, assign) int cyclePhoto;

// 开启/停止HDR (联永 安霸通用)
@property (nonatomic, assign) int HDR;

// 开启/停止 光学防抖 (联永 安霸通用)
@property (nonatomic, assign) int AntisShake;

// 开启/停止WDR (联永 安霸通用)
@property (nonatomic, assign) int WDR;

// 开/关按键音 (联永 安霸通用)
@property (nonatomic, assign) int Beep;

// 光源频率 (联永 安霸通用)
@property (nonatomic, assign) int frequency;
// 曝光 (联永 安霸通用)
@property (nonatomic, assign) int EV;

// 运动侦测开关 (联永 安霸通用)
@property (nonatomic, assign) int motion_det;

// 音频开关 (联永 安霸通用)
@property (nonatomic, assign) int movie_audio;

// 时间戳开关 (联永 安霸通用)
@property (nonatomic, assign) int dateIMPrint;

// 剩余空间还能拍多少时间的视频 (联永)
@property (nonatomic, assign) int max_record_time;

// 预览视频图像质量 (联永 安霸通用)
@property (nonatomic, assign) int liveViewSize;

// 行车记录模式视频预览 (联永)
@property (nonatomic, assign) int trafficliveShow;

// 重力感应 (联永 安霸通用)
@property (nonatomic, assign) int movie_gesnsor_sens;

// 自动录像 (联永)
@property (nonatomic, assign) int setAutoRecording;

// 关机 (联永 安霸通用)
@property (nonatomic, assign) int powerOff;

// 语言 (联永 安霸通用)
@property (nonatomic, assign) int language;

// 设置TV输出格式 (联永通用)
@property (nonatomic, assign) int tvFormat;

// 电量 (联永 安霸通用)
@property (nonatomic, assign) int battery;

// 剩余空间 (联永 安霸通用)
@property (nonatomic, assign) long long freeSpace;

// 设备号 1 (联永 安霸通用)
@property (nonatomic, copy) NSString *device;

// sd卡状态 (联永 安霸通用)
@property (nonatomic, assign) int sdCardState;

// 开机默认模式 (联永 安霸通用)
@property (nonatomic, assign) int defaultMode;

// iso (联永 安霸通用)
@property (nonatomic, assign) int iso;

// mic (联永 安霸通用)
@property (nonatomic, assign) int mic;

// 白平衡 (联永 安霸通用)
@property (nonatomic, assign) int wb;

// 照片质量 (联永 安霸通用)
@property (nonatomic, assign) int photoQuality;

// 蜂鸣器 (联永 安霸通用)
@property (nonatomic, assign) int warningTone;

// 序列号 (联永 安霸通用)
@property (nonatomic, copy) NSString *seriesNumber;

// 是否连拍 (联永 安霸通用)
@property (nonatomic, assign) int isContinuousCapture;

// 固件版本 (联永 安霸通用)
@property (nonatomic, copy) NSString *fwVersion;

// 固件版本 (联永 安霸通用)
@property (nonatomic, copy) NSString *fw_build_version;

// 硬件标注，双头的用到 (联永 安霸通用)
@property (nonatomic, copy) NSString *twinData;

// 行车模式 (联永 安霸通用)
@property (nonatomic, assign) int trafficMode;

// 重力感应灵敏度 (联永)
@property (nonatomic, assign) int gravityInduction;

// 日期水印 (联永)
@property (nonatomic, assign) int dateWaterMark;

// 录音 (联永 安霸通用)
@property (nonatomic, assign) int soundRecord;

// 录制码率 (联永 安霸通用)
@property (nonatomic, assign) int recordBitrate;

// 重力感应 (联永 安霸通用)
@property (nonatomic, assign) int SensitityOfGravity;

// led开关 (联永 安霸通用)
@property (nonatomic, assign) int ledSwitch;

// 行车预览模式 (联永 安霸通用)
@property (nonatomic, assign) int showLiveWhenTraffic;

// ssid (联永 安霸通用)
@property (nonatomic, copy) NSString * SSID;

// 密码(联永 安霸通用)
@property (nonatomic, copy) NSString * pwd;

/****安霸设置选项集合****/
// VF状态1是VF状态 0不是VF状态  (安霸)
@property (nonatomic,assign) int vfState;

// 视频质量 (安霸)
@property (nonatomic,assign) int videoQuality;

// 型号 (安霸)
@property (nonatomic,copy) NSString *cameraType;

// 网络制式 (安霸)
@property (nonatomic,copy) NSString *wifiMode;

// 视频分段 (安霸)
@property (nonatomic,copy) NSString *dtvideosplittime;

// 视频分辨率合集 (安霸)
@property (nonatomic,copy) NSArray *videoResolutionArr;

// 视频质量合集 (安霸)
@property (nonatomic,copy) NSArray *videoQualityArr;

// 照片分辨率合集 (安霸)
@property (nonatomic,copy) NSArray *photoResolutionArr;

// iso合集 (安霸)
@property (nonatomic,copy) NSArray *dtisoArr;

// 光源频率合集 (安霸)
@property (nonatomic,copy) NSArray *freqArr;

// 照片质量合集 (安霸)
@property (nonatomic,copy) NSArray *photoQualityArr;

// 蜂鸣器集合 (安霸)
@property (nonatomic,copy) NSArray *spkSwitchArr;

// 循环录影集合 (安霸)
@property (nonatomic,copy) NSArray *dtloopencswitchArr ;

// 录像分段时长集合 (安霸)
@property (nonatomic,copy) NSArray *dtvideosplittimeArr;

// 2.4G 5.8G (安霸)
@property (nonatomic,copy) NSArray *wifiModelArr;

// 开机是否自动打开WIFI (安霸)
@property (nonatomic,copy) NSString *wifi_switch;

// 缩略图信息 (安霸)
@property (nonatomic,copy) NSData *thumbData;

// 10分钟自动停止录影 (安霸)
@property (nonatomic,assign) BOOL autoStopRecord;

//国家码
@property (nonatomic,assign) int  channelCountry;

//待机休眠
@property (nonatomic,copy) NSString  *powerSave;

-(void)initData;

// 重置
- (void)reset;

@end
