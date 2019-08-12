//
//  ZZNDataModel.h
//  DeTuZZN
//
//  Created by ltd on 15/7/31.
//  Copyright (c) 2015年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ZZNDataModel : NSObject

@property (retain,nonatomic,readonly) NSArray * imageNameArray;
@property (retain,nonatomic,readonly) NSArray * adTitleArray;

- (instancetype)initWithImageName;
- (instancetype)initWithImageNameAndAdTitleArray;
+ (id)adDataModelWithImageName;
+ (id)adDataModelWithImageNameAndAdTitleArray;

@end
