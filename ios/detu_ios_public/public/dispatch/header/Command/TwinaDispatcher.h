//
//  TwinaDispatcher.h
//  DeTuZZN
//
//  Created by Seth on 16/11/29.
//  Copyright © 2016年 DETU. All rights reserved.
//

#import "MachineBaseDispatcher.h"
#import "MachineBaseDispatcher.h"
#import "TwinaCommand.h"



@interface TwinaDispatcher : MachineBaseDispatcher

@property (nonatomic, strong) TwinaCommand * dispatcher;
- (void)cancel ;
//查询VF状态
-(void)getVFState:(resultResponseBlock)responseBlock;
//stop VF
- (void)stopVF:(resultResponseBlock)responseBlock;
//start VF
- (void)startVF:(resultResponseBlock)responseBlock;
//设置WIFI制式
- (void)setWiFiChannel:(NSString *)mode callBack:(resultResponseBlock)responseBlock;
//stop session
- (void)stopSessionOrStopSocket:(BOOL)abool callBack:(resultResponseBlock)responseBlock;
//读取文件缩略图数据
- (void)getThumb:(NSString *)filePath callBack:(resultResponseBlock)responseBlock;
// 固件升级 文件路径
- (void)UpdateFW:(NSString *)filePath
             pro:(void(^)(int))progress
             res:(void(^)(BOOL))res;
// 固件升级之前的操作
- (void)connectDataSocketAndSetClientInfoCallBack:(resultResponseBlock)responseBlock ;

// 停止固件升级的数据传输
- (void)stopUploadFireWare;

// 暂停缩略图下载
- (void)pauseLoadThumb;

// 进入固件升级模式
- (void)setUpdateMode:(NSString *)filename callBack:(resultResponseBlock)responseBlock;

// 告诉相机传完数据了可以进行文件校验了
- (void)setCameraStartUpdateRes:(resultResponseBlock)responseBlock;


@end
