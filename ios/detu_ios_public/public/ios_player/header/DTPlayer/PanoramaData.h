//
//  PanoramaData.h
//  PanoPlayer
//
//  Created by qiruisun on 15/7/7.
//  Copyright (c) 2015年 apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IosPanoPlayerDef.h>



@interface PanoramaData : NSObject
@property  (nonatomic , copy)NSString* name;
@property  (nonatomic , copy)NSString* title;
@property  (nonatomic , copy)NSString* thumbUrl;
@property (nonatomic , strong)Preview* preview;
@property (nonatomic , strong)PanoNodeView* imageviewdata;
@property (nonatomic , strong)PanoNodeImage* image;
@property (nonatomic , strong)NSMutableArray* hotspotList;
@end




