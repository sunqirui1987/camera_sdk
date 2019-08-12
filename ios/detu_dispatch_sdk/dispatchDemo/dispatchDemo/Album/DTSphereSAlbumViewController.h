//
//  DTSphereSAlbumViewController.h
//  dispatchdemo
//
//  Created by lsq on 17/1/12.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DTSphereSAlbumViewController : UIViewController<UITableViewDelegate,UITableViewDataSource>

@property(nonatomic,strong)UITableView *tableView;
@property(nonatomic,strong)NSArray *titleArr;


@end
