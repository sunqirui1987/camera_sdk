//
//  DTBasePreViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/10.
//  Copyright © 2017年 detu. All rights reserved.
//
//RGB颜色转换（16进制->10进制）
#define UIColorFromRGB(rgbValue)    [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

#define ZZN_LABEL_COLOR_SCHEME_COLOR UIColorFromRGB(0xffc600) //橙色

#import "DTBasePreViewController.h"
#import "MainDispatcher.h"
#import "MachineBaseDispatcher.h"




@interface DTBasePreViewController ()<IPanoPlayerDelegate>
@property (nonatomic, assign) long long previousTimeSamp ;  /// < 统计码率的发送时间

@end

@implementation DTBasePreViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    
    [self initUI];
    
    [self initNav];
}

-(void)initUI{
    
    self.preview = [[UIView  alloc] init];
    self.preview.frame = CGRectMake(0, 49, self.view.frame.size.width, 400);;
    [self.view addSubview:self.preview];
    self.preview.backgroundColor = [UIColor blackColor];

    //拍照按钮
    UIButton *takePhotoBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    takePhotoBtn.frame = CGRectMake(30, self.preview.frame.origin.y+self.preview.frame.size.height+40, 65, 30);
    [self.view addSubview:takePhotoBtn];
    [takePhotoBtn setTitle:@"拍照" forState:UIControlStateNormal];
    [takePhotoBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [takePhotoBtn setBackgroundColor:ZZN_LABEL_COLOR_SCHEME_COLOR];
    takePhotoBtn.titleLabel.font = [UIFont systemFontOfSize:15];;
    [takePhotoBtn addTarget:self action:@selector(takePhoto:) forControlEvents:UIControlEventTouchUpInside];
    //录像按钮
    UIButton *takeMovieBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    takeMovieBtn.frame = CGRectMake(self.view.frame.size.width-30-65, self.preview.frame.origin.y+self.preview.frame.size.height+40, 65, 30);
    [self.view addSubview:takeMovieBtn];
    [takeMovieBtn setTitle:@"开始录像" forState:UIControlStateNormal];
    [takeMovieBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [takeMovieBtn setBackgroundColor:ZZN_LABEL_COLOR_SCHEME_COLOR];
    takeMovieBtn.titleLabel.font = [UIFont systemFontOfSize:15];;
    [takeMovieBtn addTarget:self action:@selector(takeMovie:) forControlEvents:UIControlEventTouchUpInside];

    //模式切换按钮
    self.changeModeBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    self.changeModeBtn.frame = CGRectMake(self.view.frame.size.width-30-65, self.preview.frame.origin.y+self.preview.frame.size.height+40, 65, 30);
    self.changeModeBtn.center = CGPointMake(self.view.frame.size.width / 2, takePhotoBtn.center.y);
    [self.view addSubview:self.changeModeBtn];
    if ([MainDispatcher shareInstance].cameraInfo.nowRecordMode == WIFI_APP_MODE_MOVIE) {
        [self.changeModeBtn setTitle:@"录像模式" forState:UIControlStateNormal];
    }else if([MainDispatcher shareInstance].cameraInfo.nowRecordMode == WIFI_APP_MODE_PHOTO){
        [self.changeModeBtn setTitle:@"拍照模式" forState:UIControlStateNormal];
    }
    [self.changeModeBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [self.changeModeBtn setBackgroundColor:ZZN_LABEL_COLOR_SCHEME_COLOR];
    self.changeModeBtn.titleLabel.font = [UIFont systemFontOfSize:15];;
    self.changeModeBtn.hidden = YES;
    [self.changeModeBtn addTarget:self action:@selector(changeModel) forControlEvents:UIControlEventTouchUpInside];

    //相册按钮
    UIButton *albumBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    albumBtn.frame = CGRectMake(self.view.frame.size.width-30-65, self.preview.frame.origin.y+self.preview.frame.size.height+40+40, 65, 30);
    [self.view addSubview:albumBtn];
    [albumBtn setTitle:@"相册" forState:UIControlStateNormal];
    [albumBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [albumBtn setBackgroundColor:ZZN_LABEL_COLOR_SCHEME_COLOR];
    albumBtn.titleLabel.font = [UIFont systemFontOfSize:15];;
    [albumBtn addTarget:self action:@selector(enterAlbum:) forControlEvents:UIControlEventTouchUpInside];
    
    
}

-(void)changeModel{
    
}

-(void)initNav{
    self.title = @"预览";
    self.view.backgroundColor = [UIColor whiteColor];
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.frame = CGRectMake(0, 0,60,22);
    button.titleLabel.font = [UIFont systemFontOfSize:15];
    [button setTitle:@"设置" forState:UIControlStateNormal];
    [button setTitleColor:ZZN_LABEL_COLOR_SCHEME_COLOR forState:UIControlStateNormal];
    [button addTarget:self action:@selector(setting:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *backItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = backItem;

}

-(void)takePhoto:(id)sender{
    
}

-(void)takeMovie:(id)sender{
    
}

-(void)setting:(id)sender{
    
}
-(void)enterAlbum:(id)sender{
}


-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
//    [self openRTSPStream];

    if (self.deviceType == 2) {
        [[MainDispatcher shareInstance] getCurrentMode:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            if ([MainDispatcher shareInstance].cameraInfo.mechineCurrentMode == PHOTO) {
                NSString* nsString = @"jiang quan dan";
                [MainDispatcher shareInstance].cameraInfo.nowRecordMode = WIFI_APP_MODE_PHOTO;
                [self openRTSPStream];
            }else if ([MainDispatcher shareInstance].cameraInfo.mechineCurrentMode == PLAYBACK){
                // 最后一步直接传入上层回调
                [[MainDispatcher shareInstance] setCurrentMode:[MainDispatcher shareInstance].cameraInfo.nowRecordMode callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
                    [self openRTSPStream];
                }];
            }else {
                [MainDispatcher shareInstance].cameraInfo.nowRecordMode = WIFI_APP_MODE_MOVIE;
                [self openRTSPStream];
            }
            
        }];
    }else{
        [self openRTSPStream];
    }

}
-(void)viewWillDisappear:(BOOL)animated{
    [[MainDispatcher shareInstance] openOrCloseLiveShow:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
    
    }];
    [self clearPlayer];
}
-(void)openRTSPStream{
    
    NSString *xml = @"<?xml version='1.0' encoding='UTF-8' ?><DetuVr><settings init='pano1' initmode='default' enablevr='false' title=''></settings><scenes><scene name='pano1' title='' thumburl=''><preview url='' /><image type = '%type' url ='%url' device='%device' biaoding='%biaoding' /><view  hlookat='270' vlookat='90'  fov='115' vrfov='105' vrz='0.5' righteye='0.1' gyroEnable='false' viewmode='fisheye' /></scene></scenes></DetuVr>";
    
    xml = [xml stringByReplacingOccurrencesOfString:@"%type" withString:@"video"];
    xml = [xml stringByReplacingOccurrencesOfString:@"%url" withString:self.rtspPath];
    xml = [xml stringByReplacingOccurrencesOfString:@"%device" withString: self.device];
    if([MainDispatcher shareInstance].cameraInfo.twinData ) { //如果存在标定就传进去
        xml = [xml stringByReplacingOccurrencesOfString:@"%biaoding" withString: [MainDispatcher shareInstance].cameraInfo.twinData];
    }
    Dispatch_Log(@"xml ->  %@",xml);
    [self showAlertIndictorWithMessage:nil withDelay:20];
    PanoPlayerUrl * panoplayerurl = [[PanoPlayerUrl alloc] init];
    [panoplayerurl setXmlContent:xml];
    
    
  
    /**播放器初始化**/
    self.player = [[PanoPlayer alloc]init];
    self.player.panoPlayerdelegate = self; //播放器参数和Opengl状态回调通知,回调线程在子线程
    self.glWidget = [[GLSurfaceWidget alloc]initWithFrame: CGRectMake(0, 49, self.view.bounds.size.width, 400) withPanoPlayer:self.player];
    [self.view addSubview:self.glWidget];
    [self.glWidget setGyroEnable:false];
    /**end**/
    
    

    NSMutableArray<PanoPlayerOption*>* options = [[NSMutableArray alloc]init];
    
    PanoPlayerOption* option = [[PanoPlayerOption alloc]init];
    option.playerOptionType = PanoPlayerOptionCategoryCodec;
    option.key = @"detu_hw_decoder";
    option.value = @"false";
    [options addObject:option];
    
    
    
    [self.player setLogLevel:PanoLogLevel_WARN];
    [self.player playByXml:panoplayerurl  options:options];
    
   
    

    
}
//- (NSArray *)getPlayerOption
//{
//    PanoPlayerOption* option = [[PanoPlayerOption alloc]init];
//    option.playerOptionType = PanoPlayerOptionCategoryCodec;
//    option.key = @"rtsp_transport";
//    option.value = @"tcp";
//    option.playerOptionValueType = PanoPlayerOptionValueString;
//    PanoPlayerOption* option1 = [[PanoPlayerOption alloc]init];
//    option1.playerOptionType = PanoPlayerOptionCategoryCodec;
//    option1.key = @"hw_decoder";
//    option1.value = @"true";
//    option.playerOptionValueType = PanoPlayerOptionValueString;
//    NSArray<PanoPlayerOption*>* dicts = [[NSArray alloc]initWithObjects:option,option1, nil];
//    return dicts;
//}

-(void)clearPlayer{
   
    [_glWidget onStop];
    [_glWidget removeFromSuperview];
    _glWidget = nil;
    self.player = nil;
    
}
#pragma mark panopalyerDelegate

-(void)onPanoPlayerStatusChanged:(PanoPlayerStatus) status tip:(NSString*) msg {
     dispatch_async(dispatch_get_main_queue(), ^(){
            switch (status) {
                case PanoPlayerStatus_LOADING:
                    Dispatch_Log(@"加载中");
                    break;
                case PanoPlayerStatus_LOADED:
                    Dispatch_Log(@"加载完成");
                    [self hideAlertIndictor];
                    break;
                case PanoPlayerStatus_ERROR:
                    NSLog(@"this is the panpplayer error!\n");
                    break;
                    
                default:
                    break;
            }
    });
}






//统计数据
//key: "detu_video_bitrate" value:NSInteger类型，每秒图像的码率
//key: "detu_gop_size"      value:NSInteger类型，每秒B和P帧的总数量
-(void)PluginVideoOnStatisticsUpdated:(NSDictionary*)dic{
    
    //统计码率 和gop
    int palyerBitRate = [[dic objectForKey:@"detu_video_bitrate"] intValue];
    int gopSize = [[dic objectForKey:@"detu_gop_size"] intValue];
    NSLog(@"inputController:bitrate:%d, gopSize:%d\n",palyerBitRate, gopSize);
    if ( ((CACurrentMediaTime() - self.previousTimeSamp) < 1.0)) {
        return;
    }
    self.previousTimeSamp = CACurrentMediaTime();
    [[MainDispatcher shareInstance] sendBitrateAndGOPSize:[NSString stringWithFormat:@"%d",palyerBitRate] GOPSize:[NSString stringWithFormat:@"%d",gopSize] callBack:^(Dispatch_Error_Type type, DispatchCommand command) {
        if (type == Dispatch_Error_None) {
            NSLog(@"发送码率：bitrate:%d gop:%d",palyerBitRate,gopSize);
        }else{
            NSLog(@"发送码率：失败");
        }
    }];
}
//通过设备号获取播放时的设备号
//- (NSString *)getPlayDeviceWithDevice:(NSString *)device {
//    
//    if (!device) {  //为nil
//        return @"11";
//    }
//    
//    if([device isEqualToString:@"8"] || [device isEqualToString:@"6"]) {//twin A / N
//        device = @"2002";
//    } else if ([device isEqualToString:@"5"]){// sphere S
//        device = @"11";
//    }
//    
//    return device;
//}



-(void)shotSuccessAlertShow{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil message:@"拍摄成功" preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"确认" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
    }];
    [alertController addAction:cancelAction];
    [self presentViewController:alertController animated:YES completion:nil];
    
}

-(void)shotFaileAlertShow{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil message:@"拍摄失败" preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"确认" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
    }];
    [alertController addAction:cancelAction];
    [self presentViewController:alertController animated:YES completion:nil];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
