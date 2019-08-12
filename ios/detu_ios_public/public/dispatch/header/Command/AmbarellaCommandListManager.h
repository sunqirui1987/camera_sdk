//
//  AmbarellaCommandListManager.h
//  DeTuZZN
//
//  Created by lsq on 16/11/24.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface AmbarellaCommandListManager : NSObject{
    
    int tail;
    dispatch_semaphore_t sem;
}

@property(nonatomic, strong) NSMutableArray *commandList;

- (NSDictionary *)readCommand;

- (void)addCommandToFIFO:(NSDictionary *)commandDict;

- (void)addCommandToFIFOFront:(NSDictionary *)commandDict;

- (void)removeAllCommand;

@end
