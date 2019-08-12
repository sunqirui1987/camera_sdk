//
//  DTWIFI.h
//  ambarella_sdk_ios
//
//  Created by detu on 15/11/3.
//  Copyright (c) 2015年 shenxing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>
#import <SystemConfiguration/CaptiveNetwork.h>
@interface DTWIFI : NSObject
//获取WIFI名字
+ (NSString *) getCurrentWifiName;
+ (NSMutableDictionary *) getIPAddress;
//获取IPV4 地址
+ (NSString *) getIPAddress:(BOOL)preferIPv4;
+ (NSString *) getIPAddressip;

- (NSDictionary *) getIPAddresses;


@end
