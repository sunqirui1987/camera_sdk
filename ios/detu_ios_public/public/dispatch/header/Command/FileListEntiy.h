//
//  FileListEntiy.h
//  spsdk
//
//  Created by qiruisun on 15/7/21.
//  Copyright (c) 2015年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseEntiy.h"

//关机
typedef NS_ENUM(NSInteger,FileEntiyType){
    FileEntiyTypePic,
    FileEntiyTypeMov
};

@interface FileEntiy : NSObject


@property (nonatomic) NSString* Name;
@property (nonatomic) NSString* Fpath;//访问地址
@property (nonatomic) NSString* Size;
@property (nonatomic) NSString* TimeCode;
@property (nonatomic) NSString* Time;
@property (nonatomic) NSString* Attr;
@property (nonatomic) NSString* diskPath;//磁盘地址
@property (nonatomic) NSData* thumbData; //缩略图数据

//返回缩略图
-(NSString*)getThumbPath;

//返回大的缩略图
-(NSString*)getBigThumbPath;

//返回类型
-(FileEntiyType)getFileType;

@end

@interface FileListEntiy : BaseEntiy

@property (nonatomic) NSMutableArray* filelist;

@end
