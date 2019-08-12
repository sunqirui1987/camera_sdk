//
//  DTAmbaSettingViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/11.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "DTAmbaSettingViewController.h"
#import "MainDispatcher.h"
#import "UIViewController+UE.h"

@interface DTAmbaSettingViewController ()

@end

@implementation DTAmbaSettingViewController

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
    
    
    self.titleArr = @[@"视频分辨率",@"视频质量",@"照片分辨率",@"照片质量",@"录音",@"蜂鸣器",@"循环录像",@"光源频率",@"WIFI制式",@"WIFI信息设置",@"SD卡格式化",@"恢复出厂设置",@"待机休眠"];
    
    [[MainDispatcher shareInstance] stopVF:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {    }];
}
-(void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    [[MainDispatcher shareInstance] startVF:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {    }];
}
-(void)setting:(int)index{
    [self showAlertIndictorWithMessage:nil withDelay:5];
    __weak typeof(self) weakSElf = self;
    if (index == 0) {
        //@"视频分辨率"
        //  0  =  3040x1520 30P  ;
        //  1  =  2048x1024 30P ;
        [[MainDispatcher shareInstance] setRecordSize:1 callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 1){
        //@"视频质量"
        //        2,   普通
        //        1,  很好
        //        0  精细
        [[MainDispatcher shareInstance] setVideoQuality:2 callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 2){
        //@"照片分辨率"
        //3040x1520   =  0;
        //2048x1024   =  1;
        [[MainDispatcher shareInstance] setCaptureSize:1 callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 3){
        //照片质量
        //        2,   普通
        //        1,   很好
        //        0    精细
        [[MainDispatcher shareInstance] setPhotographicQuality:2 callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 4){
        //录音
        //YES Or NO
        [[MainDispatcher shareInstance] mediaMIC:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 5){
        //蜂鸣器
        //YES Or NO
        [[MainDispatcher shareInstance] setBeep:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 6){
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
    }else if (index == 7){
        //@"光源频率"
        //         WIFI_APP_FREQUENCY_50HZ://
        //         WIFI_APP_FREQUENCY_60HZ://中
        [[MainDispatcher shareInstance] SetSystemFreq:WIFI_APP_FREQUENCY_50HZ CallBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 8){
        //WIFI制式成功之后需重启机器
        //2.4G = 0
        //5.8G = 1
        [[MainDispatcher shareInstance] setWiFiChannel:0 callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 9){
        //@"WiFi信息设置"
        NSString *newSSID = @"T2-T8BV11111";// 新WiFi名
        NSString *newPasswodr = @"123456789";      //新WIFI密码
        [[MainDispatcher shareInstance] ModifySSId:newSSID andPwd:newPasswodr callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 10){
        //@"SD卡格式化"
        [[MainDispatcher shareInstance] FormatDisk:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
            });
            
        }];
    }else if (index == 11){
        //@"回复出厂设置"
        [[MainDispatcher shareInstance] SystemReset:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                __strong typeof(weakSElf) stongSelf = weakSElf;
                [stongSelf hideAlertIndictor];
                [[MainDispatcher shareInstance] shouldDone];
                [stongSelf.navigationController popToRootViewControllerAnimated:YES];
            });
            
        }];
    }else if (index == 12){
        
        [[MainDispatcher shareInstance] setPowerSave:@"5mins" callBack:^(Dispatch_Error_Type type, DispatchCommand command) {
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
