//
//  APPUtil.h
//  dispatchlib
//
//  Created by Seth on 2017/7/28.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface APPUtil : NSObject

+ (void)hookClass:(Class )cls
           method:(SEL)sel
        withBlock:(void(^)())block;
@end
