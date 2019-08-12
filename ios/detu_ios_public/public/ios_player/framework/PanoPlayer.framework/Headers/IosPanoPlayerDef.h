//
//  IosPanoPlayerDef.h
//  PanoPlayer
//
//  Created by chao on 2017/10/25.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>

//PanoPlayer状态及代理事件
typedef enum PanoPlayerErrorCode {
    PanoPlayerErrorCode_LACK_CALIBRATION,
} PanoPlayerErrorCode;

typedef enum PanoPlayerStatus {
    PanoPlayerStatus_LOADING,
    PanoPlayerStatus_LOADED,
    PanoPlayerStatus_ERROR,
} PanoPlayerStatus;

@protocol IPanoPlayerDelegate <NSObject>
//当状态为PanoPlayerStatus_ERROR时
-(void)onPanoPlayerStatusChanged:(PanoPlayerStatus) status tip:(NSString*) msg;
@end

//PanoPlayer Plugin状态及代理事件
typedef enum PanoPluginStatus
{
    PanoPluginStatus_PREPARED,
    PanoPluginStatus_PLAYING,
    PanoPluginStatus_PAUSE,
    PanoPluginStatus_STOP,
    PanoPluginStatus_FINISH,
    PanoPluginStatus_CODEC_SWITCH,
    PanoPluginStatus_ERROR,
} PanoPluginStatus;

typedef enum PanoPluginError
{
    PanoPluginError_NETWORK
} PanoPluginError;

@protocol IPanoPlayerPluginDelegate <NSObject>
-(void)onPanoPlayerPluginStatusChanged:(PanoPluginStatus) status tip:(NSString*) msg;
-(void)onPanoPlayerPluginProgressChanged:(long) playTime bufferTime:(long) bufferTime duration:(long) duration;
@end



//Log级别
typedef enum PanoLogLevel {
    PanoLogLevel_UNKNOWN = 0,
    PanoLogLevel_DEFAULT = 1,
    PanoLogLevel_VERBOSE = 2,
    PanoLogLevel_DEBUG   = 3,
    PanoLogLevel_INFO    = 4,
    PanoLogLevel_WARN    = 5,
    PanoLogLevel_ERROR   = 6,
    PanoLogLevel_FATAL   = 7,
    PanoLogLevel_SILENT  = 8,
} PanoLogLevel;

//切换动画类型
typedef enum PanoAnimation {
    PanoAnimation_BackEaseIns = 0,
    PanoAnimation_BackEaseOuts = 1,
    PanoAnimation_BackEaseInOuts = 2,
    PanoAnimation_BounceEaseIns = 3,
    PanoAnimation_BounceEaseOuts = 4,
    PanoAnimation_BounceEaseInOuts = 5,
    PanoAnimation_CircEaseIns = 6,
    PanoAnimation_CircEaseOuts = 7,
    PanoAnimation_CircEaseInOuts = 8,
    PanoAnimation_CubicEaseIns = 9,
    PanoAnimation_CubicEaseOuts = 10,
    PanoAnimation_CubicEaseInOuts = 11,
    PanoAnimation_ElasticEaseIns = 12,
    PanoAnimation_ElasticEaseOuts = 13,
    PanoAnimation_ElasticEaseInOuts = 14,
    PanoAnimation_ExpoEaseIns = 15,
    PanoAnimation_ExpoEaseOuts = 16,
    PanoAnimation_ExpoEaseInOuts = 17,
    PanoAnimation_LinearEaseIns = 18,
    PanoAnimation_LinearEaseOuts = 19,
    PanoAnimation_LinearEaseInOuts = 20,
    PanoAnimation_QuadEaseIns = 21,
    PanoAnimation_QuadEaseOuts = 22,
    PanoAnimation_QuadEaseInOuts = 23,
    PanoAnimation_QuartEaseIns = 24,
    PanoAnimation_QuartEaseOuts = 25,
    PanoAnimation_QuartEaseInOuts = 26,
    PanoAnimation_QuintEaseIns = 27,
    PanoAnimation_QuintEaseOuts = 28,
    PanoAnimation_QuintEaseInOuts = 29,
    PanoAnimation_SineEaseIns = 30,
    PanoAnimation_SineEaseOuts = 31,
    PanoAnimation_SineEaseInOuts = 32,
} EaseTypes;

