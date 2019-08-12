//
//  UIViewController+UE.h
//  DeTuZZN
//
//  Created by Seth on 16/9/6.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MBProgressHUD.h"
#import <objc/runtime.h>
@interface UIViewController (UE)

- (void)showAlertIndictorWithMessage:(NSString *)message withDelay:(NSTimeInterval)time ;

- (void)hideAlertIndictor ;

@end
