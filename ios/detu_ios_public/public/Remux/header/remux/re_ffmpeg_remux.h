#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#include "libff/def.h"
#include "libff/ff-packet-queue.h"

#ifdef __cplusplus
extern "C" {
#endif

 #include "re_ffmpeg.h"

 bool ffmpeg_data_init(struct ffmpeg_data *data);
 void ffmpeg_data_free(struct ffmpeg_data *data);


 void ffmpeg_write_video(struct ffmpeg_data *data, struct video_data *frame);
 void ffmpeg_write_audio(struct ffmpeg_data   *data , struct audio_data *frame);


 void ffmpeg_send(struct ffmpeg_data *data);
    
 void ffmepg_write_avpacket(struct ffmpeg_data   *data , AVPacket packet);

#ifdef __cplusplus
}
#endif
