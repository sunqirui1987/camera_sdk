//
//  SpheresDispatcher.h
//  DeTuZZN
//
//  Created by Seth on 16/11/29.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MachineBaseDispatcher.h"
#import "SpheresCommand.h"

@interface SpheresDispatcher : MachineBaseDispatcher

@property (nonatomic, strong) SpheresCommand * dispatcher;

@end
