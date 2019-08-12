//
//  config.h
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

#include "re_util.h"
#define MAX_AV_PLANES 8

#define CAPTUREPALYER_LOG_TAG "catputerplayer"

#if defined(__ANDROID__)

#include <android/log.h>
#define  ALOG(level, TAG, ...)  __android_log_print(ANDROID_LOG_INFO,CAPTUREPALYER_LOG_TAG,__VA_ARGS__)

#else

#define VLOG(level, TAG, ...)    ((void)vprintf(__VA_ARGS__))
#define ALOG(level, TAG, ...)    ((void)printf(__VA_ARGS__))

#endif


#define re_fftime_to_milliseconds(ts) (av_rescale(ts, 1000, AV_TIME_BASE))
#define re_milliseconds_to_fftime(ms) (av_rescale(ms, AV_TIME_BASE, 1000))

enum video_format {
    VIDEO_FORMAT_NONE,
    
    /* planar 420 format */
    VIDEO_FORMAT_I420, /* three-plane */
    VIDEO_FORMAT_NV12, /* two-plane, luma and packed chroma */
    
    /* packed 422 formats */
    VIDEO_FORMAT_YVYU,
    VIDEO_FORMAT_YUY2, /* YUYV */
    VIDEO_FORMAT_UYVY,
    
    /* packed uncompressed formats */
    VIDEO_FORMAT_RGBA,
    VIDEO_FORMAT_BGRA,
    VIDEO_FORMAT_BGRX,
    
    /* planar 4:4:4 */
    VIDEO_FORMAT_I444,
};

enum video_colorspace {
    VIDEO_CS_DEFAULT,
    VIDEO_CS_601,
    VIDEO_CS_709,
};

enum video_range_type {
    VIDEO_RANGE_DEFAULT,
    VIDEO_RANGE_PARTIAL,
    VIDEO_RANGE_FULL
};

enum audio_format {
    AUDIO_FORMAT_UNKNOWN,
    
    AUDIO_FORMAT_U8BIT,
    AUDIO_FORMAT_16BIT,
    AUDIO_FORMAT_32BIT,
    AUDIO_FORMAT_FLOAT,
    
    AUDIO_FORMAT_U8BIT_PLANAR,
    AUDIO_FORMAT_16BIT_PLANAR,
    AUDIO_FORMAT_32BIT_PLANAR,
    AUDIO_FORMAT_FLOAT_PLANAR,
};

enum speaker_layout {
    SPEAKERS_UNKNOWN,
    SPEAKERS_MONO,
    SPEAKERS_STEREO,
    SPEAKERS_2POINT1,
    SPEAKERS_QUAD,
    SPEAKERS_4POINT1,
    SPEAKERS_5POINT1,
    SPEAKERS_5POINT1_SURROUND,
    SPEAKERS_7POINT1,
    SPEAKERS_7POINT1_SURROUND,
    SPEAKERS_SURROUND,
};


struct obs_source_frame {
    uint8_t             *data[MAX_AV_PLANES];
    uint32_t            linesize[MAX_AV_PLANES];
    
    
    uint32_t            width;
    uint32_t            height;
    uint64_t            timestamp;
    
    int   format;
    float               color_matrix[16];
    bool                full_range;
    float               color_range_min[3];
    float               color_range_max[3];
    bool                flip;
    
    int					index;
    int64_t             frame_index;
    int64_t					duration;
    int64_t             duration_frame;
};
typedef struct obs_source_frame obs_source_frame_s;


struct obs_source_audio {
	const uint8_t       *data[MAX_AV_PLANES];
	uint32_t            frames;

	enum speaker_layout speakers;
	enum audio_format   format;
	uint32_t            samples_per_sec;

	uint64_t            timestamp;
	int					index;
	int64_t				frame_index;
	int64_t					duration;

	int64_t             duration_frame;
};
typedef struct obs_source_audio obs_source_audio_s;

struct audio_convert_info {
	uint32_t            samples_per_sec;
	enum audio_format   format;
	enum speaker_layout speakers;
};


typedef struct MediaSourceMetaData{

	int64_t bit_rate;
	int width;
	int height;
	int fps;

	int sample_rate;
	int channel_layout;

	int64_t total_duration_frame;
	int64_t total_duration;


	char* original_format ;

    char* metadata_title ;
    
    bool is_have_audio;
  

}MediaSourceMetaData;

#ifdef __cplusplus
}
#endif
