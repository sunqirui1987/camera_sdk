//
//  SettingViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/11.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "DTSpsSettingViewController.h"
#import "MainDispatcher.h"
#import "UIViewController+UE.h"

@interface DTSpsSettingViewController ()

@end

@implementation DTSpsSettingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = @"设置";
    
    UITableView *tableView = [[UITableView alloc] initWithFrame:
                              CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height) style:(UITableViewStyleGrouped)];
    
    tableView.dataSource = self;
    tableView.delegate = self;
    
    self.tableView = tableView;
    [self.view addSubview:self.tableView];
    
    
    self.titleArr = @[@"视频分辨率",@"HDR",@"WDR",@"录音",@"循环录影",@"照片分辨率",@"照片质量",@"曝光",@"iso",@"白平衡",@"光学防抖",@"蜂鸣器",@"自动关机",@"光源频率",@"WiFi信息设置",@"SD卡格式化",@"恢复出厂设置"];
    
}

-(void)setting:(int)index{
    [self showAlertIndictorWithMessage:nil withDelay:5];
    __weak typeof(self) weakSElf = self;
    if (index == 0) {
        //@"视频分辨率"
//        MOVIE_SIZE_FRONT_2880x2160P24 = @"2880x2160 24fps";
//        MOVIE_SIZE_FRONT_2560x1440P30 = @"1920x1440 30fps";
//        MOVIE_SIZE_FRONT_2304x1296P30 = @"1728x1296 30fps";
//        MOVIE_SIZE_FRONT_1920x1080P96 = @"1440x1080 96fps";
//        MOVIE_SIZE_FRONT_1920x1080P60 = @"1440x1080 60fps";
//        MOVIE_SIZE_FRONT_1920x1080P30 = @"1440x1080 30fps";
//        MOVIE_SIZE_FRONT_1280x720P120 = @"960x720 120fps";
//        MOVIE_SIZE_FRONT_1280x720P60 = @"960x720 60fps";
//        MOVIE_SIZE_FRONT_1280x720P30 = @"960x720 30fps";
        [[MainDispatcher shareInstance] setRecordSize:MOVIE_SIZE_FRONT_2880x2160P24 callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 1){
        //@"HDR"
        //YES Or NO
        [[MainDispatcher shareInstance] setHDR:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 2){
        //@"WDR"
        //YES Or NO
        [[MainDispatcher shareInstance] setWDR:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 3){
        //@"录音"
        //YES Or NO
        [[MainDispatcher shareInstance] setSoundRecord:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 4){
        //@"循环录影"
//        MOVIE_CYCLICREC_OFF,    关
//        MOVIE_CYCLICREC_3MIN,   3分钟
//        MOVIE_CYCLICREC_5MIN,   5分钟
//        MOVIE_CYCLICREC_10MIN,  10分钟
        [[MainDispatcher shareInstance] setCyclicRec:MOVIE_CYCLICREC_10MIN callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 5){
        //@"照片分辨率"
//        PHOTO_SIZE_12M = @"4032x3024 12M";
//        PHOTO_SIZE_10M = @"3648x2736 10M";
//        PHOTO_SIZE_8M = @"3264x2448 8M";
//        PHOTO_SIZE_5M = @"2592x1944 5M";
//        PHOTO_SIZE_3M = @"2048x1536 3M";
//        PHOTO_SIZE_2MHD = @"1920 x 1080";
//        PHOTO_SIZE_VGA = @"640 x 480";
//        PHOTO_SIZE_1M = @"1280 x 960";
//        PHOTO_SIZE_ID_MAX = @"1280 x 720";
        [[MainDispatcher shareInstance] setCaptureSize:PHOTO_SIZE_12M callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];

    }else if (index == 6){
        //@"照片质量"
//        PQ_LOW,   普通
//        ISO_MID,  很好
//        ISO_HIGH  精细
        [[MainDispatcher shareInstance] setPhotographicQuality:ISO_MID callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 7){
        //@"曝光"
//        EV_P20 = @"2";
//        EV_P16 = @"1⅔";
//        EV_P13 = @"1⅓";
//        EV_P10 = @"1";
//        EV_P06 = @"⅔";
//        EV_P03 = @"⅓";
//        EV_00 = @"0";
//        EV_N03 = @"-⅓";
//        EV_N06 = @"-⅔";
//        EV_N10 = @"-1";
//        EV_N13 = @"-1⅓";
//        EV_N16 = @"-1⅔";
//        EV_N20 = @"-2";
        [[MainDispatcher shareInstance] setEV:EV_N20 callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 8){
        //ISO
//         AUTO://自动
//         ISO_100://100
//         ISO_200://200
//         ISO_400://400
//         ISO_800://800
//         ISO_1600://1600

        [[MainDispatcher shareInstance] setISO:ISO_800 callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }
    else if (index == 9){
        //@"白平衡"
//         AWB://自动
//         WB_SUNNY://日光
//         WB_CLOUDY://阴天
//         WB_TUNGSTEN_LAMP://钨丝灯
//         WB_FLUORESCENT_LAMP://荧光灯
        [[MainDispatcher shareInstance] setWB:WB_TUNGSTEN_LAMP callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 10){
        //光学防抖
        //YES Or NO
        [[MainDispatcher shareInstance] SetAntisShake:YES CallBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 11){
        //蜂鸣器
        //YES Or NO
        [[MainDispatcher shareInstance] setBeep:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 12){
        // 自动关机
//         POWER_ON://关闭
//         POWER_3MIN://3分钟
//         POWER_5MIN://5分钟
//         POWER_10MIN://10分钟

        [[MainDispatcher shareInstance] MediaPowerOff:POWER_3MIN callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 13){
        //@"光源频率"
//         WIFI_APP_FREQUENCY_50HZ://
//         WIFI_APP_FREQUENCY_60HZ://中
        [[MainDispatcher shareInstance] SetSystemFreq:WIFI_APP_FREQUENCY_50HZ CallBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 14){
        //@"WiFi信息设置",@"SD卡格式化",@"回复出厂设置"
        NSString *newSSID = @"SphereS-SSBJGTMD250";// 新WiFi名
        NSString *newPasswodr = @"123456789";      //新WIFI密码
        [[MainDispatcher shareInstance] ModifySSId:newSSID andPwd:newPasswodr callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 15){
        //@"SD卡格式化"
        [[MainDispatcher shareInstance] FormatDisk:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 16){
        //@"回复出厂设置"
        [[MainDispatcher shareInstance] SystemReset:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }
}

-(void)dealloc{
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}




#pragma mark ---- --- UITableViewDataSource
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}

#pragma mark 返回每组行数
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.titleArr.count;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:nil];
    cell.textLabel.text = [self.titleArr objectAtIndex:indexPath.row];
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [self setting:(int)indexPath.row];
}
@end
