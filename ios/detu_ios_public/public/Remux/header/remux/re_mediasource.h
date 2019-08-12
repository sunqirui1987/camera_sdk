//
//  mediasource.h
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

#include "libff/ff-demuxer.h"
#include "re_config.h"
#include "re_ffmpeg.h"


typedef bool (*ReadVideoCallbackProc)(struct obs_source_frame *video,int index, void* op);
typedef bool (*ReadAudioCallbackProc)(struct obs_source_audio *audio, int index, void* op);


typedef struct {
    char* input;

    void* op;
    int index;
    ReadVideoCallbackProc videoproc;
    ReadAudioCallbackProc audioproc;
}MediaSourceConfig;

typedef struct  {
    struct ff_demuxer *demuxer;
    struct SwsContext *sws_ctx;
    int sws_width;
    int sws_height;
    enum AVPixelFormat sws_format;
    uint8_t *sws_data;
    int sws_linesize;
    
    
    
    enum AVDiscard frame_drop;
    int audio_buffer_size;
    int video_buffer_size;
    
    int audio_frame_index;
    int video_frame_index;

    MediaSourceConfig config;
    
    bool isstop;
    
    pthread_mutex_t mutex;
    const char* decoderName;
}MediaSourcePlay;


MediaSourceMetaData mediasource_play(MediaSourcePlay* s);
void mediasource_close(MediaSourcePlay* s);

bool audio_from_scale(MediaSourcePlay* s,struct ff_frame *frame, struct obs_source_audio *obs_frame);
bool video_frame_scale(MediaSourcePlay* s,struct ff_frame *frame, struct obs_source_frame *obs_frame);

bool update_sws_context(MediaSourcePlay* s,AVFrame *frame);
#ifdef __cplusplus
}
#endif
