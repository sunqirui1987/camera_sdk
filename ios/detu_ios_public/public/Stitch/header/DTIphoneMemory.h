//
//  DTIphoneMemory.h
//  StitchTest
//
//  Created by lsq on 2017/4/6.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DTIphoneMemory : NSObject

+ (instancetype)sharedInstance;

- (double)re_availableMemory ;

- (double)availableMemory;

- (double)usedMemory;

-(long long)getAvailableMemorySize;


@end
