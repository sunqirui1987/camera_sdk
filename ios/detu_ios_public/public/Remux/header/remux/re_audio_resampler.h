//
//  audio_resampler.h
//  remuxmediapano
//
//  Created by qiruisun on 16/7/15.
//  Copyright © 2016年 detu. All rights reserved.
//

#pragma once

#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "re_ffmpeg.h"

struct audio_resampler {
    struct SwrContext   *context;
    bool                opened;
    
    uint32_t            input_freq;
    uint64_t            input_layout;
    enum AVSampleFormat input_format;
    
    uint8_t             *output_buffer[MAX_AV_PLANES];
    uint64_t            output_layout;
    enum AVSampleFormat output_format;
    int                 output_size;
    uint32_t            output_ch;
    uint32_t            output_freq;
    uint32_t            output_planes;
    
    bool isresampler;
    bool iscreate;
    
};

typedef struct audio_resampler audio_resampler_t;

struct resample_info {
    uint32_t            samples_per_sec;
    enum audio_format   format;
    enum speaker_layout speakers;
};



void audio_resampler_create(audio_resampler_t *rs,const struct resample_info *dst,
                                                 const struct resample_info *src);
void audio_resampler_destroy(audio_resampler_t *rs);

bool audio_resampler_resample_audio_output(audio_resampler_t *rs,struct audio_data *data);

bool audio_resampler_resample(audio_resampler_t *rs,
                                     uint8_t *output[], uint32_t *out_frames, uint64_t *ts_offset,
                                     const uint8_t *const input[], uint32_t in_frames);


#ifdef __cplusplus
}
#endif
