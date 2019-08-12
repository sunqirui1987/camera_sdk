#ifndef re_panorender_uv_h
#define re_panorender_uv_h

#include <stdio.h>

#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "re_opengl_const.h"

bool pano_initShader(GLES2_Renderer *renderer);

void pano_initPointCoords(GLES2_Renderer *renderer);
void pano_initTexCoords(GLES2_Renderer *renderer);

void pano_draw(GLES2_Renderer *renderer);

Vector3 pano_getImageXY(GLES2_Renderer *renderer, int x, int y, re_lens len);


#ifdef __cplusplus
}
#endif
#endif /* re_gLsphere2fisheye_h */
