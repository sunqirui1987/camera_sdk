//
//  Sphere800Dispatcher.h
//  DeTuZZN
//
//  Created by Seth on 16/11/29.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import "MachineBaseDispatcher.h"
#import "Sphere800Command.h"

@interface Sphere800Dispatcher : MachineBaseDispatcher
@property (nonatomic, strong) Sphere800Command * dispatcher;

@end
