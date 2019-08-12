//
//  SdkErrorConstans.h
//  spsdk
//
//  Created by qiruisun on 15/7/21.
//  Copyright (c) 2015年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>


#define SUCCCESS 0
#define NETWORK_EXCEPTION  -1000 //网络异常
#define PARSE_EXCEPTION    -1001 //解析异常
#define CMD_EXCEPTION      -1002 //命令异常
#define CMD_UNKNOW         -1003 //未知错误

#define WIFIAPP_RET_RECORD_STARTED         1 //录像开始
#define WIFIAPP_RET_RECORD_STOPPED         2 //录像停止
#define WIFIAPP_RET_DISCONNECT         3 //wifi连接失败
#define WIFIAPP_RET_MIC_ON         4 //麦克风已打开
#define WIFIAPP_RET_MIC_OFF         5 //麦克风已关闭
#define WIFIAPP_RET_POWER_OFF         6 //Notify app Car DV power off	关机
#define WIFIAPP_RET_REMOVE_BY_USER         7 //有其他用户连接到相机，您已断线

#define WIFIAPP_RET_NOFILE         -1//找不到文件
#define WIFIAPP_RET_EXIF_ERR         -2 //照片EXIF信息出错
#define WIFIAPP_RET_NOBUF         -3 //内存不足
#define WIFIAPP_RET_FILE_LOCKED         -4 //文件是只读的
#define WIFIAPP_RET_FILE_ERROR         -5 //文件删除出错
#define WIFIAPP_RET_DELETE_FAILED         -6 //照删除失败
#define WIFIAPP_RET_MOVIE_FULL         -7 //存储空间已满
#define WIFIAPP_RET_MOVIE_WR_ERROR         -8 //视频存储出错
#define WIFIAPP_RET_MOVIE_SLOW         -9 //请使用C10级别以上高速卡
#define WIFIAPP_RET_BATTERY_LOW         -10 //电量不足
#define WIFIAPP_RET_STORAGE_FULL         -11 //存储空间已满
#define WIFIAPP_RET_FOLDER_FULL         -12 //文件夹数量已满

#define WIFIAPP_RET_FAIL         -13 //执行出错
#define WIFIAPP_RET_FW_WRITE_CHK_ERR         -14 //写入固件信息失败
#define WIFIAPP_RET_FW_READ2_ERR         -15 //读取固件信息失败
#define WIFIAPP_RET_FW_WRITE_ERR         -16 //固件升级程序写入失败
#define WIFIAPP_RET_FW_READ_CHK_ERR         -17 //读取固件信息失败

#define WIFIAPP_RET_FW_READ_ERR         -18 //无法读取固件信息
#define WIFIAPP_RET_FW_INVALID_STG         -19 //存储失败
#define WIFIAPP_RET_FW_OFFSET         -20 //固件更新出错
#define WIFIAPP_RET_PAR_ERR         -21 //参数错误
#define WIFIAPP_RET_CMD_NOTFOUND         -256 //无效的命令


//其他错误清单


@interface SdkErrorConstans : NSObject

@end
