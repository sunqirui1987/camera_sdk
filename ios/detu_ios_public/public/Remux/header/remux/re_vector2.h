//
//  re_vector2.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/25.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_vector2_h
#define re_vector2_h



#include <math.h>
#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif
union _Vector2 {
    struct {
        float x, y;
    };
   
    float v[2];
};
typedef union _Vector2 Vector2;

static inline Vector2 vector2Make(float x, float y) {
    Vector2 v = {x, y};
    return v;
}

#ifdef __cplusplus
}
#endif

#endif /* re_vector2_h */
