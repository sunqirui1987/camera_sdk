//
//  ReVideoDecoder.h
//  remuxmediapano
//
//  Created by chao on 2017/8/4.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "re_config.h"

@protocol ReVideoDecoderDelegate <NSObject>
-(void)onVideoDecoderGetFrame:(obs_source_frame_s *)frame;
-(void)onVideoDecoderEnd;
@end

@interface ReVideoDecoder : NSObject
@property(nonatomic, weak) id <ReVideoDecoderDelegate> delegate;
-(void)setFrameCallBack:(obs_source_frame_s *)frame;
-(void)endFrameCallBack;

-(MediaSourceMetaData)start:(NSString*)path;
-(void)stop;

@end
