//
//  ZZNDownLoadFwInfo.h
//  DeTuZZN
//
//  Created by shenxing on 15/10/16.
//  Copyright © 2015年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZZNFwInfoItem.h"

//下载到本地的固件数据
@interface ZZNDownLoadFwInfo : NSObject

/**
 *  固件列表数据
 */
@property (nonatomic,strong) NSMutableArray *infoList;


/**
 *  根据硬件设备号获取对应的固件信息
 *
 *  @param deviceId 硬件设备号
 *
 *  @return ZZNFwInfoItem＊ 固件信息
 */
- (ZZNFwInfoItem*) getFwInfoItemByDeviceId:(NSString*)deviceId;

/**
 *  从网上更新最新固件数据
 *
 *  @param arr 网上最新的固件数据
 */
- (void) parseWebNewestFwInfos:(NSArray*)arr;

/**
 *  保存在本地
 */
- (void) saveToLocal;

@end
