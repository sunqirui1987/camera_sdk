//
//  TwinnDispatcher.h
//  DeTuZZN
//
//  Created by Seth on 16/11/29.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import "MachineBaseDispatcher.h"
#import "TwinnCommand.h"

@interface TwinnDispatcher : MachineBaseDispatcher

@property (nonatomic, strong) TwinnCommand * dispatcher;

@end
