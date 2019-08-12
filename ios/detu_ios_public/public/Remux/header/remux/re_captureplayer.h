//
//  captureplayer.h
//  remuxmediapano
//
//  Created by qiruisun on 16/7/8.
//  Copyright © 2016年 detu. All rights reserved.
//

#pragma once



#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "re_mediasource.h"
#include "re_captureremux.h"
#include "re_audio_resampler.h"


typedef bool (*PreFrameCallBack)(obs_source_frame_s *s, void* arg);
typedef bool (*PreAudioCallBack)(struct audio_data *ad, void* arg);
typedef bool (*VideoCompleteFrameCallBack)(void* arg);



typedef void(*ffp_log_callback)(void *ptr, int level, const char *fmt, va_list vl);


typedef struct{

    char path[1000];
    
    bool isrender_flag;
  
    void* arg;
    
    int video_index;
    
    MediaSourcePlay s;
    
    CaptureRemux cr;
    
    struct audio_resampler audio_resampler_;
    
    struct audio_convert_info conversion;
    
    PreFrameCallBack framecallback;
    PreAudioCallBack audiocallback;
    
    VideoCompleteFrameCallBack endcallback;


    ffp_log_callback  ffp_log;
    int ffp_log_level;
  
    
    pthread_mutex_t video_mutex;
    pthread_mutex_t audio_mutex;

	pthread_t sync_thread;
    
    bool initialized;
    
    bool audio_end;
    bool video_end;
    bool isYuvOutput;
}CapturePlay_s;

//播放地址
MediaSourceMetaData captureplay_open(CapturePlay_s *cp);
    
void captureplay_close(CapturePlay_s *cp);

#ifdef __cplusplus
}
#endif
