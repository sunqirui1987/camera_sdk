//
//  SpherePlugin.h
//  PanoPlayer
//
//  Created by chao on 2017/10/27.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IosPlugin.h"

#define  PLUGIN_DESCRIPTION_SPHERE @"sphere_plugin"

@interface ImagePlugin : Plugin
-(void)setPanoData:(PanoData*) panoData options:(NSMutableArray<PanoPlayerOption*>*) options;
-(NSString*)getDescription;
@end
