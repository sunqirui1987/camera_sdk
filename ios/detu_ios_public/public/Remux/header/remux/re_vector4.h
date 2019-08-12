//
//  vector4.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/25.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_vector4_h
#define re_vector4_h

#include <stdio.h>
#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif
#ifdef WIN32
#pragma pack(push,16)
union _Vector4 {
	struct {
		float x, y, z, w;
	};
	struct {
		float r, g, b, a;
	};
	struct {
		float s, t, p, q;
	};
	float v[4];
};
#pragma pack(pop)
#else
union _Vector4 {
	struct {
		float x, y, z, w;
	};
	struct {
		float r, g, b, a;
	};
	struct {
		float s, t, p, q;
	};
	float v[4];
} __attribute__((aligned(16)));
#endif // WIN32

typedef union _Vector4 Vector4;

static inline Vector4 vector4Make(float x, float y, float z, float w) {
    Vector4 v = {x, y, z, w};
    return v;
}
#ifdef __cplusplus
}
#endif
#endif /* re_vector4_h */
