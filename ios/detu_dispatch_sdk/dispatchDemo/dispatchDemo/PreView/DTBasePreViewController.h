//
//  DTBasePreViewController.h
//  dispatchdemo
//
//  Created by lsq on 17/1/10.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "UIViewController+UE.h"
#import "MainDispatcher.h"

//播放器
#import "PanoPlayer.h"
#import "PanoPlayerUrl.h"
#import "GLSurfaceWidget.h"

@interface DTBasePreViewController : UIViewController


@property (nonatomic,strong)PanoPlayer *player;
@property(nonatomic, strong)GLSurfaceWidget* glWidget;



@property (nonatomic,strong)UIView *preview;
@property (nonatomic,copy)NSString *device;
@property (nonatomic,strong)UIButton *changeModeBtn;
@property (nonatomic,assign)BOOL  recordMovie;
@property (nonatomic,copy)NSString *rtspPath ;
@property (nonatomic,assign)int deviceType;// 1是800 2是S 3是amba

-(void)openRTSPStream;
-(void)clearPlayer;


-(void)takePhoto:(id)sender;

-(void)takeMovie:(id)sender;
-(void)setting:(id)sender;
-(void)enterAlbum:(id)sender;

-(void)changeModel;
-(void)shotSuccessAlertShow;
-(void)shotFaileAlertShow;

@end
