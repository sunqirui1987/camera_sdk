//
//  RequestPotocol.h
//  spsdk
//
//  Created by qiruisun on 15/7/21.
//  Copyright (c) 2015年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProtocolData.h"
#import "CaptureEntiy.h"
#import "ValueEntiy.h"
#import "FileListEntiy.h"
#import "SettingsEntiy.h"
#import "SdkErrorConstans.h"

// 几种模式类型
#define MODEL_TAKE_PHOTO 0    // 拍照模式
#define MODEL_CURRENT_NOEW_RECORDING 1   //正在录像
#define MODEL_TAKE_RECORD 2   // 录像模式




#define  WIFIAPP_HTTP_HOSTNAME  @"http://192.168.1.254"
#define  WIFIAPP_RTSP_PATH  @"rtsp://192.168.1.254:554/xxx.mov"
#define  WIFIAPP_SOCKET_HOSTNAME @"192.168.1.254:3333"


#pragma mark - 1000 + command  photo
//photo
#define  WIFIAPP_CMD_CAPTURE  1001 //获取照片
#define  WIFIAPP_CMD_CAPTURESIZE  1002 //照片大小
#define  WIFIAPP_CMD_FREE_PIC_NUM  1003 //剩余空间预计还能拍多少照片
#define  WIFIAPP_CMD_PHOTO_BURST  1004 //连拍 0 2 5 10
#define  WIFIAPP_CMD_MOVIE_PQ_SPHERS_CHANGE  1005 //照片质量         ＝＝＝＝＝＝＝   注意 800的不同 －－ 2021
#define  WIFIAPP_CMD_MOVIE_WB_SPHERS_CHANGE  1007 //白平衡           ＝＝＝＝＝＝＝   注意 800的不同 －－ 2019
#define  WIFIAPP_CMD_MOVIE_ISO_SPHERS_CHANGE 1009 //iso
#define  WIFIAPP_CMD_NEW_MOVIE_EV  1010 //设置曝光
#define  WIFIAPP_CMD_NEW_ANTIS_SHAKING  1011 //光学防抖

#pragma mark - 2000 + command  movice
//movice
#define  WIFIAPP_CMD_RECORD  2001 //开启/停止录像
#define  WIFIAPP_CMD_MOVIE_REC_SIZE  2002//设置视频质量，1080p、720p、WVGA、VGA、1440p
#define  WIFIAPP_CMD_CYCLIC_REC  2003 //开启/停止循环录像

#define  WIFIAPP_CMD_MOVIE_800_HDR  2004 //开启/停止HDR      s twin      ＝＝＝＝＝＝＝   注意 800的不同 2004是800的HDR s系列的WDR
#define  WIFIAPP_CMD_NEW_MOVIE_WDR  2004 //开启/停止WDR  s twin

#define  WIFIAPP_CMD_MOVIE_EV  2005 //设置曝光
#define  WIFIAPP_CMD_MOTION_DET  2006 // 运动侦测开关
#define  WIFIAPP_CMD_MOVIE_AUDIO  2007 // 音频开关
#define  WIFIAPP_CMD_SOUND_RECORD 2007 //录音
#define  WIFIAPP_CMD_DATEIMPRINT  2008 //时间戳开关
#define  WIFIAPP_CMD_MAX_RECORD_TIME  2009 // 剩余空间还能拍多少时间的视频
#define  WIFIAPP_CMD_MOVIE_LIVEVIEW_SIZE  2010 // 设置预览视频图像质量
#define  WIFIAPP_CMD_MOVIE_GSENSOR_SENS  2011 //重力感应
#define  WIFIAPP_CMD_SET_AUTO_RECORDING  2012 // 自动录像
#define  WIFIAPP_CMD_MOVIE_REC_BITRATE  2013// 设置视频速率，kb/s
#define  WIFIAPP_CMD_MOVIE_LIVEVIEW_BITRATE  2014 // 设置预览视频速率，kb/s
#define  WIFIAPP_CMD_MOVIE_LIVEVIEW_START  2015 //开启/关闭视频预览
#define  WIFIAPP_CMD_MOVIE_RECORDING_TIME  2016 // 获取录像时间
#define WIFIAPP_CMD_MOVIE_REC_TRIGGER_RAWENC  2017 // F4 抓图
#define WIFIAPP_CMD_MOVIE_GET_RAWENC_JPG      2018

#define  WIFIAPP_CMD_MOVIE_WB  2019 //白平衡                                                       Sphere  800
#define  WIFIAPP_CMD_MOVIE_ISO 2020 //iso                                                         Sphere  800
#define  WIFIAPP_CMD_MOVIE_PQ  2021 //照片质量                                                     Sphere  800

