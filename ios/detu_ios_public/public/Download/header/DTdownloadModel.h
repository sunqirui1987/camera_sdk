//
//  DTdownloadModel.h
//  downloadTest
//
//  Created by lsq on 2017/3/30.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DTdownloadModel : NSObject
/*
 *保存文件的沙盒文件夹
 */
@property(nonatomic,strong)NSString *savePath;

/*
 *下载文件地址
 */
@property(nonatomic,strong)NSURL *downloadPath;

@end
