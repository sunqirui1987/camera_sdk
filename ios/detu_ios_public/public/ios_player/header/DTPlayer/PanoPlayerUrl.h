//
//  PanoPlayerUrl.h
//  PanoPlayer
//
//  Created by qiruisun on 15/7/7.
//  Copyright (c) 2015年 apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ManagerData.h"

typedef void (^PanoPlayerUrlParserSuccess)(ManagerData *mdata);
typedef void (^PanoPlayerUrlErrorSuccess)(NSError *e);
@interface PanoPlayerUrl : NSObject
-(void) setXmlContent:(NSString*)xmlStr;
-(void) setXMlUrl:(NSString*)xmlUrl;
-(void)parseManagerData:(PanoPlayerUrlParserSuccess)success failure:(PanoPlayerUrlErrorSuccess)failure;
@end
