//
//  ZZNCameraSettingPickerItem.h
//  DeTuZZN
//
//  Created by shenxing on 15/8/6.
//  Copyright (c) 2015年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
//相机设置用到的数据结构
@interface ZZNCameraSettingPickerItem : NSObject

@property int key;
@property NSString* label;

+(ZZNCameraSettingPickerItem*) initWithKey:(int)key label:(NSString*)label;

@end
