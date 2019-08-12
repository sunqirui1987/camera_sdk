//
//  re_glflat.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/27.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_glflat_h
#define re_glflat_h

#include <stdio.h>


#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "re_opengl_const.h"

void flat_initShader(GLES2_Renderer *renderer);

void flat_initPointCoords(GLES2_Renderer *renderer);
void flat_initTexCoords(GLES2_Renderer *renderer);

void flat_draw(GLES2_Renderer *renderer);

#ifdef __cplusplus
}
#endif
#endif /* re_glflat_h */
