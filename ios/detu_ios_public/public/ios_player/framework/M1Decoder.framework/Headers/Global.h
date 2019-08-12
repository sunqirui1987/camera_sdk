#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <functional>
#include <iostream>

typedef enum stream_type_e{
	StreamTypeRtmp = 1,			//网络RTMP流
	StreamTypePrivate,			//网络私有流
	StreamTypeUnknow,
}stream_type_e;

typedef enum decode_type_e{
    DecodeTypeSoft = 0,        //采用intel gpu硬解码
	DecodeTypeIntel = 1,		//采用intel gpu硬解码
	DecodeTypeCuda = 2,		//采用nvidia gpu硬解码
    DecodeTypeVtb = 3,        //ios videotoolbox
    DecodeTypeVda = 4,        //mac vda
    DecodeTypeMediaCodec = 5, //android mediacodec
} decode_type_e;

typedef enum m1_pixel_format_e {
	PIX_FMT_NONE = -1,
	PIX_FMT_YUV420P,   ///< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	PIX_FMT_YUV422P,   ///< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
	PIX_FMT_YUV444P,   ///< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples)
	PIX_FMT_NV12,      ///< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V)
	PIX_FMT_NV21,      ///< as above, but U and V bytes are swapped

	PIX_FMT_DXVA2_VLD,    ///< HW decoding through DXVA2, Picture.data[3] contains a LPDIRECT3DSURFACE9 pointer
	PIX_FMT_VDPAU,        ///< HW acceleration through VDPAU, Picture.data[3] contains a VdpVideoSurface
	PIX_FMT_VDA,          ///< HW acceleration through VDA, data[3] contains a CVPixelBufferRef
	/**
	*  HW acceleration through QSV, data[3] contains a pointer to the
	*  mfxFrameSurface1 structure.
	*/
	PIX_FMT_QSV,
	/**
	* HW acceleration through CUDA. data[i] contain CUdeviceptr pointers
	* exactly as for system memory frames.
	*/
	PIX_FMT_CUDA,
	PIX_FMT_VIDEOTOOLBOX, ///< hardware decoding through Videotoolbox]
	PIX_FMT_NB,           ///< number of pixel formats, DO NOT USE THIS if you want to link with shared libav* because the number of formats might differ between versions
    PIX_FMT_MEDIACODEC,
}m1_pixel_format_e;

typedef struct m1_video_frame_s{

#define k_NUM_DATA_POINTERS 8

	int w;				//Read-only, width
	int h;				//Read-only, height

	m1_pixel_format_e format;	//Read-only, pixel format
	int planes;					//Read-only, planes
	int linesize[k_NUM_DATA_POINTERS];		//Read-only, data length in bytes
	uint8_t *data[k_NUM_DATA_POINTERS];		//Read-write,data for display

	void* opaque;
}m1_video_frame_s;


typedef std::function<void(m1_video_frame_s **video, int index, unsigned int timestamp)> func_display_callback;

typedef struct m1_player_config_s{
	std::string				url;
	func_display_callback	videoproc;
}m1_player_config_s;


#endif