#pragma mark - 3000 + command  settings
//settings
#define  WIFIAPP_CMD_MODECHANGE  3001 //  切换模式，照片、视频、回放
#define  WIFIAPP_CMD_QUERY  3002 //查询当前命令
#define  WIFIAPP_CMD_SET_SSID  3003 // 设置 SSD
#define  WIFIAPP_CMD_SET_PASSPHRASE  3004 // 设置密码
#define  WIFIAPP_CMD_SET_DATE  3005 //设置日期
#define  WIFIAPP_CMD_SET_TIME  3006 // 设置时间
#define  WIFIAPP_CMD_POWEROFF  3007// 关机
#define  WIFIAPP_CMD_LANGUAGE  3008 // 设置语言
#define  WIFIAPP_CMD_TVFORMAT  3009 //设置TV输出格式
#define  WIFIAPP_CMD_FORMAT  3010 //格式化SD卡或内存
#define  WIFIAPP_CMD_SYSRESET  3011 //恢复出厂设置
#define  WIFIAPP_CMD_VERSION  3012 // 获取版本信息
#define  WIFIAPP_CMD_FWUPDATE  3013// 固件升级
#define  WIFIAPP_CMD_QUERY_CUR_STATUS  3014 // 查询当前设置
#define  WIFIAPP_CMD_FILELIST  3015 //获取文件列表
#define  WIFIAPP_CMD_HEARTBEAT  3016 //检查连接状态
#define  WIFIAPP_CMD_DISK_FREE_SPACE  3017 //获取剩余空间大小
#define  WIFIAPP_CMD_RECONNECT_WIFI  3018 //重连wifi
#define  WIFIAPP_CMD_GET_BATTERY  3019// 获取电池电量状态
#define  WIFIAPP_CMD_NOTIFY_STATUS  3020 // 获取通知，如电量紧张，空间不足
#define  WIFIAPP_CMD_SAVE_MENUINFO  3021 //保存当前设置
#define  WIFIAPP_CMD_GET_CARD_STATUS  3024 //sd卡状态
#define  WIFIAPP_CMD_GET_UPDATEFW_PATH  3026 //获取固件上传地址
#define  WIFIAPP_CMD_GET_SSID_PASSPHRASE  3029 //获取ssid和密码
#define  WIFIAPP_CMD_SET_DEF_MODE  3030 //默认mode
#define  WIFIAPP_CMD_SET_WARNING  3031 //相机提示音开关
#define  WIFIAPP_CMD_GET_CONFIG  3032 //型号序列号

#define  WIFIAPP_CMD_MODE_CHANGE  3033 //Mode change                －－－－－－－－－---- deperad

#define  WIFIAPP_CMD_GET_MODE_STAUTS 3037 //current Mode           instead 8015


#pragma mark - 4000 + command

//playback
#define  WIFIAPP_CMD_THUMB  4001 //获取文件缩略图
#define  WIFIAPP_CMD_SCREEN  4002 //获取文件screennail图像
#define  WIFIAPP_CMD_DELETE_ONE  4003 //删除文件
#define  WIFIAPP_CMD_DELETE_ALL  4004 //删除所有文件WIFIAPP_CMD_MOVIE_LIVEVIEW_BITRATE  2014 // 设置预览视频速率，kb/s
#define WIFIAPP_CMD_MOVIE_FILE_INFO 4005 // 文件列表


#pragma mark - 5000 + command
//upload command
#define WIFIAPP_CMD_UPLOAD          5001    //   上传
#define WIFIAPP_CMD_UPLOAD_AUDIO    5002    //   上传音频


#pragma mark - 8000 + command

#define  WIFIAPP_CMD_SET_DEF_MODE_SPHERS_CHANGE  8002 //默认mode
//#define  WIFIAPP_CMD_SET_WARNING_SPHERS_CHANGE  8003 //相机提示音开关
#define  WIFIAPP_CMD_GET_CONFIG_SPHERS_CHANGE  8004 //型号序列号
#define  WIFIAPP_CMD_MODE_CHANGE_SPHERS_CHANGE 8005 //Mode change
#define  WIFIAPP_CMD_SET_USB_POWER          8006  //设置USB开关                              9.5 整理
#define  WIFIAPP_CMD_SET_SYETEM_FREQ        8007  //设置光源频率                              F4 新加命令
#define  WIFIAPP_CMD_SET_SENSOR_DATA        8008//标定设置
#define  WIFIAPP_CMD_GET_SENSOR_DATA        8009//标定读取
#define  WIFIAPP_CMD_TRAFFIC_MODE           8010 //行车模式
#define  WIFIAPP_CMD_SENSITIVITY_OF_GRAVITY_INDUCTION 8011 //重力感应灵敏度
#define  WIFIAPP_CMD_DATE_WATERMARK         8012 //日期水印
#define  WIFIAPP_CMD_NEW_BEEP               8013 //按键音 相机提示音开关
#define  WIFIAPP_CMD_SHOW_LIVE_WHEN_TRAFFIC 8014 //行车视频预览
#define  WIFIAPP_CMD_GET_SYSTEM_BUSY        8015 //当前模式                 ----- deperate
#define  WIFIAPP_CMD_GET_4SENSOR_STATUSE    8016 // f4 4灯状态                             F4 新加命令
#define  WIFIAPP_CMD_GET_F4_BATPERCENT      8017 // f4 电量                                F4 新加命令
#define  WIFIAPP_CMD_GET_DISK_SIZE     		8018 // 卡总量                                 F4 新加命令
#define  WIFIAPP_CMD_NEW_MOVIE_TIMELAPSE_REC  8019 //延时录像
#define  WIFIAPP_CMD_GET_PHOTO_NUM    		8020 // 已拍摄照片总数                           F4 新加命令
#define  WIFIAPP_CMD_CLOSE_PHOTO_DEVICE    	8021 // 关机                                   F4 新加命令
#define  WIFIAPP_CMD_SET_F4_SYN             8022 // 设置                                   F4 新加命令
#define  WIFIAPP_CMD_NEW_MOVIE_HDR          8023 // 开启/停止HDR  twin－n ／ s
#define  WIFIAPP_CMD_SET_LEDFLASH           8025 //0,off,1,on                   S  TWIN Dragon新加命令

@interface RequestPotocol : NSObject

+(ProtocolData*)Req:(NSDictionary*)params entiy:(BaseEntiy*)entiy;

@end
