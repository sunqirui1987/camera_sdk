//
//  downloadlib.h
//  downloadlib
//
//  Created by lsq on 2017/3/30.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DTdownloadModel.h"

@interface downloadlib : NSObject


+ (instancetype)sharedInstance;

/**
 *  下载
 *
 *  @param downloadModel  下载模型 DTdownloadModel
 *  @param progressBlock  下载进度的回调
 *  @param errorBlock     错误信息的回调
 *  @param completeBlock  成功失败的回调
 */
- (void)downloadWithModel:(DTdownloadModel *)downloadModel
                 progress:(void (^)(float progress))progressBlock
                    error:(void (^)(NSError *error))errorBlock
                 complete:(void (^)(BOOL downloadFinished, NSString *pathToFile))completeBlock;

/*
 *删除缓存
 */
- (void)deleteSandboxFolder;

-(void)stop;

@end
