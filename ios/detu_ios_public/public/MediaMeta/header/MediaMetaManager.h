//
//  MediaMetaManager.h
//  MediaMetaLib
//
//  Created by chao on 2017/1/7.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LiveMediaInfo.h"
#import "CameraMediaInfo.h"
#import "MediaInfo.h"
#import "MetaItem.h"

@interface MediaMetaManager : NSObject

/**
 * @brief 获取相机图片或者视频的元信息
 * @param fileAbsolutePath 源文件绝对地址
 */
-(DTCameraMediaInfo*) getCameraMediaInfo:(NSString*) fileAbsolutePath;

/**
 * @brief 获取直播流元信息
 * @param liveAbsolutePath 直播流绝对地址
 * @param microMills 超时时间，以微秒为单位
 */
-(DTLiveMediaInfo*)getLiveMediaInfo:(NSString*)liveAbsolutePath timeOut:(long)microMills;

/**
 * @brief 设置视频元信息
 * @param srcAbsolutePath 源视频绝对地址
 * @param dstAbsolutePath 目标视频绝对地址
 * @param items 元信息集合
 */
-(BOOL)setVideoMetas:(NSString*)srcAbsolutePath dstPath:(NSString*)dstAbsolutePath metas: (NSArray<MetaItem*>*) items;

/**
 * @brief 设置图片Exif信息
 * @param srcAbsolutePath 图片绝对地址
 * @param items exif信息集合
 */
-(BOOL)setPictureExifs:(NSString*)srcAbsolutePath dstPath:(NSString*)dstAbsolutePath exifs:(NSArray<MetaItem*>*) items;

@end
