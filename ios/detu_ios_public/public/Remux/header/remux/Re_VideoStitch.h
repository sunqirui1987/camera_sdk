//
//  GLPlayerView.h
//  IJKMediaDemo
//
//  Created by qiruisun on 16/5/20.
//  Copyright © 2016年 bilibili. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UiKit/UIImage.h>

typedef NS_ENUM(NSInteger, StitchState) {
    StitchState_OK, //转码完成
    StitchState_ABORT, //转码被取消
    StitchState_ERROR //转码出错
};

@protocol IStitchDelegate <NSObject>
-(void)onStitchProgressChanged:(int)progress;
-(void)onStitchStateChanged:(StitchState) state;
@end

typedef NS_ENUM(NSInteger, StitchDeviceId) {
    StitchDeviceId_TWINS, //双鱼眼
    StitchDeviceId_SPHERE, //单鱼眼
    StitchDeviceId_FLAT //平面
};

@interface StitchParam : NSObject
//both picture and video
@property(nonatomic, strong)NSString* _Nullable path; //原始文件路径
@property(nonatomic, strong)NSString* _Nullable savePath; //转出文件存储路径
@property(nonatomic, assign)int panoWidth; //输出分辨率宽度
@property(nonatomic, assign)int panoHeight; //输出分辨率高度
@property(nonatomic, strong)NSString* _Nullable calibration; //标定信息
@property(nonatomic, assign)StitchDeviceId deviceId; //设备id

//for video only
@property(nonatomic, assign)int fps; //输出视频帧率
@property(nonatomic, assign)int bitRate; //输出视频码率
@end

@interface Re_VideoStitch : NSObject
@property(nonatomic, weak) id <IStitchDelegate> delegate;
/**
 *开始转码视频
 */
-(void)startStitchVideo:(StitchParam*_Nullable) param;

/**
 *停止转码视频
 */
-(void)stopStitchVideo;

/**
 *普通转码图片
 */
-(BOOL)stitchImage:(StitchParam*_Nullable) param;

/**
 *多重融合转码图片
 */
-(BOOL)stitchImageByMultiBlend:(StitchParam*_Nullable) param;

@end
