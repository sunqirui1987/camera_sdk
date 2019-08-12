//
//  DTGetSensor.h
//  StitchTest
//
//  Created by lsq on 2017/4/1.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ImageIO/ImageIO.h>
#import <UIKit/UIKit.h>

@interface DTGetSensor : NSObject {
@private
    CGImageSourceRef imageRef;
}

/**
 *  当前的url
 */
@property(copy) NSString * resourceUrl;

/**
 *  当前标定
 */
@property(copy) NSString * sensor;


+ (instancetype)shareInstance ;

- (NSString *)getVideoSensorStringWith:(NSString *)url device:(NSString *)device ;

- (NSString *)getImageSensorStringWith:(NSString *)url ;



/*初始化方法
 *parms imageUrl 图片路径
 */
- (id)initWithURL:(NSURL*)imageUrl;

//照片EXIF
@property(strong) NSDictionary * imageExifDictionary;
//照片Tiff
@property(strong) NSDictionary * imageTiffDictionary;

@property(strong) NSDictionary * imageJfifDictionary;

//所有照片信息
@property(strong) NSDictionary * imageProperty;

@property(assign,nonatomic) NSInteger  imageFileSize;
@property(strong)           NSString * imageFileType;


@end
