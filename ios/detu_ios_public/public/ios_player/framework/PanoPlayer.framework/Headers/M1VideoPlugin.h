//
//  M1VideoPlugin.h
//  PanoPlayer
//
//  Created by chao on 2017/11/8.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "IosPlugin.h"

#define M1_PLUGIN_DESCRIPTION_VIDEO @"m1_video_plugin"

@interface M1VideoPlugin : Plugin

-(void)start;

-(void)close;

-(void)refresh;

@end
