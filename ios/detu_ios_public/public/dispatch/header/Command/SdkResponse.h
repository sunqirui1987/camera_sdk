//
//  SdkResponse.h
//  spsdk
//
//  Created by qiruisun on 15/7/22.
//  Copyright (c) 2015年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SdkResponse : NSObject

@property (nonatomic,assign) int errorno;

@end

@interface SdkPathResponse : SdkResponse

@property (nonatomic,assign) NSString* path;

@end

@interface SdkValueResponse : SdkResponse

@property (nonatomic,assign) int value;

@end

@interface SdkListResponse : SdkResponse

@property (nonatomic) NSMutableArray *list;

@end

@interface SdkSettingResponse : SdkResponse

@property (nonatomic) NSMutableArray *keys;
@property (nonatomic) NSMutableArray *values;

@end

@interface SdkStringResponse : SdkResponse

@property (nonatomic) NSString* sValue;

@end

@interface SdkSSIDAndPwdResponse : SdkResponse

@property (nonatomic) NSString* SSID;
@property (nonatomic) NSString* PWD;

@end
