//
//  AmbarellaProtocol.h
//  DeTuZZN
//
//  Created by lsq on 16/11/24.
//  Copyright © 2016年 DETU. All rights reserved.
//

//#ifndef AmbarellaProtocol_h
//#define AmbarellaProtocol_h

//ambarella notify
#define NETCTRL_STR_NOTICE_POWER_OFF 			@"power_off"
#define NETCTRL_STR_NOTICE_WIFI_OFF 		    @"wifi_on"
#define NETCTRL_STR_NOTICE_WIFI_ON 				@"wifi_off"
#define NETCTRL_STR_NOTICE_SD_REMOVE 			@"sd_remove"
#define NETCTRL_STR_NOTICE_SD_INSERT 			@"sd_insert"
#define NETCTRL_STR_NOTICE_SD_FULL 				@"sd_full"
#define NETCTRL_STR_NOTICE_SD_FORMAT_ERROR 	    @"sd_format_error"
#define NETCTRL_STR_NOTICE_SD_RUN_ERROR 		@"sd_run_error"
#define NETCTRL_STR_NOTICE_USB_MSC_ENTER 		@"usb_msc_enter"
#define NETCTRL_STR_NOTICE_USB_MSC_OUT 		    @"usb_msc_out"
#define NETCTRL_STR_NOTICE_HDMI_IN 				@"hdmi_in"
#define NETCTRL_STR_NOTICE_HDMI_OUT 			@"hdmi_out"
#define NETCTRL_STR_NOTICE_DC_IN 				@"dc_in"
#define NETCTRL_STR_NOTICE_DC_OUT 				@"dc_out"
#define NETCTRL_STR_NOTICE_RECORD_ERROR         @"record_error"
#define NETCTRL_STR_NOTICE_FWUPDATE             @"put_file_fail"
#define NETCTRL_STR_NOTICE_RECORD_STOP 		    @"record_stop"
#define NETCTRL_STR_NOTICE_RECORD_STOP_10MIN 	@"record_stoped_10min"   // 自动十分钟停止录像
#define NETCTRL_STR_NOTICE_RECORD_START 	    @"record_start"
#define NETCTRL_STR_NOTICE_CAPTURE_START 	    @"capture_start"
#define NETCTRL_STR_NOTICE_RECORD_STOP_SD_ERROR @"record_stop_sd_error"
#define NETCTRL_STR_NOTICE_RECORD_STOP_IO_ERROR @"record_stop_io_error"
#define NETCTRL_STR_NOTICE_SESSION_STOP			@"session_stop"
//错误命令集合
typedef enum {
    ERROR_NETCTRL_UNKNOWN_ERROR = -1,              // 未知错误
    ERROR_NETCTRL_SESSION_SUCCCESS = 0,            // 成功
    ERROR_NETCTRL_SESSION_START_FAIL = -3,         // 开启会话错误
    ERROR_NETCTRL_INVALID_TOKEN = -4,              // 无效TOKEN
    ERROR_NETCTRL_REACH_MAX_CLNT = -5,             // Socket 达到最大数
    ERROR_NETCTRL_JSON_PACKAGE_ERROR = -7,         // 固件JSON包生成错误
    ERROR_NETCTRL_JSON_PACKAGE_TIMEOUT = -8,       // JSON生成超时
    ERROR_NETCTRL_JSON_SYNTAX_ERROR = -9,          // JSON同步语法错误
    ERROR_NETCTRL_INVALID_OPTION_VALUE = -13,      // 无效的选项值
    ERROR_NETCTRL_INVALID_OPERATION = -14,         // 无效的操作
    ERROR_NETCTRL_HDMI_INSERTED = -16,             // HDMI已插入
    ERROR_NETCTRL_NO_MORE_SPACE = -17,             // 空间存储不足
    ERROR_NETCTRL_CARD_PROTECTED = -18,            // 卡受限制
    ERROR_NETCTRL_NO_MORE_MEMORY = -19,            // 内存不足
    ERROR_NETCTRL_PIV_NOT_ALLOWED = -20,           // PIV受限
    ERROR_NETCTRL_SYSTEM_BUSY = -21,               // 系统繁忙
    ERROR_NETCTRL_APP_NOT_READY = -22,             // APP没设置好
    ERROR_NETCTRL_OPERATION_UNSUPPORTED = -23,     // 操作不支持
    ERROR_NETCTRL_INVALID_TYPE = -24,              // 无效类型
    ERROR_NETCTRL_INVALID_PARAM = -25,             // 无效的参数
    ERROR_NETCTRL_INVALID_PATH = -26,              // 无效的路径
    ERROR_NETCTRL_DIR_EXIST = -27,                 // 文件已经存在
    ERROR_NETCTRL_PERMISSION_DENIED = -28,         // 权限限制
    ERROR_NETCTRL_AUTHENTICATION_FAILED = -29,     // 授权失败
    ERROR_NETCTRL_SD_LOW_SPEED = -30 ,             // 卡异常
    ERROR_NETCTRL_SD_NO = -31  ,                   // 没有SD卡
    ERROR_NETCTRL_SD_ERROR = -32 ,                 // SD卡错误
    ERROR_NETCTRL_LOW_BAT_LEVEL = -33 ,            // 低电
    
    ERROR_NETCTRL_USB_INSERTED = -34               // USB 已经插入
}ABErrorCommands;

