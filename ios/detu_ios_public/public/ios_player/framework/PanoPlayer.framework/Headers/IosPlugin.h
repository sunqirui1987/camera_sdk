//
//  IosPlugin.h
//  PanoPlayer
//
//  Created by chao on 2017/10/26.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IosPanoPlayerDef.h"

#define IOS_PLUGIN_MAX_PLANE 4

typedef enum PluginMediaType
{
    PluginMediaType_VIDEO,
    PluginMediaType_PIC,
} PluginMediaType;

typedef enum PluginColorFormat
{
    PluginColorFormat_RGBA,
    PluginColorFormat_ARGB,
    PluginColorFormat_ABGR,
    PluginColorFormat_BGRA,
    PluginColorFormat_RGB24,
    PluginColorFormat_BGR24,
    PluginColorFormat_YUV420P,
    PluginColorFormat_YV12,
    PluginColorFormat_NV12,
    PluginColorFormat_NV21,
    PluginColorFormat_UYVY422,
    PluginColorFormat_OPENGL_RGBA_TEXTURE,
} PluginColorFormat;

@interface PluginMetaData : NSObject
@property(nonatomic, assign)PluginMediaType mediaType;
@property(nonatomic, assign)int width;
@property(nonatomic, assign)int height;
@property(nonatomic, assign)PluginColorFormat pluginFormat;
@property(nonatomic, strong)NSArray* lineSize;
@property(nonatomic, assign)int videoBitRate;
@property(nonatomic, assign)float videoFrameRate;
@property(nonatomic, assign)long duration;
@property(nonatomic, assign)int audioBitRate;
@property(nonatomic, assign)int audioSampleRate;
@property(nonatomic, strong)NSString* calibration;
@end

typedef enum PluginState
{
    PluginState_PREPARED,
    PluginState_PLAYING,
    PluginState_PAUSE,
    PluginState_STOP,
    PluginState_SEEK_COMPLETE,
    PluginState_COMPLETED,
    PluginState_ERROR,
    PluginState_DECODER_CHANGE
} PluginState;

typedef struct PluginFrame
{
    uint8_t* data[IOS_PLUGIN_MAX_PLANE];
    int planes;
    void* opaque;
} PluginFrame;

@interface Plugin : NSObject
-(void)setPanoData:(PanoData*) panoData options:(NSMutableArray<PanoPlayerOption*>*) options;
-(void)notifyMetaDatas:(NSArray<PluginMetaData*>*) metaDatas;
-(void)notifyStateChanged:(PluginState) state tip:(NSString*) tip;
-(void)notifyProgressChanged:(long) playTime bufferTime:(long) bufferTime duration:(long) duration;
-(void)notifyFramesChanged:(PluginFrame*) frames count:(int) count;

-(NSArray<PluginMetaData*>*)getMetaDatas;
-(void*)getCommonPlugin;
-(void)setCommonPlugin:(void*) commonPlugin;
-(NSString*)getDescription;
@end
