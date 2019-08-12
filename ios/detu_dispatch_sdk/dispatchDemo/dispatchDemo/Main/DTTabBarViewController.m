//
//  DTTabBarViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/7.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "DTTabBarViewController.h"
#import "DTDeviceManager.h"
#import "DTSp800ViewController.h"
#import "DTAmbaPreViewController.h"
#import "DTDokicamViewController.h"
#import "DTSpSViewController.h"
#import "DTAmbaAlbumViewController.h"
#import "AmbarellaSDK.h"
#import "DTStitch.h"
#import "MediaMetaManager.h"

@interface DTTabBarViewController ()<UITabBarControllerDelegate>

@property (nonatomic, strong) DTStitch *stitch;

@property (nonatomic, strong) UINavigationController * stroreNav ;
@property (nonatomic, strong) AmbarellaSDK * sdk ;

@property (nonatomic, strong) UILabel * percentLab ;


@end

@implementation DTTabBarViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    _stitch = [DTStitch new];
    
    //加号按钮
    UIViewController* takePhotosViewController = [[UIViewController alloc] init];
    takePhotosViewController.tabBarItem.imageInsets = UIEdgeInsetsMake(5, 0, -5, 0);
    takePhotosViewController.tabBarItem.image = [[UIImage imageNamed:@"add"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    self.viewControllers = @[takePhotosViewController];
    self.delegate = self;

    [MainDispatcher shareInstance].notifyBlock = ^(NSString * currentDevice, NSString * previousDevice) {
        
        Dispatch_Log(@"%p 相机WIFI已经改变", __func__);
        if ([DTDeviceManager sharedInstance].curConnDevice == DispatchMachine_None) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self showAlertIndictorWithMessage:@"相机断开连接" withDelay:1.5];
            });
        }
    };
    

    UIButton * tranformButton = [UIButton buttonWithType:UIButtonTypeCustom];
    tranformButton.backgroundColor = [UIColor yellowColor];
    [tranformButton setTitle:@"转码" forState:UIControlStateNormal];
    [tranformButton setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
    tranformButton.frame = CGRectMake(20, 100, 70, 30);
    [self.view addSubview:tranformButton];
    [tranformButton addTarget:self action:@selector(tranform) forControlEvents:UIControlEventTouchUpInside];
    
    
    UIButton * livestreamButton = [UIButton buttonWithType:UIButtonTypeCustom];
    livestreamButton.backgroundColor = [UIColor yellowColor];
    [livestreamButton setTitle:@"推流" forState:UIControlStateNormal];
    [livestreamButton setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
    livestreamButton.frame = CGRectMake( CGRectGetMaxX(tranformButton.frame)+15, CGRectGetMinY(tranformButton.frame), 70, 30);
    [self.view addSubview:livestreamButton];
    [livestreamButton addTarget:self action:@selector(livestream) forControlEvents:UIControlEventTouchUpInside];
    
    UIButton * albumButton = [UIButton buttonWithType:UIButtonTypeCustom];
    albumButton.backgroundColor = [UIColor yellowColor];
    [albumButton setTitle:@"相册" forState:UIControlStateNormal];
    [albumButton setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
    albumButton.frame = CGRectMake(CGRectGetMaxX(livestreamButton.frame)+15, CGRectGetMinY(livestreamButton.frame), 70, 30);
    [self.view addSubview:albumButton];
    [albumButton addTarget:self action:@selector(pushAlbum) forControlEvents:UIControlEventTouchUpInside];
    
    
    UIButton * biaodingButton = [UIButton buttonWithType:UIButtonTypeCustom];
    biaodingButton.backgroundColor = [UIColor yellowColor];
    [biaodingButton setTitle:@"取标定" forState:UIControlStateNormal];
    [biaodingButton setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
    biaodingButton.frame = CGRectMake(CGRectGetMaxX(albumButton.frame)+15, CGRectGetMinY(albumButton.frame), 70, 30);
    [self.view addSubview:biaodingButton];
    [biaodingButton addTarget:self action:@selector(getBiaoding) forControlEvents:UIControlEventTouchUpInside];
    

    UILabel * percent = [[UILabel alloc]init];
    self.percentLab = percent;
    percent.textAlignment = NSTextAlignmentCenter;
    percent.backgroundColor = [UIColor yellowColor];
    percent.frame = CGRectMake(0, 0, 80, 80);
    percent.center = self.view.center;
    percent.clipsToBounds = YES;
    percent.layer.cornerRadius = 40;
    [self.view addSubview:percent];
    percent.text = @"0%";
}

- (void)getBiaoding {
    
    NSString *filePath = [[NSBundle mainBundle]pathForResource:@"145533AB" ofType:@"MP4"];
    // 读取文件标定
    MediaMetaManager *manager = [[MediaMetaManager alloc] init];
    NSString *strUrl = [filePath stringByReplacingOccurrencesOfString:@"file://" withString:@""];
    DTCameraMediaInfo *Info = [manager getCameraMediaInfo:strUrl];
    [self showAlertIndictorWithMessage:Info.calibration withDelay:2];
}

- (void)tranform
{
    WeakSelf
    DTStitchModel * model = [self getVideoSticModel];
    // 2k: 2048 1024
    // 3k: 3040 1520
    [[DTStitch sharedInstance] videoStitchWithItem:model ViewSize:(CGSize){3040, 1520} error:^(NSString *error) {
        
    } progress:^(float progress) {
        StrongSelf
        dispatch_async(dispatch_get_main_queue(), ^{
            NSString * s = @"%";
            _strongSelf.percentLab.text = [NSString stringWithFormat:@"%d%@", (int)(progress*100),s];
        });
        NSLog(@"stitch progress is  %f\n", progress);
    } complete:^(BOOL success) {
        StrongSelf
        dispatch_async(dispatch_get_main_queue(), ^{
            if (success)
                _strongSelf.percentLab.text = @"success";
            else
                _strongSelf.percentLab.text = @"failure";
        });
    }];
}

- (DTStitchModel * )getVideoSticModel {
    
    NSArray *documents =  NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString * outpath = documents.firstObject;
    outpath = [outpath stringByAppendingPathComponent:@"145533AB.MP4"];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:outpath]) {
        [[NSFileManager defaultManager] removeItemAtPath:outpath error:nil];
    }
    
    DTStitchModel * model = [DTStitchModel new];
    model.device = [[DTDeviceManager sharedInstance] getMachineName];
    model.stitchPath = [[NSBundle mainBundle]pathForResource:@"145533AB" ofType:@"MP4"];
    model.savePath = outpath;
    model.createTime = @"2017.08.07";
    // 用库获取，或者从相机读 做多重保护。
    model.sensor = [MainDispatcher shareInstance].cameraInfo.twinData?[MainDispatcher shareInstance].cameraInfo.twinData:@"6_746.5_762.5_771.5_-180_0_0_739_2259_763_-1.28787_-1.47992_-0.76834_3040_1520_7.00431_5.49882_0_0_0_0_-0.12765_0_0_-0.133908_198_187";
    
    
    return model;
}

- (void)livestream
{
    [self showAlertIndictorWithMessage:@"" withDelay:10];
    [[MainDispatcher shareInstance] connectMachineAndGetSensorCallBack:^(Dispatch_Error_Type errorType, DispatchCommand command) {
        [[MainDispatcher shareInstance] setPushStreamWithSSID:@"WIFI名" PWD:@"WIFI密码" PSAdress:@"推流地址" Res:^( Dispatch_Error_Type Dispatch_Error_Type, DispatchCommand DispatchCommand) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self hideAlertIndictor];
                if (Dispatch_Error_Type == Dispatch_Error_None) {
                    // 成功后相机会重启进入推流模式，不要惊慌
                }
                else
                    [self showAlertIndictorWithMessage:[DispatchErrorHandle descriptionByError:errorType] withDelay:2];
            });
        }];
    }];
}

