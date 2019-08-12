//
//  DTAmbaPreViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/9.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "DTAmbaPreViewController.h"
#import "MainDispatcher.h"
#import "DTAmbaSettingViewController.h"
#import "DTAmbaAlbumViewController.h"
#import "DTStitch.h"

@interface DTAmbaPreViewController ()

@property (nonatomic, strong) DTStitch *stitch;
@end

@implementation DTAmbaPreViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // init
    _stitch = [DTStitch new];
    
    // Do any additional setup after loading the view from its nib.
    
    UIButton *leftButton = [[UIButton alloc] initWithFrame:CGRectMake(0,0,30,32)];
    [leftButton setImage:[UIImage imageNamed:@"back"]forState:UIControlStateNormal];
    [leftButton addTarget:self action:@selector(back) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *leftItem = [[UIBarButtonItem alloc]initWithCustomView:leftButton];
    self.navigationItem.leftBarButtonItem = leftItem;

    [[MainDispatcher shareInstance] previewDidAppear:^(Dispatch_Error_Type errorType, DispatchCommand command) {
        if (errorType == Dispatch_Error_None) {
            Dispatch_Log(@"获取到配置信息了");
        }
    }];
    
    
    __weak typeof(self) weak = self;
    [MainDispatcher shareInstance].applicationStateNotifyBlock = ^
    {
        __strong typeof(weak) self = weak;
        if ([MainDispatcher shareInstance].dispatchStatus.applicationStatus == ApplicationStatus_becomeActive) {
            if ([MainDispatcher shareInstance].dispatchStatus.dispatchMachineType == DispatchMachine_None) {
                [self back];
                return;
            }
            // 挂点电话回来、应用不会挂起
            if ([MainDispatcher shareInstance].dispatchStatus.cTCallStates == CTCallStates_Disconnected) {}
            else {
                __weak typeof(self) weak = self;
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.01 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                    [self showAlertIndictorWithMessage:@"" withDelay:10];
                });
                [[MainDispatcher shareInstance]startSession:^(Dispatch_Error_Type type , DispatchCommand command) {
                    __strong typeof(weak) self = weak;
                    dispatch_async(dispatch_get_main_queue(), ^{
                        [self hideAlertIndictor];
                        if (type == Dispatch_Error_None) {
                            
                            __weak typeof(self) weak = self;
                            [[MainDispatcher shareInstance] getCurrentMode:^(Dispatch_Error_Type type , DispatchCommand c) {
                                __strong typeof(weak) self = weak;
                            }];
                            
                        }else {
                            [self back];
                        }
                    });
                }];
            }
    
        }else if ([MainDispatcher shareInstance].dispatchStatus.applicationStatus == ApplicationStatus_resignActive)
        {
            // 来电话了、应用取消活跃，不会挂起
            if ([MainDispatcher shareInstance].dispatchStatus.cTCallStates == CTCallStates_Incoming) {}
            else
            {
                __weak typeof(self) weak = self;
                [[MainDispatcher shareInstance]stopSessionOrStopSocket:NO callBack:^(Dispatch_Error_Type type, DispatchCommand command) {
                    __strong typeof(weak) self = weak;
//                    if(self.player){
//                        if([self.ca.cameraPlayer GetCurrentPluginObject]){
//                            [(VideoPlugin*)[self.cameraPlayer.cameraPlayer GetCurrentPluginObject] stop];
//                        }
//                    }
                }];
            }
        }
    };

}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [MainDispatcher shareInstance].cmeraNotifyBlock = ^(NSDictionary *info) {
        NSLog(@"%@log %@",[self class], info);
    };
}

-(void)back{
    WeakSelf
    [[MainDispatcher shareInstance] stopSessionOrStopSocket:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
        StrongSelf
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(.001 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [_strongSelf.navigationController popViewControllerAnimated:YES];
        });
    }];
}

-(void)setting:(id)sender {
//    DTStitchModel * model = [self getVideoSticModel];
//    // 2k: 2048 1024
//    // 3k: 3040 1520
//    [self.stitch videoStitchWithItem:model ViewSize:(CGSize){3040, 1520} error:^(NSString *error) {
//    } progress:^(float progress) {
//        NSLog(@"stitch progress is  %f\n", progress);
//    } complete:^(BOOL success) {
//
//    }];
//    return;
    DTAmbaSettingViewController *setVC = [[DTAmbaSettingViewController alloc] init];
    [self.navigationController pushViewController:setVC animated:YES];
}

