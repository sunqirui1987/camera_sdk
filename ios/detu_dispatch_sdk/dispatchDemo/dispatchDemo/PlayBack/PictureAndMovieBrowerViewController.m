//
//  PictureAndMovieBrowerViewController.m
//  AmbarellaSDK_Demo
//
//  Created by lsq on 16/12/6.
//  Copyright © 2016年 detu. All rights reserved.
//

#import "PictureAndMovieBrowerViewController.h"
#import "PanoPlayerUrl.h"
#import "PanoPlayer.h"
#import "GLSurfaceWidget.h"
#import "VideoPlugin.h"
#import "UIViewController+UE.h"
#import "AmbarellaCommand.h"
#import "DTStitch.h"
#import "MainDispatcher.h"

#define downloadBasePath ({\
NSString *sandboxPath=NSHomeDirectory();\
NSString *basePath=[sandboxPath stringByAppendingString:@"/Documents"];\
[[NSFileManager defaultManager] createDirectoryAtPath:[basePath stringByAppendingString:@"/transeFile"] withIntermediateDirectories:YES attributes:nil error:nil];\
basePath;\
})
#define kDownloadPath [downloadBasePath stringByAppendingString:@"/transeFile"]


@interface PictureAndMovieBrowerViewController ()<IPanoPlayerDelegate, IPanoPlayerPluginDelegate,NSURLSessionDownloadDelegate>

@property (nonatomic,strong)PanoPlayer *player;
@property(nonatomic, strong)GLSurfaceWidget* glWidget;
@property(nonatomic, strong)PluginMetaData* metaData;


@property (nonatomic,strong)UIView *preview;
@property (nonatomic,strong)NSMutableData* movieData;
@property (nonatomic,strong)NSDateFormatter *dateFormatter;
@property (nonatomic,assign)int playMovStatus;


@end

@implementation PictureAndMovieBrowerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    
    [self.slider setValue:0 animated:YES];

    self.dateFormatter = [[NSDateFormatter alloc] init];
    self.dateFormatter.dateFormat = @"HH:mm:ss";
    self.dateFormatter.timeZone = [NSTimeZone timeZoneForSecondsFromGMT:0];

    [self initUI];
    
    
    [self initNav];

}

-(void)initUI{
    self.preview = [[UIView alloc] init];
    self.preview.frame = CGRectMake(0, 49, self.view.frame.size.width, 400);;
    [self.view addSubview:self.preview];
    self.preview.backgroundColor = [UIColor blackColor];

}
-(void)initNav{
    self.view.backgroundColor = [UIColor whiteColor];
    //下载
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.frame = CGRectMake(0, 0,60,22);
    [button setTitle:@"下载" forState:UIControlStateNormal];
    [button setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [button addTarget:self action:@selector(download) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *backItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = backItem;

}
//改变视频播放速度
-(void)changeMovieSlider{
    if(_metaData == nil) {
        return;
    }
    if (self.movieOrPic == 1) {
        int currentTime = [self.slider value] * _metaData.duration;
        
        VideoPlugin* videoPlugin = (VideoPlugin*)[self.player getPlugin];
        [videoPlugin seekTo:self.slider.value];
        
        NSString *played = [self.dateFormatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:currentTime]];
        NSString *total = [self.dateFormatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:_metaData.duration]];
        self.lab_playTime.text = [self setTime:played];
        self.lab_totalTime.text = [self setTime:total];
     
    }
}

//下载视频图片
-(void)download{
    if (self.movieOrPic == 0) {
        [self downloadPic];
    }else{
        [self downloadMovie];
    }
}

