//
//  ZZNSpSDKDataTimeListItem.h
//  DeTuZZN
//
//  Created by shenxing on 15/7/30.
//  Copyright (c) 2015年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
//按时间分组用到的数据结构
@interface ZZNSpSDKDataTimeListItem : NSObject
@property(strong,nonatomic)NSMutableArray *list;
@property NSInteger month;
@property NSInteger year;
@property NSInteger day;
@property NSInteger numForSort;
@end
