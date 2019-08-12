//
//  re_image.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/25.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_image_h
#define re_image_h

#include <stdio.h>
#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef bool (*re_findcircle_callback)(void* arg, unsigned char* data,int w, int h, int c,char* desc);


typedef struct {


    //畸变校正参数
    float a;
    float b;
    float c;
    float d;
    float e;
    
    // 图一
    int dr;
    int centerx;
    int centery;
    float yaw; // 对应x轴旋转角度
    float pitch; // 对应y轴旋转角度
    float roll; // 对应z轴旋转角度
    
    
    float hd;// 水平平移参数
    float ve;// 垂直平移参数
    float sg;// 水平裁剪参数
    float st;// 垂直裁剪参数

	float degree;
	float maskdegree;
    
}re_lens;

typedef struct {

    int label;
    int width;
    int height;
    int originwidth;
    int originheight;
 
    
    int panow;// 鱼眼对应全景的宽
    int panoh;// 鱼眼对应全景的高
    
    
	re_lens lens[RE_MAX_LEN_CAMERA];
    
    
    void *re_calback_arg;
    re_findcircle_callback callback;

    
}re_image;


static inline void re_ImageParseTwins(re_image *imgdata, const char* desc)
{
    if (desc == NULL || strlen(desc) == 0)
    {
        return;
    }
    
    if (!(startsWith(desc, "2_") || startsWith(desc, "3_") || startsWith(desc, "4_") || startsWith(desc, "6_"))) {
        return;
    }
    
    char* parts[40];
    int ret = strsplit(desc, parts, "_");
    if (ret == -1) {
        return;
    }
    
    
    imgdata->label = atoi(parts[0]);
    
    
	imgdata->lens[0].dr = (float)strtod(parts[1], NULL);
	imgdata->lens[0].centerx = (float)strtod(parts[2], NULL);
	imgdata->lens[0].centery = (float)strtod(parts[3], NULL);
    
	imgdata->lens[0].yaw = (float)strtod(parts[4], NULL);
	imgdata->lens[0].pitch = (float)strtod(parts[5], NULL);
	imgdata->lens[0].roll = (float)strtod(parts[6], NULL);
    
    
    
	imgdata->lens[1].dr = (float)strtod(parts[7], NULL);
	imgdata->lens[1].centerx = (float)strtod(parts[8], NULL);
	imgdata->lens[1].centery = (float)strtod(parts[9], NULL);
    
	imgdata->lens[1].yaw = (float)strtod(parts[10], NULL);
	imgdata->lens[1].pitch = (float)strtod(parts[11], NULL);
	imgdata->lens[1].roll = (float)strtod(parts[12], NULL);
    
    
	imgdata->originwidth = (float)atoi(parts[13]);
	imgdata->originheight = (float)atoi(parts[14]);
    
    
    if ( imgdata->lens[0].yaw  < 0) {
        imgdata->lens[0].yaw = imgdata->lens[0].yaw + 180;
    }else{
        imgdata->lens[0].yaw = imgdata->lens[0].yaw - 180;
    }
    
    if ( imgdata->lens[1].yaw  < 0) {
        imgdata->lens[1].yaw = imgdata->lens[1].yaw + 180;
    }else{
        imgdata->lens[1].yaw = imgdata->lens[1].yaw - 180;
    }
    
    
    
        
    if(hasPrefix(desc, "6_")){
        
		imgdata->lens[0].hd = (float)strtod(parts[15], NULL);
		imgdata->lens[0].ve = (float)strtod(parts[16], NULL);
		imgdata->lens[0].sg = (float)strtod(parts[17], NULL);
		imgdata->lens[0].st = (float)strtod(parts[18], NULL);
        
		imgdata->lens[1].hd = (float)strtod(parts[15], NULL);
		imgdata->lens[1].ve = (float)strtod(parts[16], NULL);
		imgdata->lens[1].sg = (float)strtod(parts[17], NULL);
		imgdata->lens[1].st = (float)strtod(parts[18], NULL);
        
        
		imgdata->lens[0].a = (float)strtod(parts[19], NULL);
		imgdata->lens[0].b = (float)strtod(parts[20], NULL);
		imgdata->lens[0].c = (float)strtod(parts[21], NULL);
        
		imgdata->lens[1].a = (float)strtod(parts[22], NULL);
		imgdata->lens[1].b = (float)strtod(parts[23], NULL);
		imgdata->lens[1].c = (float)strtod(parts[24], NULL);
        
        
		imgdata->lens[0].degree = (float)strtod(parts[25], NULL);
		imgdata->lens[0].maskdegree = (float)strtod(parts[26], NULL);

		imgdata->lens[1].degree = (float)strtod(parts[25], NULL);
		imgdata->lens[1].maskdegree = (float)strtod(parts[26], NULL);
        
        
        
    }else{
        
        imgdata->lens[0].a = imgdata->lens[1].a = 0;
        imgdata->lens[0].b = imgdata->lens[1].b = 0;
        imgdata->lens[0].c = imgdata->lens[1].c = 0;
        
        
        
        imgdata->panow =  atoi(parts[15]);
        imgdata->panow =  atoi(parts[16]);
		imgdata->lens[0].degree = strtod(parts[17], NULL);
		imgdata->lens[0].maskdegree = strtod(parts[18], NULL);
		imgdata->lens[1].degree = strtod(parts[17], NULL);
		imgdata->lens[1].maskdegree = strtod(parts[18], NULL);
        
    }
    
    
    
    
}
static inline void re_ImageParseSphere(re_image *imgdata, const char* desc)
{
    if (desc == NULL || strlen(desc) == 0)
    {
        return;
    }
    
    if (!startsWith(desc, "5_") ) {
        return;
    }
    
    char* parts[40];
    int ret = strsplit(desc, parts, "_");
    if (ret == -1) {
        return;
    }
    
    imgdata->label = atoi(parts[0]);
    
    
    imgdata->lens[0].dr = strtod(parts[1], NULL);
    imgdata->lens[0].centerx = strtod(parts[2], NULL);
    imgdata->lens[0].centery = strtod(parts[3], NULL);
    
    imgdata->originwidth = atoi(parts[4]);
    imgdata->originheight = atoi(parts[5]);
	imgdata->lens[0].degree = strtod(parts[6], NULL);
    
    imgdata->lens[0].a = strtod(parts[7], NULL);
    imgdata->lens[0].b = strtod(parts[8], NULL);
    imgdata->lens[0].c = strtod(parts[9], NULL);
    

    


}

static inline void re_ImageFindCircle(re_image *imgdata, obs_source_frame_s *frame)
{

    if (imgdata->lens[0].dr > 10) {
        return;
    }
    
    int frameHeight = frame->height;
 
    int widths[3]  = { (int)frame->linesize[0], (int)frame->linesize[1], (int)frame->linesize[2] };
    int heights[3] = { frameHeight, frameHeight / 2, frameHeight / 2 };
    
    size_t datasize = widths[0] * heights[0] * 3;
    unsigned char *data = (unsigned char *)(malloc( datasize ));
    Re_YUV420_To_BGR24((unsigned char *)frame->data[0], (unsigned char *)frame->data[1], (unsigned char *)frame->data[2], data, widths[0], heights[0]);
    
    
    if (imgdata->callback != NULL) {
        char desc[256];
        imgdata->callback(imgdata->re_calback_arg, data, widths[0], heights[0], 3 ,desc);
        
        re_ImageParseSphere(imgdata, desc);
    }
      
}

#ifdef __cplusplus
}
#endif


#endif /* re_image_h */