-(void)downloadPic{
    //http://192.168.42.1:8989/SD0/DCIM/161202000//19475700.JPG
    NSURLSession *session = [NSURLSession sharedSession];
    NSURL *url = [NSURL URLWithString:self.downloadPath] ;
    NSURLSessionDownloadTask *task = [session downloadTaskWithURL:url completionHandler:^(NSURL *location, NSURLResponse *response, NSError *error) {
       
        
        
        NSString *path = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingPathComponent:response.suggestedFilename];
        [[NSFileManager defaultManager] moveItemAtURL:location toURL:[NSURL fileURLWithPath:path] error:nil];
        
         Dispatch_Log(@"下载成功:%@",location);
        
        //拼接。
        UInt64 recordTime = [[NSDate date] timeIntervalSince1970]*1000;
         NSString * pathToSave = [NSString stringWithFormat:@"%@/save--%lld.jpg",kDownloadPath, recordTime];
        DTStitchModel *model = [[DTStitchModel alloc] init];
        model.device = @"6";
        model.stitchPath =path;
        model.savePath = pathToSave;
        model.sensor = [MainDispatcher shareInstance].cameraInfo.twinData;
     
        CGSize size = CGSizeMake(3000, 1500);
        [[DTStitch sharedInstance] imageStitchWithItem:model ViewSize:size error:^(NSString *error)
         {
             NSLog(@"error == %@",error);
         } progress:^(float progress) {
             NSLog(@"progress -- %f",progress);
         } complete:^(BOOL success) {
             NSLog(@"success --- %d",success);
         }];
        
        
        
        // 提示下载完成
        dispatch_async(dispatch_get_main_queue(), ^{
            [[[UIAlertView alloc] initWithTitle:nil message:@"下载完成" delegate:self cancelButtonTitle:@"知道了" otherButtonTitles: nil] show];
        });        
    }];
    // 启动任务
    [task resume];
    
    
    
}

-(void)downloadMovie{
    //http://192.168.42.1:8989/SD0/DCIM/161202000//194722AA.MP4
    NSURLSessionConfiguration *cfg = [NSURLSessionConfiguration defaultSessionConfiguration];
    NSURLSession *session = [NSURLSession sessionWithConfiguration:cfg delegate:self delegateQueue:[NSOperationQueue mainQueue]];
    
    NSURL* url = [NSURL URLWithString:self.downloadPath];
    
    // 创建任务
    NSURLSessionDownloadTask * downloadTask = [session downloadTaskWithURL:url];
    
    // 开始任务
    [downloadTask resume];
    
    
    
    
}
-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [self openRTSPStream];
}

-(void)viewDidDisappear:(BOOL)animated{
    
}

-(void)clearPlayer{

    [_glWidget onStop];
    [_glWidget removeFromSuperview];
    _glWidget = nil;

    self.player = nil;
    
}
-(void)openRTSPStream{
    NSString *videoOrPic;
    if (self.movieOrPic == 0) {
        videoOrPic = @"sphere";
    }else{
        videoOrPic = @"video";    }
    
    NSString *xml = @"<?xml version='1.0' encoding='UTF-8' ?><DetuVr><settings init='pano1' initmode='default' enablevr='false' title=''></settings><scenes><scene name='pano1' title='' thumburl=''><preview url='' /><image type = '%type' url ='%url' device='%device' biaoding='%biaoding' /><view  hlookat='270' vlookat='90'  fov='115' vrfov='105' vrz='0.5' righteye='0.1' gyroEnable='false' viewmode='fisheye' /></scene></scenes></DetuVr>";
        xml = [xml stringByReplacingOccurrencesOfString:@"%type" withString:videoOrPic];
        xml = [xml stringByReplacingOccurrencesOfString:@"%device" withString: self.device];
        xml = [xml stringByReplacingOccurrencesOfString:@"%url" withString:self.playbackPath];
        if([MainDispatcher shareInstance].cameraInfo.twinData ) { //如果存在标定就传进去
            xml = [xml stringByReplacingOccurrencesOfString:@"%biaoding" withString: [MainDispatcher shareInstance].cameraInfo.twinData];
        }
    Dispatch_Log(@"xml   %@",xml);
    [self showAlertIndictorWithMessage:nil withDelay:20];
    PanoPlayerUrl * panoplayerurl = [[PanoPlayerUrl alloc] init];
    [panoplayerurl setXmlContent:xml];
    
    
    self.player = [[PanoPlayer alloc] init];

    /**播放器初始化**/
    self.player = [[PanoPlayer alloc]init];
    self.player.panoPlayerdelegate = self; //播放器参数和Opengl状态回调通知,回调线程在子线程
    self.player.panoPlayerPluginDelegate = self; //资源加载状态回调通知,回调线程在子线程
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

#pragma action
-(IBAction)fishEye:(id)sende{
    self.player.viewMode = PanoViewMode_FISHEYE;
}
-(IBAction)panorama:(id)sender{
    self.player.viewMode = PanoViewMode_DEFAULT;
}
-(IBAction)littleplanet:(id)sender{
    self.player.viewMode =  PanoViewMode_LITTLE_PLANET;
}
-(IBAction)vr:(id)sender{
    self.player.viewMode =  PanoViewMode_VR_HORIZONTAL;
}

-(void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
}

-(void)dealloc{
    [self clearPlayer];
}

#pragma mark panopalyerDelegate
-(void)onPanoPlayerStatusChanged:(PanoPlayerStatus) status tip:(NSString*) msg {
    
    switch (status) {
        case PanoPlayerStatus_LOADING:
            Dispatch_Log(@"加载中");
            break;
        case PanoPlayerStatus_LOADED:
            Dispatch_Log(@"加载完成");
            
            break;
        case PanoPlayerStatus_ERROR:
            NSLog(@"this is the panpplayer error!\n");
            break;
            
        default:
            break;
    }
}



/**IPanoPlayerPluginDelegate， 线程环境不是主线程**/
-(void)onPanoPlayerPluginStatusChanged:(PanoPluginStatus) status tip:(NSString*) msg {
    switch (status) {
        case PanoPluginStatus_PREPARED:{
            //prepare状态，资源（不区分图片和视频）开始加载，此时可以获取到资源的基本信息
            Plugin* plugin = [self.player getPlugin];
            NSArray<PluginMetaData*>* metaDatas = [plugin getMetaDatas];
            //目前即使多路流metaData都是一样的，基本metaDatas数组现在只有一个数据
            _metaData = metaDatas[0];
        }
            break;
        case PanoPluginStatus_FINISH:{
            //finish,播放正常结束
            Dispatch_Log(@"播放结束");
            
            [self.slider setValue:1 animated:YES];
            NSString *total = [self.dateFormatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:_metaData.duration]];
            //            self.lab_time.text = [NSString stringWithFormat:@"%@ / %@",total,total];
            self.lab_playTime.text =  [self setTime:total];
            self.lab_totalTime.text = [self setTime:total];
            Dispatch_Log(@"total11111=%@",total);
            
        }
            break;
        case PanoPluginStatus_ERROR:{
            //error,资源出现错误
        }
            break;
            
        default:
            break;
    }
}

