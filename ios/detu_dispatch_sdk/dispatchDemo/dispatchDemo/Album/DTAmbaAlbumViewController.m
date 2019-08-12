//
//  DTAmbaAlbumViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/11.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "DTAmbaAlbumViewController.h"
#import "MainDispatcher.h"
#import "PictureAndMovieBrowerViewController.h"
#import "AmbarellaSDK.h"
@interface DTAmbaAlbumViewController ()

@end

@implementation DTAmbaAlbumViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    UITableView *tableView = [[UITableView alloc] initWithFrame:
                              CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height) style:(UITableViewStyleGrouped)];
    
    tableView.dataSource = self;
    tableView.delegate = self;
    
    self.tableView = tableView;
    [self.view addSubview:self.tableView];
    self.titleArr = [[NSMutableArray alloc] init];
    
    __weak typeof(self) weakSelf = self;
    [[MainDispatcher shareInstance] showFileList:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        if (errorType == Dispatch_Error_None) {
            Dispatch_Log(@"listingArr ->%@",[MainDispatcher shareInstance].cameraInfo.fileList);
            strongSelf.titleArr = [MainDispatcher shareInstance].cameraInfo.fileList;
            dispatch_async(dispatch_get_main_queue(), ^{
                [strongSelf.tableView reloadData];
//                [strongSelf getThumb:(int)strongSelf.titleArr.count];
            });
        }
    }];

    
}

// 递归获取缩略图
-(void)getThumb:(int)tag{
    tag -- ;
    if (tag >= 0) {
        AmbarellaFile *fileModel = [[AmbarellaFile alloc] init];
        fileModel = [self.titleArr objectAtIndex:tag];
        
        __weak typeof(self) weakSekf = self;
        [[MainDispatcher shareInstance] getThumb:fileModel.filePath callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            __strong typeof(weakSekf) strongSelf = weakSekf;
            if (errorType == Dispatch_Error_None) {
                fileModel.thumbData = [MainDispatcher shareInstance].cameraInfo.thumbData;
                [strongSelf.titleArr replaceObjectAtIndex:tag withObject:fileModel];
                [strongSelf.tableView reloadData];
                [strongSelf getThumb:tag];
            }else{
                [weakSekf.tableView reloadData];
            }
        }];
        
    }
}


-(void)dealloc {
    
    Dispatch_Log( @"album dealloc ...");
    if (self.whereFrom == 0) {
        [[MainDispatcher shareInstance]stopSessionOrStopSocket:YES callBack:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
            
            
        }];
    }
}

-(void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
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
    AmbarellaFile *fileInfo = [[AmbarellaFile alloc] init];
    fileInfo = [self.titleArr objectAtIndex:indexPath.row];
    cell.imageView.image = [UIImage imageWithData:fileInfo.thumbData];
    cell.textLabel.text = fileInfo.fileName;
    return cell;
}


-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    AmbarellaFile *fileInfo = [[AmbarellaFile alloc] init];
    fileInfo = [self.titleArr objectAtIndex:indexPath.row];
    PictureAndMovieBrowerViewController *picMoiveVC = [[PictureAndMovieBrowerViewController alloc] init];
    picMoiveVC.device = @"2002";
    
    int fileLength = (int)fileInfo.filePath.length ;
    NSString *str =  [fileInfo.filePath substringWithRange:NSMakeRange(4,fileLength - 4)] ;
    
    if ([fileInfo.fileName rangeOfString:@".MP4"].location != NSNotFound) {
        
        picMoiveVC.movieOrPic = 1;
        picMoiveVC.playbackPath = [NSString stringWithFormat:MOVIEPLAYBACKSTREAM,fileInfo.filePath];
        picMoiveVC.downloadPath = [NSString stringWithFormat:AMBARELLA_DOWNLOAD_PATH,str];
        picMoiveVC.fileName = fileInfo.fileName;
    }else{
        picMoiveVC.movieOrPic = 0;
        picMoiveVC.playbackPath = [NSString stringWithFormat:PICTUREPLAYBACKSTREAM,str];
        picMoiveVC.downloadPath = [NSString stringWithFormat:AMBARELLA_DOWNLOAD_PATH,str];
        picMoiveVC.fileName = fileInfo.fileName;
    }
    
    [self.navigationController pushViewController:picMoiveVC animated:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
