//
//  PictureAndMovieBrowerViewController.h
//  AmbarellaSDK_Demo
//
//  Created by lsq on 16/12/6.
//  Copyright © 2016年 detu. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PictureAndMovieBrowerViewController : UIViewController
@property (nonatomic,strong)NSString *playbackPath;
@property (nonatomic,assign)int movieOrPic; // 0 pic，1movie
@property (nonatomic,strong)NSString *downloadPath;
@property (nonatomic,strong)NSString *fileName;
@property (nonatomic,copy)NSString *device;

@property (nonatomic,strong)IBOutlet UILabel *lab_playTime;
@property (nonatomic,strong)IBOutlet UILabel *lab_totalTime;
@property (nonatomic,strong)IBOutlet UISlider *slider;

@end