- (void)pushAlbum
{
    [self showAlertIndictorWithMessage:@"" withDelay:10];
    [[MainDispatcher shareInstance]connectMachineAndGetSensorCallBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self hideAlertIndictor];
            if (errorType == Dispatch_Error_None) {
                DTAmbaAlbumViewController *albumVC = [[DTAmbaAlbumViewController alloc] init];
                albumVC.whereFrom = 0;
                [self.navigationController pushViewController:albumVC animated:YES];
            }
        });
    }];
}

//连接相机的按钮
- (void)clickConnectButton
{
    if ([DTDeviceManager sharedInstance].curConnDevice == DispatchMachine_None)
        return;
    
    WeakSelf
    [self showAlertIndictorWithMessage:@"" withDelay:20];
    [[MainDispatcher shareInstance] connectMachineAndGetSensorCallBack:^(Dispatch_Error_Type errorType, DispatchCommand command) {
        if (errorType == Dispatch_Error_None)
        {
            [[MainDispatcher shareInstance] pushInpreview:^(Dispatch_Error_Type errorType, DispatchCommand command) {
                StrongSelf
                Dispatch_Log(@"pushInpreview error is %@", [DispatchErrorHandle descriptionByError:errorType]);
                if (errorType == Dispatch_Error_None) {
                    [[MainDispatcher shareInstance] getMachineVersion:^(Dispatch_Error_Type errorType, DispatchCommand command) {
                        dispatch_async(dispatch_get_main_queue(), ^{
                            [_strongSelf hideAlertIndictor];
                            [_strongSelf pushInTakePhotoViewController];
                        });
                    }];
                }
            }];
        }else if (errorType == Dispatch_Error_USB_INSERTED){
            dispatch_async(dispatch_get_main_queue(), ^{
                [[MainDispatcher shareInstance] stopSessionOrStopSocket:YES callBack:^(Dispatch_Error_Type e, DispatchCommand c) {
                    
                }];
                [self hideAlertIndictor];
                [self showAlertIndictorWithMessage:@"USB已经插入" withDelay:2];
                
            });
        }else if(errorType == Dispatch_Error_SESSION_START_FAIL) {
        
            dispatch_async(dispatch_get_main_queue(), ^{
                [self showAlertIndictorWithMessage:@"相机被他人连接" withDelay:2];
            });
            [[MainDispatcher shareInstance] shouldDone];
        }
    }];
    
//
}


