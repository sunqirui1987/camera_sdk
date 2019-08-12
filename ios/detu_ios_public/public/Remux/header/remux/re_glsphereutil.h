//
//  gl_sphereutil.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/25.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef gl_sphereutil_h
#define gl_sphereutil_h

#include <stdio.h>

#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "re_vector3.h"
typedef  struct {

    float dx;
    float dy;
    float dz;
    int width;
    int height;
    float theta;
    float phi;
    float x;
    float y;
    
}gl_sphere_struct;

void re_sphere_rotation(Vector3 v,float radians,Vector3* b);

void re_init_gl_sphere_struct(gl_sphere_struct *sp);


void re_cal_xyz_from_theta_phi(gl_sphere_struct *sp);
void re_cal_sphere_xyz(gl_sphere_struct *sp,int px,int py);


#ifdef __cplusplus
}
#endif
#endif /* gl_sphereutil_h */
