//
//  re_util.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/25.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_util_h
#define re_util_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif
int startsWith(const char *full, const char *prefix);

int strsplit (const char *str, char *parts[], const char *delimiter);

const char* hasPrefix(const char* str, const char* prefix);



float re_Horiz(float destx, float horiz_d);

float re_Verte(float desty, float vert_e);

bool Re_YUV420_To_BGR24(unsigned char *puc_y, unsigned char *puc_u, unsigned char *puc_v, unsigned char *puc_rgb, int width_y, int height_y);

void re_pixelYuvToYuv420p(unsigned char *src, unsigned char *dst, int w, int h);

void re_reversalByLine(unsigned char *data, int width, int height, int channel);

#ifdef __cplusplus
}
#endif

#endif /* re_util_h */
