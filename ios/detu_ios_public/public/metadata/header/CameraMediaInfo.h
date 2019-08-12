//
//  CameraMediaInfo.h
//  MediaMetaLib
//
//  Created by chao on 2017/4/6.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "MediaInfo.h"

typedef NS_ENUM(NSInteger, DTCameraId) {
    //单鱼眼
    DT_Sphere800 = 0,
    DT_SphereS = 1,
    
    //双鱼眼
    DT_Twin_01 = 10, //TB401
    DT_Twin_02 = 11, //TB402
    DT_Twin_03 = 12, //TB403
    DT_Liveman_D1 = 13,  //TB404
    DT_Dragon = 14,      //DB405
    DT_NIX = 15,         //NB406
    
    //四鱼眼
    DT_F4 = 100,    //F4
    DT_F4_Pro = 101, //F4_Pro
    
    //大致类型
    DT_OneFishEye = 200,
    DT_TwoFishEye = 201,
    DT_FourFishEye = 202,
    DT_UnKnowCamera = 203
};

@interface DTCameraMediaInfo : DTMediaInfo

@property(nonatomic, assign)DTCameraId cameraId;
@property(nonatomic, copy)NSString* calibration;
@property(nonatomic, copy)NSString* serialNumber;

-(int)getPlayerDevice;

@end
