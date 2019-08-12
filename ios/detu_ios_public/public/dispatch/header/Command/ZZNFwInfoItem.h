//
//  ZZNFwInfoItem.h
//  DeTuZZN
//
//  Created by shenxing on 15/10/16.
//  Copyright © 2015年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
//固件信息
@interface ZZNFwInfoItem : NSObject <NSCoding>

/**
 *  硬件设备号
 */
@property (nonatomic,copy) NSString* deviceId;

/**
 *  固件版本号
 */
@property (nonatomic,copy) NSString* fwVersion;

/**
 *  固件描述
 */
@property (nonatomic,copy) NSString* fwDes;

/**
 *  固件更新时间
 */
@property (nonatomic,copy) NSString* updateTime;

/**
 *  下载的地址
 */
@property (nonatomic,copy) NSString* downloadPath;

/**
 *  下载完成后本地的地址
 */
@property (nonatomic,copy) NSString* localPath;

/**
 *  下载完成后本地的bin文件名字
 */
@property (nonatomic,copy) NSString* localFileName;

@end
