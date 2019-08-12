//
//  SettingViewController.h
//  dispatchdemo
//
//  Created by lsq on 17/1/11.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DTSpsSettingViewController : UIViewController<UITableViewDelegate,UITableViewDataSource,UIActionSheetDelegate>

@property(nonatomic,strong)UITableView *tableView;
@property(nonatomic,strong)NSArray *titleArr;


@end