/**系统相关命令*/
typedef enum {
    AMBA_GET_SETTING                = 1,                 //相机参数
    AMBA_SET_SETTING                = 2,                 //个别相机参数值参数
    AMBA_GET_ALL_CURRENT_SETTINGS   = 3,                 //用于检索所有摄像机参数的当前值
    AMBA_FORMAT                     = 4,
    AMBA_GET_SPACE                  = 5,
    AMBA_GET_NUMB_FILES             = 6,
    AMBA_NOTIFICATION               = 7,
    AMBA_BURNIN_FW                  = 8,
    AMBA_GET_SINGLE_SETTING_OPTIONS = 9,                 // 获取相机配置
    AMBA_PUT_GPS_INFO               = 10,
    AMBA_GET_DEVICEINFO             = 11,
    AMBA_POWER_MANAGE               = 12,
    AMBA_GET_BATTERY_LEVEL          = 13,
    AMBA_ZOOM                       = 14,
    AMBA_ZOOM_INFO                  = 15,
    AMBA_CHANGE_BITRATE             = 16,
    
}ABSystemCommands;

/**会话命令集合*/
typedef enum {
    AMBA_START_SESSION = 257,  //开始会话
    AMBA_STOP_SESSION = 258,   //停止会话
    AMBA_RESET_VF = 259,       //重置
    AMBA_STOP_VF  = 260,        //停止重置
    AMBA_STATE_VF  = 260,        //停止重置
    AMBA_SET_CLNT_INFO = 261,    //获取了Session 以后立马就发这个命令
}ABSessioncommandType;

/***视频命令集合***/
typedef enum {
    AMBA_RECORD_START=513,
    AMBA_RECORD_STOP=514,
    AMBA_GET_RECORD_TIME=515,
    AMBA_FORCE_SPLIT=516,
}ABVideoCommands;

/***照片命令集合***/
typedef enum {
    AMBA_TAKE_PHOTO=769,
    AMBA_CONTINUE_CAPTURE_STOP=770,
}ABPhotoCommands;

/***文件命令集合***/
typedef enum {
    AMBA_DEL_FILE=1281,
    AMBA_LS=1282,
    AMBA_CD=1283,
    AMBA_PWD=1284,
    AMBA_GET_FILE=1285,
    AMBA_PUT_FILE=1286,
    AMBA_CANCEL_FILE_XFER=1287,
    AMBA_MKDIR=1289
}ABFileSystemCommands;

/***WIFI设置命令集合***/
typedef enum {
    AMBA_WIFI_RESTART=1537,
    AMBA_SET_WIFI_SETTING=1538,
    AMBA_GET_WIFI_SETTING=1539,
    AMBA_WIFI_STOP=1540,
    AMBA_WIFI_START=1541,
    AMBA_GET_WIFI_STATUS=1542,
}ABWiFiCommands;

/***Media命令集合***/
typedef enum {
    AMBA_GET_THUMB=1025,
    AMBA_GET_MEDIAINFO=1026,
    AMBA_SET_MEDIA_ATTRIBUTE=1027
}ABMediaCommands;

/***Query命令集合***/
typedef enum {
    AMBA_QUERY_SESSION_HOLDER=1793
}ABQueryCommands;

/***镜头参数集合***/
typedef enum {
    AMBA_DETU_SET_LENS_PARAM=2049,
    AMBA_DETU_GET_LENS_PARAM=2050
}ABLensParamCommands;

/***自定义***/
typedef enum {
    AMBA_DETU_AUTO_poWER_OFFF=2051,
    SET_RTMP_SERVER_ADDR = 2054,
    RESTART = 2061,                       //重启相机
    AMBA_START_RTSP_PUSH = 2057,          //开启推流
    AMBA_STOP_RTSP_PUSH = 2058,           //关闭推流
    AMBA_DETU_SET_WIFI_CONFIG = 2060,     //设置WIFI信息
    AMBA_DETU_GET_TEMPERATURE = 2062,     //获取相机机内温度
    AMBA_DETU_CLOSE_MACHINE = 2063,       //关机
    AMBA_DETU_GET_CAM_STATE	 = 0x810,     //获取相机存储模式（rec：录像拍照模式，msc存储模式，fwupdate升级状态，other其他 ）
    AMBA_DETU_FW_UPDATE = 0x811,          //设置固件升级模式
    AMBA_DETU_FW_UPDATE_VERIFY_AFTER_DATA_COMPLETE = 0x812,          // 固件传输完成通知机器进行校验
    AMBA_DETU_SEND_RTSP_INFO = 2065       //统计码率、gop   // 注释掉
    
}ABOtherCommands;



//#endif /* AmbarellaProtocol_h */




