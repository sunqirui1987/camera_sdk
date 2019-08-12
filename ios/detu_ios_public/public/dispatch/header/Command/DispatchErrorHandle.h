//
//  DispatchErrorHandle.h
//  dispatchlib
//
//  Created by Seth on 17/3/7.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SdkErrorConstans.h"
#import "AmbarellaProtocol.h"


/**
 *  @abstract Dispatch  Error's Type
 */
typedef NS_ENUM(int, Dispatch_Error_Type) {
    
    Dispatch_Error_None                     = 0 ,             //成功
    Dispatch_Error_Cancel                   = 10000001 ,      //命令取消
    Dispatch_Error_Busy                     = 10000002 ,      //调度器繁忙
    /////////////////////////////////////////////////////////
    /// APP
    Dispatch_Error_Net                      = 1 ,       //网络异常
    Dispatch_Error_Param                    = 2 ,       //参数错误
    Dispatch_Error_NotFound                 = 3 ,       //无效命令
    Dispatch_Error_Parse                    = 4 ,       //解析异常
    
    /////////////////////////////////////////////////////////
    /// FW
    Dispatch_Error_RET_Fail                 = 5 ,       //执行出错
    Dispatch_Error_CMD_Exception            = 6 ,       //命令异常
    Dispatch_Error_MECHINE_OTHERS           = 7 ,       //机器被占用
    Dispatch_Error_FILE_None                = 8 ,       //找不到文件
    Dispatch_Error_EXIF_ERR                 = 9 ,       //照片EXIF信息出错
    Dispatch_Error_BUF_None                 = 10 ,      //内存不足
    Dispatch_Error_FILE_OnlyRead            = 11 ,      //文件是只读的
    Dispatch_Error_FILE_Del                 = 12 ,      //文件删除出错
    Dispatch_Error_PHOTO_Del                = 13 ,      //照删除失败
    Dispatch_Error_CARD_FULL                = 14 ,      //存储空间已满
    Dispatch_Error_MOVIE_Wr                 = 15 ,      //视频存储出错
    Dispatch_Error_MOVIE_Slow               = 16 ,      //请使用C10级别以上高速卡
    Dispatch_Error_BATTERY_Low              = 17 ,      //电量不足
    Dispatch_Error_STORAGE_Full             = 18 ,      //存储空间已满
    Dispatch_Error_FOLDER_Full              = 19 ,      //文件夹数量已满
    Dispatch_Error_FW_WRITE                 = 20 ,      //写入固件信息失败
    Dispatch_Error_FW_READ                  = 21 ,      //读取固件信息失败
    Dispatch_Error_FW_FW_INVALID_STG        = 22 ,      //存储失败
    Dispatch_Error_FW_FW_OFFSET             = 23 ,      //固件更新出错
    Dispatch_Error_FW_READ_CHK_ERR          = 24 ,      //断开连接
    
    ////////////
    //AMBA New
    Dispatch_Error_SESSION_START_FAIL       = 25 ,      // 开启会话错误
    Dispatch_Error_INVALID_TOKEN            = 26 ,      // 无效TOKEN
    Dispatch_Error_REACH_MAX_CLNT           = 27 ,      // Socket 达到最大数
    Dispatch_Error_JSON_PACKAGE             = 28 ,      // 固件JSON包生成错误
    Dispatch_Error_JSON_PACKAGE_TIMEOUT     = 29 ,      // JSON生成超时
    Dispatch_Error_JSON_SYNTAX_ERROR        = 30 ,      // JSON同步语法错误
    Dispatch_Error_HDMI_INSERTED            = 31 ,      // HDMI已插入
    Dispatch_Error_USB_INSERTED             = 301 ,     // USB已插入
    Dispatch_Error_CARD_PROTECTED           = 32 ,      // 卡受限制
    Dispatch_Error_PIV_NOT_ALLOWED          = 33 ,      // PIV受限
    Dispatch_Error_SYSTEM_BUSY              = 34 ,      // 系统繁忙
    Dispatch_Error_APP_NOT_READY            = 35 ,      // APP没设置好
    Dispatch_Error_INVALID_PATH             = 36 ,      // 无效的路径
    Dispatch_Error_DIR_EXIST                = 37 ,      // 文件已经存在
    Dispatch_Error_PERMISSION_DENIED        = 38 ,      // 权限限制
    Dispatch_Error_AUTHENTICATION_FAILED    = 39 ,      // 授权失败
    Dispatch_Error_TimeOut                  = 40 ,      // 超时
    Dispatch_Error_GetVF                    = 41 ,      // 获取VF出错
    Dispatch_Error_SetVF                    = 42 ,      // 重置VF出错
    Dispatch_Error_low_electric             = 43        // 低电
};


@interface DispatchErrorHandle : NSObject


/**
 *  @abstract 统一处理联永返回错误
 */
+ (Dispatch_Error_Type) handleSPhereError:(int)error;

/**
 *  @abstract 统一处理安霸返回错误
 */
+ (Dispatch_Error_Type) handleAmbaError:(int)error;

/**
 *  @abstract 统一返回字符描述
 */
+ (NSString *)descriptionByError:(Dispatch_Error_Type)error ;

@end