//资源类型
typedef enum PanoResourceType {
    PanoResourceType_CUBE, //六面图
    PanoResourceType_SPHERE, //图片
    PanoResourceType_VIDEO, //视频
    PanoResourceType_SPACE3D,
}PanoResourceType;

typedef enum PanoDeviceId {
    PanoDeviceId_UNKNOW = -1,
    PanoDeviceId_2_1 = 0,
    PanoDeviceId_SPHERE_800 = 1,
    PanoDeviceId_SPHERE_S = 11,
    PanoDeviceId_482 = 101,
    PanoDeviceId_SPHERE_360 = 360,
    PanoDeviceId_TWO_SPHERE = 2000,
    PanoDeviceId_SPHERE_DETU_TWINS = 2002,
    PanoDeviceId_SPHERE_THETAS = 2003,
    PanoDeviceId_SPHERE_INSTA_360 = 2004,
    PanoDeviceId_SPHERE_Real3D = 2005,
    PanoDeviceId_SPHERE_DETU_F4 = 4001,
    PanoDeviceId_SPHERE_DETU_M1 = 4003,
}PanoDeviceId;

@interface PanoNodeImage : NSObject
@property(nonatomic, assign)PanoResourceType panoResourceType;
@property(nonatomic, assign)PanoDeviceId panoDeviceId;
@property(nonatomic, strong)NSString* calibration; //标定信息
@property(nonatomic, strong)NSArray<NSString*>* urls; //资源绝对地址
@property(nonatomic, assign)float rz;//用于翻转模型
@property(nonatomic, assign)float rx;//用于旋转模型
@property(nonatomic, assign)float ry;//用于旋转模型
@property(nonatomic,assign)bool isreplay_f4;
@end

@interface Preview : NSObject
@property (nonatomic , copy)NSString* url;
@property (nonatomic , copy)NSString* type;
@end

//视图类型
typedef enum PanoViewMode {
    PanoViewMode_UNKNOW = 0, //未知模式
    PanoViewMode_DEFAULT = 1, //默认全景模式
    PanoViewMode_FISHEYE, //鱼眼模式
    PanoViewMode_VR_HORIZONTAL, //水平分割VR模式
    PanoViewMode_VR_VERTICAL, //竖直分割VR模式
    PanoViewMode_ORIGINAL, //原图模式
    PanoViewMode_FLAT, //平面模式， 多鱼眼被展开为2：1
    PanoViewMode_LITTLE_PLANET, //小行星模式
    PanoViewMode_SPHERE, //曲面模式
    PanoViewMode_SPACE3D,//obj 3d 模式
}PanoViewMode;

#define PanoNodeViewInvalidateValue -1000000.0f

@interface PanoNodeView : NSObject
@property(nonatomic, assign)float hLookAt;
@property(nonatomic, assign)float hLookAtMin;
@property(nonatomic, assign)float hLookAtMax;

@property(nonatomic, assign)float vLookAt;
@property(nonatomic, assign)float vLookAtMin;
@property(nonatomic, assign)float vLookAtMax;

@property(nonatomic, assign)float curfov;
@property(nonatomic, assign)float deffov;
@property(nonatomic, assign)float deffovMin;
@property(nonatomic, assign)float deffovMax;

@property(nonatomic, assign)float spherefov;
@property(nonatomic, assign)float spherefovMin;
@property(nonatomic, assign)float spherefovMax;

@property(nonatomic, assign)float littlePlanetfov;
@property(nonatomic, assign)float littlePlanetfovMax;
@property(nonatomic, assign)float littlePlanetfovMin;

@property(nonatomic, assign)float fisheyefov;
@property(nonatomic, assign)float fisheyefovMax;
@property(nonatomic, assign)float fisheyefovMin;

@property(nonatomic, assign)float VREyeOffset;//右眼相对左眼的偏移量
@property(nonatomic, assign)float vrFov;
@property(nonatomic, assign)PanoViewMode viewMode;
@property(nonatomic, assign)bool isPointSelecting;
@property(nonatomic,assign)float zOffsetScale;
@end

