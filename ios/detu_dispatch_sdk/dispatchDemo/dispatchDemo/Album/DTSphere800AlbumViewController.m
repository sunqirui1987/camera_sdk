//
//  DTSphere800AlbumViewController.m
//  dispatchdemo
//
//  Created by lsq on 17/1/12.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "DTSphere800AlbumViewController.h"
#import "MainDispatcher.h"
#import "UIImageView+WebCache.h"
#import "PictureAndMovieBrowerViewController.h"

@interface DTSphere800AlbumViewController ()

@end

@implementation DTSphere800AlbumViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    UITableView *tableView = [[UITableView alloc] initWithFrame:
                              CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height) style:(UITableViewStyleGrouped)];
    
    tableView.dataSource = self;
    tableView.delegate = self;
    
    self.tableView = tableView;
    [self.view addSubview:self.tableView];
    
    __weak typeof(self) weakSelf = self;
    [[MainDispatcher shareInstance] showFileList:^(Dispatch_Error_Type errorType, DispatchCommand dispatchCommand) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        if (errorType != Dispatch_Error_None) {
            Dispatch_Log(@"listingArr ->%@",[MainDispatcher shareInstance].cameraInfo.fileList);
            strongSelf.titleArr = [MainDispatcher shareInstance].cameraInfo.fileList;
            dispatch_async(dispatch_get_main_queue(), ^{
                [strongSelf.tableView reloadData];
            });
        }
    }];
}

-(void)dealloc{
    
}

-(void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    //    [[AmbarellaSDK shareInstance] closeSocketConnect];
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
    FileEntiy *items = [[FileEntiy alloc] init];
    items = [self.titleArr objectAtIndex:indexPath.row];
    [cell.imageView sd_setImageWithURL:[NSURL URLWithString:[items getThumbPath]] placeholderImage:[UIImage imageNamed:@"default_nopic"] options:SDWebImageRetryFailed completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, NSURL *imageURL) {
    }];
    cell.textLabel.text = items.Name;
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    FileEntiy *items = [[FileEntiy alloc] init];
    items = [self.titleArr objectAtIndex:indexPath.row];
    
    PictureAndMovieBrowerViewController *picMoiveVC = [[PictureAndMovieBrowerViewController alloc] init];
    picMoiveVC.device = @"1";
    picMoiveVC.playbackPath = items.Fpath;
    picMoiveVC.downloadPath = items.Fpath;
    picMoiveVC.fileName = items.Name;
    
    if ([items.Name rangeOfString:@".JPG"].location != NSNotFound) {
        picMoiveVC.movieOrPic = 0;
    }else{
        picMoiveVC.movieOrPic = 1;
    }
    
    [self.navigationController pushViewController:picMoiveVC animated:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
