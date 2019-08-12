##得图相机SDK使用说明##
#### 介绍
得图相机SDK 集成了相机命令控制器、全景播放器、视频照片拼接、标定获取等
++注意：==只能支持真机调试==++
***
****目录：**
![WechatIMG547.jpeg](../../detu_dispatch_sdk/目录.png)
***
****配置：**
![WechatIMG547.jpeg](../../detu_dispatch_sdk/路径.png)
++按照demo++
++1.设置header Paths、lib paths++
++2. build phases 添加相关lib文件++
***
##### 全景播放器
参考[得图全景相机](http://www.detu.com/develop/page/41)
##### 标定获取
支持从本地资源、直播流读取标定信息以及支持对本地视频以及照片Metadata、Exif信息的设置。
``` 
NSString *filePath = [[NSBundle mainBundle]pathForResource:@"145533AB" ofType:@"MP4"];
    // 读取文件标定
MediaMetaManager *manager = [[MediaMetaManager alloc] init];
NSString *strUrl = [filePath stringByReplacingOccurrencesOfString:@"file://" withString:@""];
DTCameraMediaInfo *Info = [manager getCameraMediaInfo:strUrl];
NSLog(@"%@",Info.calibration);    
```
##### 视频照片拼接
```
+ (instancetype)sharedInstance;

/**
 * 视频转码
 *
 * @param stitchModel   DTStitchModel
 * @param viewSize      转码大小2k(2048, 1024),3k(3040, 1520)
 * @param errorBlock    错误回调
 * @param progressblock 转码进度回调
 * @param completeblock 转码成功失败回调
 */
- (void)videoStitchWithItem:(DTStitchModel *)stitchModel
                   ViewSize:(CGSize)viewSize
                      error:(void (^)(NSString *error))errorBlock
                   progress:(void(^)(float progress))progressblock
                   complete:(void(^)(BOOL success))completeblock ;

/**
 * 图片转码
 *
 * @param stitchModel   DTStitchModel
 * @param viewSize      转码大小2k(2048, 1024),3k(3040, 1520)
 * @param errorBlock    错误回调
 * @param progressblock 转码进度回调
 * @param completeblock 转码成功失败回调
 */
- (void)imageStitchWithItem:(DTStitchModel *)stitchModel
                   ViewSize:(CGSize)viewSize
                      error:(void (^)(NSString *error))errorBlock
                   progress:(void(^)(float progress))progressblock
                   complete:(void(^)(BOOL success))completeblock ;
// 停止转码
- (void)stop ;

```
****注意：==转码分辨率能够自定义设置，但是需要转成二比一，转码完毕自动添加了元数据、Exif信息，能够上传到facebook、Youtube被识别为全景数据==**
##### 相机调度器
功能：WiFi实时检测，得图相机识别，相机命令
####使用
1.==**引入**==
`#import "dispatchlib.h"`
2.==**AppDelegate 的 didFinishLaunchingWithOptions 方法中加入**==
`[[DTDeviceManager sharedInstance] config];`
3.==**监听**==
==WiFi监听==
```

 WeakSelf
    [MainDispatcher shareInstance].notifyBlock = ^(NSString * currentDevice, NSString * previousDevice){
        StrongSelf
        if (![currentDevice isEqualToString: previousDevice]) {
            Dispatch_Log(@"WiFi 发生改变 previous WIFI is %@ current Wifi is %@", [DTDeviceManager sharedInstance].preDeviceName, [DTDeviceManager sharedInstance].curWifiName);
            [_strongSelf back];
        }
    };
```
***
==App 生命周期监听==
```
 __weak typeof(self) weak = self;
    [MainDispatcher shareInstance].applicationStateNotifyBlock = ^
    {
        __strong typeof(weak) self = weak;
        if ([MainDispatcher shareInstance].dispatchStatus.applicationStatus == ApplicationStatus_becomeActive) {
            
            // 挂点电话回来、应用不会挂起
            if ([MainDispatcher shareInstance].dispatchStatus.cTCallStates == CTCallStates_Disconnected) {}
            else {
                __weak typeof(self) weak = self;
               
                // 开启会话
                [[MainDispatcher shareInstance]startSession:^(Dispatch_Error_Type type , DispatchCommand command) {
                    __strong typeof(weak) self = weak;
                    dispatch_async(dispatch_get_main_queue(), ^{
                        if (type == Dispatch_Error_None) {
                           
                           //1. 播放器做刷新处理
                           //   自定义UI处理...
                           //2. 获取录制时间，以及当前模式，更新UI。
                            __weak typeof(self) weak = self;
                            [[MainDispatcher shareInstance] getCurrentMode:^(Dispatch_Error_Type type , DispatchCommand c) {
                                __strong typeof(weak) self = weak;
                                self.cameraModel.cameraCurrentRecordTime = [MainDispatcher shareInstance].cameraInfo.nowMovieRecordingTime;
                                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.01 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                                    [self refreshUI:previewUIControl];
                                });
                            }];
                        }else {
                            dispatch_async(dispatch_get_main_queue(), ^{
                                // 退出
                            });
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
                // 停止会话
                
                // 自定义UI处理...
                __weak typeof(self) weak = self;
                [[MainDispatcher shareInstance]stopSessionOrStopSocket:NO callBack:^(Dispatch_Error_Type type, DispatchCommand command) {
                    __strong typeof(weak) self = weak;
                    if(self.cameraPlayer){
                        if([self.cameraPlayer.cameraPlayer GetCurrentPluginObject]){
                            [(VideoPlugin*)[self.cameraPlayer.cameraPlayer GetCurrentPluginObject] stop];
                        }
                    }
                }];
            }
        }else if ([MainDispatcher shareInstance].dispatchStatus.applicationStatus == ApplicationStatus_willTerminate){
            [[MainDispatcher shareInstance]stopSessionOrStopSocket:YES callBack:^(Dispatch_Error_Type type, DispatchCommand command) {
                NSLog(@"APP崩溃 关闭会话");
            }];
        }
    };
```
***
==相机实时通知==
```
 WeakSelf
    [MainDispatcher shareInstance].cmeraNotifyBlock = ^(NSDictionary *info){
        StrongSelf
        NSString * type = info[@"type"];
        dispatch_async(dispatch_get_main_queue(), ^
                       {
                           if ([type isEqualToString: NETCTRL_STR_NOTICE_POWER_OFF]||[type isEqualToString: NETCTRL_STR_NOTICE_WIFI_OFF]||[type isEqualToString: NETCTRL_STR_NOTICE_RECORD_ERROR]||[type isEqualToString:NETCTRL_STR_NOTICE_USB_MSC_ENTER]||[type isEqualToString: NETCTRL_STR_NOTICE_HDMI_IN]) {
                               // 关机、关WIFI、录影中异常（无法恢复，机器会重启) 需要做退出处理
                           }
                           else if ([type isEqualToString: NETCTRL_STR_NOTICE_DC_IN]||[type isEqualToString: NETCTRL_STR_NOTICE_DC_OUT])
                           {
                               // 相机端备操作开始拍照，app发送停止录像命令
                           }
                           else if ([type isEqualToString: NETCTRL_STR_NOTICE_CAPTURE_START])
                           {
                               // 相机端备操作开始拍照，app发送停止录像命令
                           }else if ([type isEqualToString: NETCTRL_STR_NOTICE_RECORD_START])
                           {
                               // 相机端备操作开始录像，app发送开始录像命令
                           }else if ([type isEqualToString: NETCTRL_STR_NOTICE_RECORD_STOP])
                           {
                               // 相机端备操作停止录像，app发送停止录像命令
                           }else if ([type isEqualToString: NETCTRL_STR_NOTICE_RECORD_STOP_10MIN]||[type isEqualToString: NETCTRL_STR_NOTICE_RECORD_STOP_SD_ERROR]||[type isEqualToString: NETCTRL_STR_NOTICE_RECORD_STOP_IO_ERROR]){
                               // 十分钟停止录影、录影中卡错误、IO错误-->改变UI、不需要发送停止命令
                           }
                           else if ([type isEqualToString: NETCTRL_STR_NOTICE_SD_FULL]){
                               // 卡满、改变UI、不需要发送停止命令
                           }
                       });
    };


```

4.==**相机命令（具体使用见demo）**==

App与相机是用socket通信，因此连接相机之前需要进行会话申请，离开相机的时候需要断开会话。

==连接相机==
```
/**
 * number  1.
 * do      连接机器并且获取标定
 * return: 设置结果 命令号
 */
- (void)connectMachineAndGetSensorCallBack:(resultResponseBlock)responseBlock;
```
==断开相机==
```
/**
 * number  34.
 * do      停止会话、断开socket
 * return: 设置结果 命令号
 */
- (void)stopSessionOrStopSocket:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

```

==拍照、录像==
拍照、录像之前需要暂停拉流，回调以后需要刷新播放器。
```
/**
 * number  10.
 * do      拍摄照片
 * return: 设置结果 命令号
 */
- (void)takePhoto:(resultResponseBlock)responseBlock ;

/**
 * number  11.
 * do      录制视频
 * params: start or shut
 * return: 设置结果 命令号
 */
- (void)recordStartOrStop:(BOOL)abool callBack:(resultResponseBlock)responseBlock ;

```
==设置==
只有**恢复出厂设置**、**修改WiFi设置**会导致相机重启（需要退出相机连接界面）、其他设置类的命令不会重启相机（可以保持在当前界面）。