@interface PanoData : NSObject
@property(nonatomic,strong)Preview *preview;
@property(nonatomic, strong)PanoNodeView* nodeView;
@property(nonatomic, strong)PanoNodeImage* nodeImage;
@property (nonatomic , strong)NSMutableArray *hotpotlist;
@end

@interface Hotpotdata : NSObject
@property (nonatomic , copy)NSString* name;
@property (nonatomic , assign)float ath;
@property (nonatomic , assign)float atv;
@property (nonatomic , copy)NSString* eventtype;
@property (nonatomic , copy)NSString* eventarg;
@property (nonatomic , copy)NSString* style;
@property (nonatomic , copy)NSString* stylearg;
@property (nonatomic , copy)NSString* locdata;//坐标
@property (nonatomic , assign)float alpha;
@property (nonatomic , assign)float scale;
@property (nonatomic,assign) BOOL checkrange;//检测区域是否加大
@property (nonatomic,assign) BOOL hidden;//是否显示 配置里的值
@property (nonatomic,assign) BOOL copyhidden;//是否显示 实际的值，控制热点显示和隐藏
@end
//一个option: Category:[key:value]
typedef NS_ENUM(NSInteger, PanoPlayerOptionType) {
    PanoPlayerOptionCategoryFormat = 1,
    PanoPlayerOptionCategoryCodec  = 2,
    PanoPlayerOptionCategorySws    = 3,
    PanoPlayerOptionCategoryPlayer = 4,
    PanoPlayerOptionCategorySwr    = 5,
};

typedef NS_ENUM(NSInteger, PanoPlayerOptionValueType) {
    PanoPlayerOptionValueInt = 1,
    PanoPlayerOptionValueString = 2
};

@interface PanoPlayerOption : NSObject
@property(nonatomic, assign)PanoPlayerOptionType playerOptionType;
@property(nonatomic, strong)NSString* key;
@property(nonatomic, strong)NSString* value;
@property(nonatomic, assign)PanoPlayerOptionValueType playerOptionValueType;
@end

@protocol IPanoPlayerHotpotDelegate <NSObject>
-(void)PanoPlayOnTapBeforeHotpot:(Hotpotdata*)hotspot;//点击热点响应前
-(void)PanoPlayOnTapAfterHotpot:(Hotpotdata*)hotspot;//点击热点后
@end

typedef NS_ENUM(NSInteger, DisplayType) {
    DisplayType_GL_DISTORTED,
    DisplayType_GL_UN_DISTORTED,
    DisplayType_PLATFORM,
    DisplayType_UNKNOW
};

static const float LAYOUT_INVALIDATE_VALUE = -10000;

@interface LayoutParams : NSObject
@property(nonatomic, assign)float width;
@property(nonatomic, assign)float height;
@property(nonatomic, assign)DisplayType displayType;
@property(nonatomic, assign)float rx;
@property(nonatomic, assign)float ry;
@property(nonatomic, assign)float rz;
@property(nonatomic, assign)float scale;
@property(nonatomic, assign)float ath;
@property(nonatomic, assign)float atv;
@end

@interface LiteDecor : NSObject
@property(nonatomic, strong)NSString* tag;
@property(nonatomic, strong)NSString* imageUrl;
@property(nonatomic, strong)LayoutParams* layoutParams;
@end

//是否使用硬解，type:[PanoPlayerOptionCategoryCodec];value:[true|false]
#define PLAYER_OPTION_DETU_KEY_DECODER "detu_hw_decoder"

//des: «∑ÒÕ≥º∆ ˝æ›, type:PlayerOptionType_Player, value:["true"|"false"]
#define PLAYER_OPTION_DETU_KEY_IS_SHOW_STATISTICS "detu_show_statistics"

//des: «∑Ò◊Ë»˚ ˝æ›, type:PlayerOptionType_Player, value:["true"|"false"]
#define PLAYER_OPTION_DETU_KEY_IS_BLOCK_FRAME "detu_block_frame"



