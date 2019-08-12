//
//  GLSurfaceWidget.h
//  PanoPlayer
//
//  Created by chao on 2017/10/23.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "IosPanoPlayer.h"
@interface GLSurfaceWidget : UIView
@property(nonatomic, strong) IosPanoPlayer *panoPlayer;
@property(atomic, assign) int windowWidth;
@property(atomic, assign) int windowHeight;
- (id)initWithFrame:(CGRect)frame withPanoPlayer:(IosPanoPlayer *)panoPlayer;

- (id)initWithFrame:(CGRect)frame withPanoPlayer:(IosPanoPlayer *)panoPlayer renderFps:(int) fps;

- (void)onResume;

- (void)onPause;

- (void)onStop;

/**
 * 手势缩放开关
 * @param toggle
 */
- (void)setZoomEnable:(bool)toggle;

-(BOOL)getZoomEnable;


/**
 * 手势功能开关
 * @param toggle
 */
- (void)setGestureEnable:(bool)toggle;

-(BOOL)getGestureEnable;

/**
 * 陀螺仪功能开关
 * @param toggle
 */
-(void)setGyroEnable:(bool)toggle;

-(BOOL)getGyroEnable;


/**
 陀螺仪手势共存开关
 @param toggle
 */
-(void)setGyroModeShouldMove:(bool)toggle;
-(BOOL)getGyroModeShouldMove;
@end
