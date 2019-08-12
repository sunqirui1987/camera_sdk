//
//  AmbarellaDataSocket.h
//  DeTuZZN
//
//  Created by lsq on 16/11/24.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AmbarellaCommand.h"
#import "GCDAsyncSocket.h"


#define AMBARELLA_DATASOCKET_TIMEOUT            30      //socket连接超时时间
#define AMBARELLA_DATASOCKET_SENDDATA_TIMEOUT   60       //发数据超时时间

enum{
    SocketOfflineByServer,      //服务器掉线
    SocketOfflineByUser,        //用户断开
    SocketOfflineByWifiCut,     //wifi 断开
};

@protocol  AmbarellaDataSocketDelegate <NSObject>
@optional

// 端口连接成功
-(void)dataSocketDidConnect:(NSString *)connectHost onPort:(int)port;

// 端口连接失败,超时
-(void)dataSocketDisConnect:(NSString *)error;

// 接收数据
-(void)dataSocketReceiveData:(NSData *)receiveData;

@end

@interface AmbarellaDataSocket : NSObject <GCDAsyncSocketDelegate>

@property (strong, nonatomic) GCDAsyncSocket              *ambarellaDataSocket;
@property (nonatomic, weak) id<AmbarellaDataSocketDelegate> ambarellaDataSocketDeleage;

@property (nonatomic, assign) BOOL ambarellaDataSocketfinish;



//建立接收数据sorcket连接
-(BOOL )connectToDataSocketWithHost:(NSString *)host onPort:(uint16_t)port;

 //关闭socket
-(void)closeDataSocketConnect;

//传数据到socket
-(void)writeDataToDataSocket:(NSData *)data;

@end
