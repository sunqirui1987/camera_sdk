//
//  DTAmbaAlbumViewController.h
//  dispatchdemo
//
//  Created by lsq on 17/1/11.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DTAmbaAlbumViewController : UIViewController<UITableViewDelegate,UITableViewDataSource>

@property(nonatomic,strong)UITableView *tableView;
@property(nonatomic,strong)NSMutableArray *titleArr;
@property(nonatomic,assign)int  whereFrom; // 0 来自主页 1 来自预览
@end
