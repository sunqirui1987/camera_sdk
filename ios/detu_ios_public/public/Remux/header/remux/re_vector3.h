
#ifndef re_vector3_h
#define re_vector3_h

#include <math.h>
#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif
union _Vector3 {
    struct {
        float x, y, z;
    };
    struct {
        float r, g, b;
    };
    struct {
        float s, t, p;
    };
    float v[3];
};
typedef union _Vector3 Vector3;

static inline Vector3 vector3Make(float x, float y, float z) {
    Vector3 v = {x, y, z};
    return v;
}

static inline float vector3Length(Vector3 vector) {
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1] + vector.v[2] * vector.v[2]);
}

static inline Vector3 vector3Normalize(Vector3 vector) {
    float scale = 1.0f / vector3Length(vector);
    Vector3 v = {vector.v[0] * scale, vector.v[1] * scale, vector.v[2] * scale};
    return v;
}
#ifdef __cplusplus
}
#endif
#endif /* re_vector3_h */