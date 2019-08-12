//
//  DTStitch.h
//  StitchTest
//
//  Created by lsq on 2017/3/31.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DTStitchModel.h"
#import <CoreGraphics/CoreGraphics.h>

@interface DTStitch : NSObject

+ (instancetype)sharedInstance;

/**
 * 视频转码
 *
 * @param stitchModel   DTStitchModel
 * @param viewSize      转码大小2k(2048, 1024),3k(3040, 1520)
 * @param errorBlock    错误回调
 * @param progressblock 转码进度回调
 * @param completeblock 转码成功失败回调
 */
- (void)videoStitchWithItem:(DTStitchModel *)stitchModel
                   ViewSize:(CGSize)viewSize
                      error:(void (^)(NSString *error))errorBlock
                   progress:(void(^)(float progress))progressblock
                   complete:(void(^)(BOOL success))completeblock ;

/**
 * 图片转码
 *
 * @param stitchModel   DTStitchModel
 * @param viewSize      转码大小2k(2048, 1024),3k(3040, 1520)
 * @param errorBlock    错误回调
 * @param progressblock 转码进度回调
 * @param completeblock 转码成功失败回调
 */
- (void)imageStitchWithItem:(DTStitchModel *)stitchModel
                   ViewSize:(CGSize)viewSize
                      error:(void (^)(NSString *error))errorBlock
                   progress:(void(^)(float progress))progressblock
                   complete:(void(^)(BOOL success))completeblock ;

- (void)stop ;

@end