- (NSString *)setTime:(NSString *)time {
    NSString *showTime;
    NSArray *array = [time componentsSeparatedByString:@":"];
    NSString *str1 = [NSString stringWithFormat:@"%d", [array[0] intValue] *60 + [array[1] intValue]];
    showTime = [str1 stringByAppendingString:[NSString stringWithFormat:@":%@", array[2]]];
    return showTime;
}

-(void)onPanoPlayerPluginProgressChanged:(long) playTime bufferTime:(long) bufferTime duration:(long) duration {
    dispatch_async(dispatch_get_main_queue(), ^(){
        //NSLog(@"222");
        
        if (!self.slider.tracking && self.movieOrPic == 1) {
            [self.slider setValue:playTime/duration animated:YES];
            NSString *played = [self.dateFormatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:self.slider.value * _metaData.duration]];
            NSString *total = [self.dateFormatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:_metaData.duration]];
            //        self.lab_time.text = [NSString stringWithFormat:@"%@ / %@",played,total];
            self.lab_playTime.text = [self setTime:played];
            self.lab_totalTime.text = [self setTime:total];    }
    });
}
/******end********/







#pragma mark -- NSURLSessionDownloadDelegate
/**
 *  下载完毕会调用
 *
 *  @param location     文件临时地址
 */
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
didFinishDownloadingToURL:(NSURL *)location
{
    NSString *document = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    NSString *file = [document stringByAppendingPathComponent:downloadTask.response.suggestedFilename];
    
    NSFileManager *mgr = [NSFileManager defaultManager];
    
    // AtPath : 剪切前的文件路径
    // ToPath : 剪切后的文件路径
    [mgr moveItemAtPath:location.path toPath:file error:nil];
    
    // 提示下载完成
    [[[UIAlertView alloc] initWithTitle:@"下载完成" message:downloadTask.response.suggestedFilename delegate:self cancelButtonTitle:@"知道了" otherButtonTitles: nil] show];
}

/**
 *  每次写入沙盒完毕调用
 *  在这里面监听下载进度，totalBytesWritten/totalBytesExpectedToWrite
 *
 *  @param bytesWritten              这次写入的大小
 *  @param totalBytesWritten         已经写入沙盒的大小
 *  @param totalBytesExpectedToWrite 文件总大小
 */
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
      didWriteData:(int64_t)bytesWritten
 totalBytesWritten:(int64_t)totalBytesWritten
totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite
{
    Dispatch_Log(@"download Progress:%f",(double)totalBytesWritten/totalBytesExpectedToWrite);
}

- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
 didResumeAtOffset:(int64_t)fileOffset
expectedTotalBytes:(int64_t)expectedTotalBytes
{
    
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
