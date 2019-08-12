//
//  DTSp800ViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/9.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "DTSp800ViewController.h"
#import "DTSp800SettingViewController.h"
#import "DTSphere800AlbumViewController.h"

@interface DTSp800ViewController ()

@end

@implementation DTSp800ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
-(void)enterAlbum:(id)sender{
    DTSphere800AlbumViewController *album = [[DTSphere800AlbumViewController alloc] init];
    [self.navigationController pushViewController:album animated:YES];
}
-(void)setting:(id)sender{
    DTSp800SettingViewController *setVC = [[DTSp800SettingViewController alloc] init];
    [self.navigationController pushViewController:setVC animated:YES];
}

-(void)takePhoto:(id)sender{
    __weak typeof(self) weakSelf = self;
    
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
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
