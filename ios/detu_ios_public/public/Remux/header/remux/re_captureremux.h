//
//  captureremux.h
//  remuxmediapano
//
//  Created by qiruisun on 16/7/8.
//  Copyright © 2016年 detu. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif


#include "re_opengl_const.h"
#include "re_ffmpeg_remux.h"




typedef struct {

    int x;
    int y;
    
    int origin_width;
    int origin_height;
    
    bool is_origin_push;
    
    int width;
    int height;
    
    int panowidth;
    int panoheight;
    

    int rate; //码率
    int fps;

    char* save_file;
    char* save_format;
    char* deivce_name;
   
    
    struct ffmpeg_data data;
    
    pthread_t save_thread;
    
    bool thread_stop;
    
    bool initialized;

    bool useHardwareEncode;

    enum AVPixelFormat srcPixFmt;
    
}CaptureRemux;

bool capture_init(CaptureRemux* cr);

void capture_fromaudio(CaptureRemux* cr,struct audio_data* data);
    
GLubyte*  capture_formgl_v3(CaptureRemux* cr,GLES2_Renderer* renderer);


bool capture_formgl(CaptureRemux* cr,GLES2_Renderer* renderer);
    
void *capture_save_thread(void* arg);

bool capture_close(CaptureRemux* cr);

#ifdef __cplusplus
}
#endif
