//
//  re_opengl.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/25.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_opengl_h
#define re_opengl_h


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "re_texture.h"
#include "re_opengl_const.h"
#include "re_matrix4.h"
void Re_GLES2_Setup(GLES2_Renderer* renderer);

int Re_GLES2_RenderBufferSize();

void Re_GLES_SetTexture(GLES2_Renderer* renderer,obs_source_frame_s *overlay);

void Re_GLES2_Render(GLES2_Renderer* renderer);

void Re_GLES2_ReadPixelStart(GLES2_Renderer* renderer, unsigned char* pixelData);

void Re_GLES2_ReadPixelFinish(GLES2_Renderer* renderer);

void Re_GLES2_ParserOffset(GLES2_Renderer* renderer,const char* desc);

void Re_GLES2_Distory(GLES2_Renderer* renderer);

#ifdef __cplusplus
}
#endif
#endif /* re_opengl_h */
