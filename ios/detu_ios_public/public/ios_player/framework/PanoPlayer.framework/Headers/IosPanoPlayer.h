//
//  PanoPlayer.h
//  PanoPlayer
//
//  Created by chao on 2017/10/24.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IosPanoPlayerDef.h"
#import "IosPlugin.h"
#import "VideoPlugin.h"
#import "ImagePlugin.h"
#import "M1VideoPlugin.h"
@class UIView;
@interface IosPanoPlayer : NSObject
@property(atomic, assign) int winWidth;
@property(atomic, assign) int winHeight;
@property(nonatomic, assign) PanoViewMode curViewMode;
@property(atomic, weak) id <IPanoPlayerDelegate> panoPlayerdelegate;
@property(atomic, weak) id <IPanoPlayerPluginDelegate> panoPlayerPluginDelegate;
 /*****内部使用和功能拓展使用api start*****/
- (void)onSurfaceCreated;

- (void)onSurfaceChanged:(int)width height:(int)height;

- (void)onDrawFrame;

- (void)setDefaultFrameBufferObject:(int)defaultFramebuffer;

- (void)close;

- (void*)getCommonPanoPlayer;

/*****内部使用和功能拓展使用api end*****/

- (void)play:(PanoData *)panoData;
- (void)replay;

- (void)draw;
- (void)play:(PanoData *)panoData options:(NSMutableArray<PanoPlayerOption *> *)options;
- (void)loadPano:(NSString*)name options:(NSMutableArray<PanoPlayerOption *> *)options;
- (void)loadPano:(NSString*)name viewmode:(PanoViewMode)viewmode options:(NSMutableArray<PanoPlayerOption *> *)options;

- (void)setPauseTime:(float)time;
- (void)setAutoRotate:(bool) autoplay :(float) hlookat;
- (void)setWeight:(NSArray<NSString*>*) fileAbsolutePath;//设置weight纹理，为f4 he m1服务

- (void)setreverse:(bool)is_up_down;//设置相机是否倒置
- (UIView*)gethotview;//set hotpot view
- (void)sethotview :(UIView*)hview;
- (void)setCurrentGestureData:(float)fov hlookat:(float)hlookat vlookat:(float) vlookat;
- (void)getCurrentGesturedata:(float *)gesData;

- (void)setPointSelecting:(bool)isPointSelecting;//设置点选开关，为真时，fov不受模式的最大最小值限制
/**
 * 带有动画的模式切换
 * @param viewMode 模式
 * @param duration 动画时长
 * @param type 动画类型
 */
- (void)setAnimationViewMode:(PanoViewMode)viewMode duration:(float)duration type:(EaseTypes)type;
- (void)setAnimationViewMode:(PanoViewMode)viewMode type:(EaseTypes)type;
/**
 //设置离场动画

 @param detafov fov变化量
 @param duration 动画时长
 @param easeType 动画曲线
 */
-(void) setanimationfov:(float)detafov duration: (float) duration type:(EaseTypes) easeType;
/**
 * 不带动画的模式切换
 * @param viewMode
 */
- (void)setViewMode:(PanoViewMode)viewMode;
/**
 * 获取当前画面截图， 输出数据为RGBA数据
 * @param callBack
 */
- (void)getScreenShot:(void (^)(int width, int height, unsigned char *data))callBack;

/**
 * 设置log级别
 * @param logLevel
 */
- (void)setLogLevel:(PanoLogLevel)logLevel;
- (Plugin *)getPlugin;

//经纬度和屏幕坐标相互转换
/**
 通过屏幕坐标转换经纬度
 @param px 屏幕上x方向的点
 @param py 屏幕上y方向的点
 @param outdeg 输出经纬度[0]为经度，[1]为纬度
 */
- (void) calDegByWinPoint:(float) px :(float) py : (float*)outdeg;
- (void) calDegByWinPointleft:(float) px :(float) py : (float*)outdeg;
- (void) calDegByWinPointRight:(float) px :(float) py : (float*)outdeg;

/**
  通过经纬度转换屏幕坐标
 @param degX 经度
 @param degY 纬度
 @param sw 当前热点的宽
 @param sh 当前热点高
 @param out 输出屏幕坐标
 */
- (void) calWinPointByDeg:(float) degX :(float) degY  hotwidth: (int) sw hotheight: (int)sh outwin:(float*)out;
- (void) calWinPointByDegleft:(float) degX :(float) degY  hotwidth: (int) sw hotheight: (int)sh outwin:(float*)out;
- (void) calWinPointByDegright:(float) degX :(float) degY  hotwidth: (int) sw hotheight: (int)sh outwin:(float*)out;
//获取当前场景信息
-(PanoData*)getCurrentPanoramaData;
-(void) setCurImageDataCalibration:(NSString*) cali;//set f4/m1 biaoding para

-(void)addLiteDecor:(LiteDecor*)liteDecor;
-(void)updateLiteDecorLayoutParamsSect:(NSString*)tag params:(LayoutParams*)params;
-(void)deleteLiteDecor:(NSString*)tag;
@end
