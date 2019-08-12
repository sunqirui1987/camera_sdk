//
//  re_texture.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/25.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_texture_h
#define re_texture_h

#include <stdio.h>

#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "re_opengl_const.h"
void re_deleteTexture(GLES2_Texture * tex);
void re_updateWithObs(GLES2_Texture * tex,obs_source_frame_s *overlay);
#ifdef __cplusplus
}
#endif
#endif /* re_texture_h */
