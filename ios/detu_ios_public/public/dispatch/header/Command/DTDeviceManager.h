//
//  DTDeviceManager.h
//  DeTuZZN
//
//  Created by Seth on 16/11/22.
//  Copyright © 2016年 DETU. All rights reserved.
//

/**
 *  备管理器 管理连接相机
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


UIKIT_EXTERN NSNotificationName const DTDeviceCameraDidChangedNotification;


@interface DTDeviceManager : NSObject

@property (nonatomic, assign) int  curConnDevice;      ///< 当前连接的设备
@property (nonatomic, assign) int  preConnDevice;      ///< 上一次连接的设备
@property (nonatomic, copy) NSString * curWifiName;    ///< 当前连接的wifi名
@property (nonatomic, copy) NSString * preWifiName;    ///< 上一次连接的wifi名
@property (nonatomic, copy) NSString * preDeviceName;  ///< 设备前置名称
@property (nonatomic, copy) NSString * device;         ///< 设备

+ (instancetype)sharedInstance;
- (void) config;

/**
 *  @abstract 获取完整的型号名称
 */
- (NSString *) getDeviceFullName;

/**
 *  @abstract 通过具体型号，获取与播放器协议好的数字，sphere800为1，主要用来传于播放器识别。
 */
- (NSString *) getMachineName;

/**
 *  @abstract 单眼为11 ,双眼为2002 , 拼接好的为0
 */
- (NSString *)getPlayDeviceWithDevice:(NSString *)device fileType:(int )fileType ;
- (NSString *)panoPlayerXml;
- (NSString *)panoPlayerXmlForTwinN;
- (NSString *)panoPlayerXmlForThetaSLive;
- (NSString *)panoPlayerXmlForAmba;
- (NSString *)panoramaPlayerXml;
- (NSString *)panoPlayerXmlForThetaS;

@end
