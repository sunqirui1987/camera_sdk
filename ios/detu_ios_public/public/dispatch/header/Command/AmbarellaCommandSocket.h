//
//  AmbarellaCommandSocket.h
//  DeTuZZN
//
//  Created by lsq on 16/11/24.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AmbarellaCommand.h"
#import "GCDAsyncSocket.h"
#import "AmbarellaCommandListManager.h"

#define AMBARELLA_COMMANDSOCKET_TIMEOUT            5       //socket连接超时时间
#define AMBARELLA_COMMANDSOCKET_SENDDATA_TIMEOUT   5       //发数据超时时间
#define AMBARELLA_COMMANDSOCKET_READ_TIMEOUT       -1       //接收数据超时时间


@protocol  AmbarellaCommandSocketDelegate <NSObject>
@optional

//端口连接成功
-(void)commandSocketDidConnect:(NSString *)connectHost onPort:(int)port;

//端口连接失败,超时
-(void)commandSocketDisConnect:(NSError *)error;

//接收数据
-(void)commandSocketReceiveData:(NSDictionary *)receiveData;

@end

@interface AmbarellaCommandSocket : NSObject <GCDAsyncSocketDelegate>

@property (strong, nonatomic) GCDAsyncSocket              *ambarellaCommandSocket;
@property (nonatomic, weak) id<AmbarellaCommandSocketDelegate> ambarellaCommadSocketDeleage;
@property (nonatomic, strong) AmbarellaCommandListManager *commandListManager;
@property (nonatomic, assign) BOOL commandIsFinish;
@property (nonatomic, assign) BOOL isSessionConnect;

//+ (instancetype)shareInstance;

//建立接收数据sorcket连接
-(void)connectToCommandSocketWithHost:(NSString *)host onPort:(uint16_t)port res:(void(^)(BOOL result))res;

//关闭socket
-(void)closeCommandSocketConnect;


-(void)addCommand:(NSMutableDictionary *)commandDic;

-(void)addCommandFront:(NSMutableDictionary *)commandDic;

@end
