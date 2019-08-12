//
//  PanoPlayer.h
//  ios_player_lib
//
//  Created by chao on 2017/11/4.
//  Copyright © 2017年 detu. All rights reserved.
//

#import "IosPanoPlayer.h"
#import "PanoPlayerUrl.h"
@class HotpotManager;
@class VrEventObjectManager;
@interface PanoPlayer : IosPanoPlayer

-(void)playByXml:(PanoPlayerUrl*) panoPlayerUrl;

-(void)playByXml:(PanoPlayerUrl*) panoPlayerUrl options:(NSMutableArray<PanoPlayerOption *> *)options;
-(void)setHotManager: (HotpotManager*)hotm;
-(nullable VrEventObjectManager*)getVrEventManager;
-(nullable HotpotManager*)getHotManager;
@end
