//
//  VideoPlugin.h
//  PanoPlayer
//
//  Created by chao on 2017/10/26.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IosPlugin.h"

#define PLUGIN_DESCRIPTION_VIDEO @"video_plugin"

@interface VideoPlugin : Plugin
-(void)setPanoData:(PanoData*) panoData options:(NSMutableArray<PanoPlayerOption*>*) options;
-(void)start;
-(void)pause;
-(void)stop;
-(void)close;
-(void)refresh;
-(void)setVolume:(float) volume;
-(float)getVolume;
-(bool)isPlaying;
-(void)seekTo:(long) msec;
-(NSString*)getDescription;
@end
