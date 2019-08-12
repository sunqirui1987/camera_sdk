//
//  re_gLsphere2fisheye.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/25.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_gLsphere2fisheye_h
#define re_gLsphere2fisheye_h

#include <stdio.h>

#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "re_opengl_const.h"
void twin_initShader(GLES2_Renderer *renderer);

void twin_initPointCoords(GLES2_Renderer *renderer);
void twin_initTexCoords(GLES2_Renderer *renderer);

void twin_draw(GLES2_Renderer *renderer);


Vector2 twin_getImageXY(GLES2_Renderer *renderer, int x, int y, re_lens len);
#ifdef __cplusplus
}
#endif
#endif /* re_gLsphere2fisheye_h */