- (DTStitchModel * )getVideoSticModel {

    NSString * outpath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
    outpath = [outpath stringByAppendingPathComponent:@"xxx.mp4"];
    DTStitchModel * model = [DTStitchModel new];
    model.device = [[DTDeviceManager sharedInstance] getMachineName];
    model.stitchPath = [[NSBundle mainBundle]pathForResource:@"094348AA" ofType:@"MP4"];
    model.savePath = outpath;
    model.createTime = @"2017.07.26";
    model.sensor = [MainDispatcher shareInstance].cameraInfo.twinData;
    
    return model;
}

-(void)takePhoto:(id)sender{
    __weak typeof(self) weakSelf = self;
    
    [self showAlertIndictorWithMessage:nil withDelay:5];
    

    [[MainDispatcher shareInstance] takePhoto:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        
        dispatch_async(dispatch_get_main_queue(), ^{
            
            [self.player replay];
            
            
            [strongSelf hideAlertIndictor];
            if (errorType == Dispatch_Error_None) {
                [strongSelf showAlertIndictorWithMessage:@"success" withDelay:2];
            }else{
                [strongSelf showAlertIndictorWithMessage:@"failure" withDelay:2];
            }
        });
        
        NSArray *thumbPathArr =  [[MainDispatcher shareInstance].cameraInfo.newestPicThumPath componentsSeparatedByString:@"\\"];
        AmbarellaFile *fileModel = [[AmbarellaFile alloc] init];
        fileModel.fileName = [thumbPathArr lastObject];
        fileModel.filePath = [NSString stringWithFormat:@"/tmp/SD0/DCIM/%@/%@",[thumbPathArr objectAtIndex:2],[thumbPathArr objectAtIndex:3]];
        
        [[MainDispatcher shareInstance]getThumb:fileModel.filePath callBack:^(Dispatch_Error_Type errorType, DispatchCommand command) {
            if ([MainDispatcher shareInstance].cameraInfo.thumbData) {
                //                        UIImage *cutImage = [[DTThumbAndVideoTool sharedInstance] cutSphereImage:[UIImage imageWithData:thumbData]];UIImagePNGRepresentation(thumbData);
                UIImage *cutImage = [UIImage imageWithData:[MainDispatcher shareInstance].cameraInfo.thumbData];
                
                dispatch_async(dispatch_get_main_queue(), ^{
                  
                });
            }
        }];
    }];

}

-(void)takeMovie:(id)sender{
    self.recordMovie = !self.recordMovie;
    UIButton *btn = (UIButton *)sender;
    [self showAlertIndictorWithMessage:nil withDelay:5];
    
    __weak typeof(self) weakSelf = self;
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil message:@"录像成功" preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"好的" style:UIAlertActionStyleDefault handler:nil];
    [alertController addAction:okAction];
    
    if (self.recordMovie) {
        [[MainDispatcher shareInstance] recordStartOrStop:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            __strong typeof(weakSelf) strongSelf = weakSelf;
            
             dispatch_async(dispatch_get_main_queue(), ^{
                if (errorType == Dispatch_Error_None) {
                    [strongSelf hideAlertIndictor];
                    [btn setTitle:@"停止录像" forState:UIControlStateNormal];
                }else{
                    Dispatch_Log(@"开始录像失败");
                    strongSelf.recordMovie = YES;
                }
             });
        }];
    }else{
    
        [[MainDispatcher shareInstance] recordStartOrStop:NO callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            __strong typeof(weakSelf) strongSelf = weakSelf;
            
            dispatch_async(dispatch_get_main_queue(), ^{
                [strongSelf hideAlertIndictor];
       
                if (errorType == Dispatch_Error_None) {
                    [btn setTitle:@"开始录像" forState:UIControlStateNormal];
                    Dispatch_Log(@"录制成功");
                    [strongSelf shotSuccessAlertShow];
                }else{
                    strongSelf.recordMovie = NO;
                }
            });
            
            
        }];
    }
}

-(void)enterAlbum:(id)sender{
    DTAmbaAlbumViewController *albumVC = [[DTAmbaAlbumViewController alloc] init];
    albumVC.whereFrom  = 1;
    [self.navigationController pushViewController:albumVC animated:YES];
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
