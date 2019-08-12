//
//  re_glsphere.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/30.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_glsphere_h
#define re_glsphere_h

#include <stdio.h>

#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif


#include "re_opengl_const.h"

void sphere_initShader(GLES2_Renderer *renderer);

void sphere_initPointCoords(GLES2_Renderer *renderer);
void sphere_initTexCoords(GLES2_Renderer *renderer);

void sphere_draw(GLES2_Renderer *renderer);
#ifdef __cplusplus
}
#endif
#endif /* re_glsphere_h */