- (BOOL)tabBarController:(UITabBarController *)tabBarController shouldSelectViewController:(UIViewController *)viewController{
    NSUInteger index = [[tabBarController viewControllers] indexOfObject:viewController];
    switch (index) {
        case 0:
        {
            [self clickConnectButton];
            return NO;
        }
        default:{
            return YES;
        }
    }
}


- (void)pushInTakePhotoViewController {
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(.1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        switch ([DTDeviceManager sharedInstance].curConnDevice) {
                
            case DispatchMachine_Sphere800:
            {
                DTSp800ViewController* controller = [[DTSp800ViewController alloc] init];
                controller.title = @"Player";
//                UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:controller];;
//                self.stroreNav = nav;
//                [self presentViewController:nav animated:YES completion:nil];
                controller.rtspPath = NVT_RTSP_STREAM;
                controller.device = @"1";
                controller.deviceType = 1;
                [self.navigationController pushViewController:controller animated:YES];
                break;
            }
            case DispatchMachine_SphereS:
            {
                DTSpSViewController* controller = [[DTSpSViewController alloc] init];
                controller.title = @"Player";
//                UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:controller];;
//                self.stroreNav = nav;
//                [self presentViewController:nav animated:YES completion:nil];
                controller.device = @"11";
                controller.deviceType = 2;
                if ([MainDispatcher shareInstance].cameraInfo.nowRecordMode == WIFI_APP_MODE_PHOTO) {
                    controller.rtspPath = NVT_HTTP_STREAM;
                }else{
                    controller.rtspPath = NVT_RTSP_STREAM;
                }
                
                [self.navigationController pushViewController:controller animated:YES];
                break;
            }
            case DispatchMachine_Dokicam:
            {
                DTDokicamViewController* controller = [[DTDokicamViewController alloc] init];
                controller.title = @"Player";
//                UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:controller];;
//                self.stroreNav = nav;
//                [self presentViewController:nav animated:YES completion:nil];
                controller.rtspPath = NVT_RTSP_STREAM;
                controller.device = @"2002";
                [self.navigationController pushViewController:controller animated:YES];
                break;
            }
            case DispatchMachine_TwinA:
            {
                DTAmbaPreViewController* controller = [[DTAmbaPreViewController alloc] init];
                controller.title = @"Player";
//                UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:controller];;
//                self.stroreNav = nav;
//                [self presentViewController:nav animated:YES completion:nil];
                controller.rtspPath = AMBARELLA_RTSP_STREAM;
                controller.device = @"2002";
                controller.deviceType = 3;
                [self.navigationController pushViewController:controller animated:YES];
                break;
            }
            default:
                break;
        }
    });
    
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
