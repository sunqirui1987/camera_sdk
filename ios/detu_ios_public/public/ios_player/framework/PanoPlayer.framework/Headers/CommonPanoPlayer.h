//
//  CommonPanoPlayer.hpp
//  PanoPlayer
//
//  Created by chao on 2017/10/28.
//  Copyright © 2017年 detu. All rights reserved.
//

#ifndef CommonPanoPlayer_hpp
#define CommonPanoPlayer_hpp

#include <stdio.h>
#include "PanoPlayer.h"

namespace DetuPanoPlayer {

    class CommonPanoPlayer : public PanoPlayer {
    public:
        CommonPanoPlayer();

        CommonPanoPlayer(PanoPlayerPlatform platForm);

        ~CommonPanoPlayer();

        void setPlugin(Plugin *plugin);

        Plugin *configPlugin(PanoramaData panoData, vector<PlayerOption> options);

    private:
        Plugin *cachePlugin;
    };
}

#endif /* CommonPanoPlayer_hpp */
