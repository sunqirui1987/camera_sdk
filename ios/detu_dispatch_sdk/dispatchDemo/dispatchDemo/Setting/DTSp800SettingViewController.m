//
//  DTSp800SettingViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/11.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "DTSp800SettingViewController.h"
#import "MainDispatcher.h"
#import "UIViewController+UE.h"

@interface DTSp800SettingViewController ()

@end

@implementation DTSp800SettingViewController

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
    
    
    self.titleArr = @[@"视频分辨率",@"开机默认模式",@"HDR",@"录音",@"循环录影",@"照片分辨率",@"照片质量",@"曝光",@"iso",@"白平衡",@"蜂鸣器",@"自动关机",@"WiFi信息设置",@"SD卡格式化",@"恢复出厂设置"];
    
}

-(void)setting:(int)index{
    [self showAlertIndictorWithMessage:nil withDelay:5];
    __weak typeof(self) weakSElf = self;
    if (index == 0) {
        //@"视频分辨率"
//        0 = @"1440x1080 1080p";
//        1 = @"960x720 720p";
//        2 = @"640x480 VGA";
        [[MainDispatcher shareInstance] setRecordSize:0 callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 1){
        //@"开机默认模式"
//        MODE_MOVIE ,视频
//        MODE_PHOTO ,拍照
        [[MainDispatcher shareInstance] setDefaultMode:MODE_PHOTO callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 2){
        //@"HDR"
        //YES Or NO
        [[MainDispatcher shareInstance] setHDR:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
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
        //        PHOTO_SIZE_8M = @"3264x2448 8M";
        //        PHOTO_SIZE_5M = @"2592x1944 5M";
        //        PHOTO_SIZE_3M = @"2048x1536 3M";
        [[MainDispatcher shareInstance] setCaptureSize:PHOTO_SIZE_8M callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];    }else if (index == 6){
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
        //蜂鸣器
        //YES Or NO
        [[MainDispatcher shareInstance] setBeep:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 11){
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
    }else if (index == 12){
        //@"WiFi信息设置"
        NSString *newSSID = @"Sphere-T8BV11111";// 新WiFi名
        NSString *newPasswodr = @"123456789";      //新WIFI密码
        [[MainDispatcher shareInstance] ModifySSId:newSSID andPwd:newPasswodr callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 13){
        //@"SD卡格式化"
        [[MainDispatcher shareInstance] FormatDisk:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 14){
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
