//
// Created by chao on 2017/3/23.
//

#ifndef ANDROID_RE_GLSPHERE_TOYUV_H
#define ANDROID_RE_GLSPHERE_TOYUV_H

#define FBOYUV_VERTEXT_SIZE 12
#define FBOYUV_TEXTURE_SIZE 8

#include <stdbool.h>

typedef struct FboToYuv {
    int programHandle;
    int textureHandle;
    int textureSize;
    int aPosition;
    int aTextureCoord;
    int uniType;
    float vertextCoordsY[FBOYUV_VERTEXT_SIZE];
    float vertextCoordsU[FBOYUV_VERTEXT_SIZE];
    float vertextCoordsV[FBOYUV_VERTEXT_SIZE];
    float textureCoordsY[FBOYUV_TEXTURE_SIZE];
    float textureCoordsU[FBOYUV_TEXTURE_SIZE];
    float textureCoordsV[FBOYUV_TEXTURE_SIZE];
} FboToYuv;

bool reFboTextureToYuvSetup(FboToYuv* fboToYuv);

void reFboTextureToYuv420pOnRender(FboToYuv* fboToYuv, unsigned char *dstData, int* ids, int width,
                           int height);

#endif //ANDROID_RE_GLSPHERE_TOYUV_H
