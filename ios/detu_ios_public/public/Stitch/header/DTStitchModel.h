//
//  DTStitchModel.h
//  StitchTest
//
//  Created by lsq on 2017/3/31.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DTStitchModel : NSObject

/*
 * 设备号
 */
@property(nonatomic,copy)NSString *device;

/*
 * 需转码的文件地址
 */
@property(nonatomic,copy)NSString *stitchPath;

/*
 * 转码成功文件保存路径
 */
@property(nonatomic,copy)NSString *savePath;

/*
 * 标定参数
 */
@property(nonatomic,copy)NSString *sensor;

/*
 * 图片转码需传创建时间 2017/03/31 13:31:02
 */
@property(nonatomic,copy)NSString * createTime;

@end
