//
//  EAGLOffscreenSurface.hpp
//  PanoPlayer
//
//  Created by chao on 2018/5/31.
//  Copyright © 2018年 detu. All rights reserved.
//

#ifndef EAGLOffscreenSurface_hpp
#define EAGLOffscreenSurface_hpp

#include <stdio.h>
#include "GLOffscreenSurface.h"

namespace DetuPanoPlayer {
    
    struct EAGLOffscreenSurfacePrivate;
    
    class EAGLOffscreenSurface : public GLOffscreenSurface {
    private:
        EAGLOffscreenSurfacePrivate* mNSOpenglOffscreenSurfacePrivate;
    public:
        EAGLOffscreenSurface(PanoPlayer* panoPlayer);
        ~EAGLOffscreenSurface();
        void initOpenglContext() override;
        void eglMakeCurrent() override;
        void destroyOpenglContext() override;
    };
}


#endif /* EAGLOffscreenSurface_hpp */
