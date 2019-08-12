//
//  DTSpSViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/9.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "DTSpSViewController.h"
#import "DTSpsSettingViewController.h"
#import "DTTabBarViewController.h"
#import "DTSphereSAlbumViewController.h"

@interface DTSpSViewController ()

@end

@implementation DTSpSViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.changeModeBtn.hidden = NO;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
//    [[MainDispatcher shareInstance] previewDidAppear:^(Dispatch_Error_Type, DispatchCommand) {
//        
//    }];
}

-(void)enterAlbum:(id)sender{
    DTSphereSAlbumViewController *album = [[DTSphereSAlbumViewController alloc] init];
    [self.navigationController pushViewController:album animated:YES];
}
-(void)setting:(id)sender{
    DTSpsSettingViewController *setVC = [[DTSpsSettingViewController alloc] init];
    [self.navigationController pushViewController:setVC animated:YES];
}

-(void)changeModel{
    __weak typeof(self) weakSelf = self;
    if ([MainDispatcher shareInstance].cameraInfo.nowRecordMode != WIFI_APP_MODE_PHOTO) {
        [self showAlertIndictorWithMessage:@"转拍照模式中" withDelay:10];
        [[MainDispatcher shareInstance] changeMode:WIFI_APP_MODE_PHOTO callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            __strong typeof(weakSelf) strongSelf = weakSelf;
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(.1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                if (errorType == Dispatch_Error_None) {
                   
                } else {
                    [strongSelf.changeModeBtn setTitle:@"拍照模式" forState:UIControlStateNormal];
                    [MainDispatcher shareInstance].cameraInfo.nowRecordMode = WIFI_APP_MODE_PHOTO;
                    [strongSelf clearPlayer];
                    strongSelf.rtspPath = NVT_HTTP_STREAM;


                    [strongSelf openRTSPStream];
                }
                [strongSelf hideAlertIndictor];
            });
        }];
    }else{
        [self showAlertIndictorWithMessage:@"转录像模式中" withDelay:10];
        [[MainDispatcher shareInstance] changeMode:WIFI_APP_MODE_MOVIE callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            __strong typeof(weakSelf) strongSelf = weakSelf;
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(.1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                if (errorType == Dispatch_Error_None) {
                  
                } else {
                    [self.changeModeBtn setTitle:@"录像模式" forState:UIControlStateNormal];
                    [MainDispatcher shareInstance].cameraInfo.nowRecordMode = WIFI_APP_MODE_MOVIE;
                    [strongSelf clearPlayer];
                    strongSelf.rtspPath = NVT_RTSP_STREAM;
                    [strongSelf openRTSPStream];
                }
                [strongSelf hideAlertIndictor];
            });
        }];

    }
}

-(void)takePhoto:(id)sender{
    __weak typeof(self) weakSelf = self;
    
    if ([MainDispatcher shareInstance].cameraInfo.nowRecordMode != WIFI_APP_MODE_PHOTO) {
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil message:@"请切换到拍照模式" preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"好的" style:UIAlertActionStyleDefault handler:nil];
        [alertController addAction:okAction];
        [self presentViewController:alertController animated:YES completion:nil];
        return;
    }
    [self showAlertIndictorWithMessage:nil withDelay:10];
    
    [[MainDispatcher shareInstance] takePhoto:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [strongSelf hideAlertIndictor];
        });
     
        if (errorType == Dispatch_Error_None) {
            [strongSelf shotSuccessAlertShow];
        }else{
            [strongSelf shotFaileAlertShow];
        }
    }];
    
}

-(void)takeMovie:(id)sender{
    __weak typeof(self) weakSelf = self;
    if ([MainDispatcher shareInstance].cameraInfo.nowRecordMode == WIFI_APP_MODE_PHOTO) {
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil message:@"请切换到录像模式" preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"好的" style:UIAlertActionStyleDefault handler:nil];
        [alertController addAction:okAction];
        [self presentViewController:alertController animated:YES completion:nil];
        return;
    }

    self.recordMovie = !self.recordMovie;
    UIButton *btn = (UIButton *)sender;
    [self showAlertIndictorWithMessage:nil withDelay:10];
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil message:@"录像成功" preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"好的" style:UIAlertActionStyleDefault handler:nil];
    [alertController addAction:okAction];
    
    [[MainDispatcher shareInstance] recordStartOrStop:![MainDispatcher shareInstance].cameraInfo.isTakingMovie callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
       
        dispatch_async(dispatch_get_main_queue(), ^{
            if (errorType == Dispatch_Error_None) {
                [strongSelf hideAlertIndictor];
                [MainDispatcher shareInstance].cameraInfo.isTakingMovie = ![MainDispatcher shareInstance].cameraInfo.isTakingMovie;
                [btn setTitle:@"停止录像" forState:UIControlStateNormal];
                if (![MainDispatcher shareInstance].cameraInfo.isTakingMovie) {
                    [strongSelf presentViewController:alertController animated:YES completion:nil];
                    [btn setTitle:@"开始录像" forState:UIControlStateNormal];
                }
            }else{
                if([MainDispatcher shareInstance].cameraInfo.isTakingMovie){
                    [MainDispatcher shareInstance].cameraInfo.isTakingMovie = NO;
                }
                Dispatch_Log(@"开始录像失败");
                [strongSelf hideAlertIndictor];
                strongSelf.recordMovie = YES;
            }
        });
    }];

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
