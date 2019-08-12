//
//  MediaInfo.h
//  MediaMetaLib
//
//  Created by chao on 2017/4/6.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, DTMediaType) {
    DT_Pic,
    DT_Video,
    DT_Type_UnKnow
};

@interface DTMediaInfo : NSObject

@property(nonatomic, assign) DTMediaType mediaType;
@property(nonatomic, assign) int width;
@property(nonatomic, assign) int height;

@end
