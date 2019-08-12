//
//  ZZNPictureBrowserItem.h
//  DeTuZZN
//
//  Created by shenxing on 15/8/3.
//  Copyright (c) 2015年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FileListEntiy.h"
#import "ZZNPanorama.h"
#import "ZZNMovieData.h"
#import "ZZNTempItem.h"
#import "AmbaPhotoAndVideoModel.h"
typedef NS_ENUM(NSInteger, ZZNDataFromWhere) {
    ZZNDataFromLocal = 0,
    ZZNDataFromWeb = 1,
    ZZNDataFromHard = 2
};

//显示图片或者视频用到的数据结构
@interface ZZNPictureOrMovieBrowserItem : NSObject
@property  NSString * createTime;//创建时间
@property  NSString * url;//播放路径
@property  NSString * title;//名称
@property  ZZNDataFromWhere fromWhere;//数据从哪个平台过来的
@property NSString *currentpath; //测试
@property  NSNumber * longitude;//经度
@property  NSNumber * latitude;//纬度

@property  NSString * hardKey;//硬件key 用地址
@property  NSString * localKey;//本地key 用地址
@property  NSString * webKey;//云端key fromWhere为ZZNDataFromWeb有效

@property  NSString * diskPath;//删除硬件时用
@property  NSString * fileDirectory;//安霸文件目录
@property  NSString* fileSize;//文件大小

@property  NSString* resolutionRatio;//分辨率

@property  int fileType;//文件类型 1照片 2视频

@property NSString *device;//设备号

@property NSString *rotate;//方向

@property NSString *app_config;//播放的XML
@property (nonatomic, assign) int qualityDef; //默认清晰度
@property (nonatomic, assign) int qualityMax; //最大清晰度
@property (nonatomic, assign) BOOL isTemp;//是否为临时文件（theta 和 twin）
@property BOOL islocalHaveToPlayer;//本地是否有这个文件，有的话替换播 fromWhere为ZZNDataFromWeb有效

@property  ZZNPanorama* pano;//图片数据
@property  ZZNMovieData* movie;//视频数据

@property  NSString * domainname;//作者id fromWhere为ZZNDataFromWeb有效
@property NSURL *previewURL;//缩略图地址fromWhere为ZZNDataFromWeb有效

@property NSString *width;//宽
@property NSString *height;//高
@property (nonatomic, strong) ZZNTempItem *tempItem;
//根据相机的数据结构解析
-(void)parseFileEntiy:(FileEntiy*)file;
//根据本地图片的数据结构解析
-(void)parseLocalPic:(ZZNPanorama*)pic;
//根据本地视频的数据结构解析
-(void)parseLocalMovie:(ZZNMovieData*)movie;

//根据云端的图片数据结构解析

-(void)parseWebPic:(ZZNPicModel*)webPic;
//根据云端的视频数据结构解析
-(void)parseWebMovie:(ZZNMovModel*)webMovie;

//创建FileEntiy
-(FileEntiy*)createFileEntiy;

//云端key
-(NSString *)getWebKey;

//解析临时数据
- (void)parseTempItem:(ZZNTempItem *)item;
//系统相册
- (void)pareLocalPhoto:(NSString *)url device:(NSString *)device type:(int )type name:(NSString *)name;


//安霸相机的数据结构解析
-(void)parseAmbaFileEntiy:(AmbaPhotoAndVideoModel*)file;

@end



