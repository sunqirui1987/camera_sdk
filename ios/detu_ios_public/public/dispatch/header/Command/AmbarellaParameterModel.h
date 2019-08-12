//
//  AmbarellaParameterModel.h
//  DeTuZZN
//
//  Created by lsq on 16/11/25.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface AmbarellaParameterModel : NSObject

@end


@interface AmbarellaFile : NSObject

// 文件路径
@property (nonatomic,copy) NSString *filePath;
// 文件生成日期
@property (nonatomic,copy) NSString *date;
// 文件名
@property (nonatomic,copy) NSString *fileName;
// 缩略图数据
@property (nonatomic,copy) NSData *thumbData;

@end


@interface AmbarellaResponseModel : NSObject

@property (nonatomic, assign) int rval;                         // 错误返回
@property (nonatomic, assign) int token;                        // 会话ID
@property (nonatomic, assign) int msg_id;                       // 消息命令
@property (nonatomic, copy) NSString *type;                     // 类型
@property (nonatomic, copy) NSString *param;                    // 消息字段
@property (nonatomic, strong) NSArray *listing;                 // 文件列表
@property (nonatomic, strong) NSArray *options;                 // 参数集合
@property (nonatomic, copy) NSString *video_resolution;         // 视频分辨率
@property (nonatomic, copy) NSString *video_quality;            // 视频质量
@property (nonatomic, copy) NSString *dt_photo_size;            // 照片分辨率
@property (nonatomic, copy) NSString *dt_photo_quality;         // 照片质量
@property (nonatomic, copy) NSString *dt_mic_switch;            // 录音开关
@property (nonatomic, copy) NSString *dt_spk_switch;            // 蜂鸣器开关
@property (nonatomic, copy) NSString *dt_loop_enc_switch;       // 循环录制开关
@property (nonatomic, copy) NSString *dt_video_split_time;      // 循环录制分段时间
@property (nonatomic, copy) NSString *dt_long_time_record;      // 10分钟自动停止录影
@property (nonatomic,copy) NSString  *dt_wifi_channel_country;  //国家码
@property (nonatomic,copy) NSString  *dt_power_save;            //待机休眠
@property (nonatomic, copy) NSString *power_freq;               // 光源频率
@property (nonatomic, copy) NSString *machine_id;               // 机器序列号
@property (nonatomic, copy) NSString *fw_version;               // 固件版本号
@property (nonatomic, copy) NSString *fw_build_version;         // 固件build版本号
@property (nonatomic, copy) NSString *camera_type;              // 机器型号
@property (nonatomic, copy) NSData *thumbData;                  // 缩略图数据
@property (nonatomic, copy) NSString *AP_CHANNEL;               // 信道号
@property (nonatomic, copy) NSString *AP_SSID;                  // WIFI ssid
@property (nonatomic, copy) NSString *AP_PASSWD;                // WIFI 密码

// 普通数据转换
+ (AmbarellaResponseModel *)msgSwitch:(NSDictionary *)data;
// WIFI信息转换
+ (AmbarellaResponseModel *)tansfomWIFIInfo:(AmbarellaResponseModel *)model;

@end






