//
//  re_opengl_const.h
//  remuxmediapano
//
//  Created by qiruisun on 16/8/25.
//  Copyright © 2016年 detu. All rights reserved.
//

#ifndef re_opengl_const_h
#define re_opengl_const_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>





#include "libff/def.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(MAC_QT)
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>


#elif defined(__APPLE__)
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#else
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>
#endif

#define RE_MAX_LEN_CAMERA 8


#include "re_config.h"
#include "re_ffmpeg.h"

#include "re_matrix4.h"
#include "re_vector3.h"
#include "re_vector2.h"
#include "re_glsphereutil.h"
#include "re_image.h"
    
#ifndef GL_RGBA8_OES
#define GL_RGBA8_OES GL_RGBA8
#endif


#ifndef RE_COUNTX
#define RE_COUNTX 512
#endif
    
 
#ifndef RE_COUNTY
#define RE_COUNTY 256
#endif

    
#define PBO_COUNT 2

#define TEXTURE_BUFFER_COUNT 2


#define RE_POINTCOUNT (RE_COUNTX+1)*RE_COUNTY*2
#define RE_POINT3DCOUNT RE_POINTCOUNT * 3
#define RE_POINT2DCOUNT RE_POINTCOUNT * 2

#define RE_GLES_STRINGIZE(x)   #x
#define RE_GLES_STRINGIZE2(x)  RE_GLES_STRINGIZE(x)
#define RE_GLES_STRING(x)      RE_GLES_STRINGIZE2(x)


#define TODEGRESS(a) a * 180.0f/M_PI
#define TORADIANS(a) a * M_PI/180.0f
  
#if defined(MAC_QT) || defined(WIN32)
    static const char MOBILE_HIGHP_FSH_STR[] = RE_GLES_STRINGIZE(
                                                                
                                                                 );

    
#else
    static const char MOBILE_HIGHP_FSH_STR[] = RE_GLES_STRINGIZE(
                                                                 precision highp float;
                                                                 precision highp int;
                                                                 precision lowp sampler2D;
                                                                 precision lowp samplerCube;
                                                                 
                                                                 );

#endif
    



typedef  struct texture_s{
    
    const GLfloat *preferredConversion;
    GLuint textures[3];
    GLint uniformSamplers[3];
    GLint uniform[1];
    
    int width;
    int height;

	float xrange;
	float yrange;
    
    
}GLES2_Texture;



typedef enum {
    DEVICE_TWINS,
    DEVICE_SPHERE,
    DEVICE_FLAT
}GLES2_Deviceid;

typedef enum {
	GLES2_RENDER_TWINS,
	GLES2_RENDER_SPHERE,
	GLES2_RENDER_UV,
    GLES2_RENDER_FLAT
}GLES2_Renderer_Type;

//纹理创建方式，0:标准软解创建方式 1:android surfaceTexture 2:ios cv_texture
typedef enum {
    SOFT,
    ANDROID_SURFACE_TEXTURE,
    IOS_CVOpenGLESTexture
} GLES2_Renderer_Texture_Platform;

typedef struct {
    int view_w;
    int view_h;

	int currentindex;
	int lennum;
    
    GLES2_Deviceid deviceid;
	GLES2_Renderer_Type render_type;
    
  //  GLfloat points[RE_POINT3DCOUNT]; //
    GLfloat plane_points[RE_POINT2DCOUNT]; // (COUNTX+1)*COUNTY*2 * 2
    



	GLfloat *spriteTexcoords[RE_MAX_LEN_CAMERA];// [RE_POINT2DCOUNT]; // (COUNTX+1)*COUNTY*2 * 2
	GLfloat *spriteTexcoordsExtra[RE_MAX_LEN_CAMERA];
    
    
    Matrix4 projectionMatrix;
    Matrix4 modelMatrix;
    Matrix4 viewMatrix;
    Matrix4 mvPMatrix;
    
    GLuint mProgramHandle;
    GLuint mMVPMatrixHandle;
    GLuint mTextureUniformHandle;
    GLuint mPositionHandle;
    GLuint misforwardHandle;
    GLuint mIsRewindHandle;
    
    
    
    
    GLint _uniformSamplers[3];
    GLint _uniform[1];
    

    GLuint msizeHandle;
    
    
    GLuint mTextureCoordinateHandle;
    GLuint mTextureCoordinate_Extra_Handle;
    
    
    GLuint mTextureCoordinateHandleA;
    GLuint mTextureCoordinateHandleB;
    GLuint mTextureCoordinateHandleC;
    GLuint mTextureCoordinateHandleD;
    
    GLuint mdeviceTypeHandel;
    GLuint mmodeTypeHandel;
    
    
    GLuint yaw0Handle;
    GLuint yaw1Handle;
    float yaw0;
    float yaw1;
    



	GLuint cx_Handle;
	GLuint cy_Handle;
	GLuint r_Handle;
	GLuint xrate_Handle;
	GLuint yrate_Handle;
	GLuint dre_Handle;

    bool ismask;
    GLuint isMaskHandle;
    
   

    
    float v_maskdegree;
    
    
    Vector3 yaw_rotation;
    Vector3 pitch_rotation;
    Vector3 roll_rotation;
    
    Vector3 sphere_vector;
    
    
    gl_sphere_struct spheredata;
    re_image imgdata;
    
    GLES2_Texture texture;
    
    
	GLuint movieFramebuffer, movieRenderbuffer;
    

    GLuint pboIds[PBO_COUNT];
    bool isuse_pbo;
    bool isUseFbo;
    
    bool isYuvOutPut;
    bool isRewind; //是否倒置图像
    GLuint isYuvOutputHandle;

    GLES2_Renderer_Texture_Platform texturePlatform;

    GLuint vertextArrayBuffer;
    GLuint textureArrayBuffer[TEXTURE_BUFFER_COUNT];
}GLES2_Renderer;





static inline bool re_gles2_compileShader(GLuint *shader,GLenum type,const char *str)
{
    GLint status;
    const GLchar *source;
    
    source = str;
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    

    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        
        LOGE("compileShader:\n%s\n \n", log);
        
        free(log);
    }

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        glDeleteShader(*shader);
        return false;
    }
    
    return true;
}

static inline bool re_gles2_linkProgram(GLuint prog)
{
    GLint status;
    
    glLinkProgram(prog);
    

    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        av_log(NULL, AV_LOG_ERROR, "linkProgram:\n%s", log);
        
        free(log);
    }

    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0)
        return false;
    
    return true;
}

static inline bool re_gles2_validateProgram(GLuint prog)
{
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        av_log(NULL, AV_LOG_ERROR, "Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0)
        return false;
    
    return true;
}

static inline GLuint re_gles2_loadShaders(GLES2_Renderer *renderer,const char* vsh_str ,const char* fsh_str)
{
    GLuint vertShader, fragShader;
    
    // Create shader program
    renderer->mProgramHandle = glCreateProgram();
    
    
    if (!re_gles2_compileShader(&vertShader,GL_VERTEX_SHADER,vsh_str))
    {
        LOGE("Failed to compile vertex shader");
        return 0;
    }
    
    
    if (!re_gles2_compileShader(&fragShader,GL_FRAGMENT_SHADER,fsh_str))
    {
        LOGE("Failed to compile vertex shader");
        return 0;
    }
    
    
    // Attach vertex shader to program
    glAttachShader(renderer->mProgramHandle, vertShader);
    
    // Attach fragment shader to program
    glAttachShader(renderer->mProgramHandle, fragShader);
    
    
    // Link program
    if (!re_gles2_linkProgram(renderer->mProgramHandle))
    {
        LOGE("Failed to link program: %d", renderer->mProgramHandle);
        
        if (vertShader)
        {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader)
        {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (renderer->mProgramHandle)
        {
            glDeleteProgram(renderer->mProgramHandle);
            renderer->mProgramHandle = 0;
        }
        
        return 0;
    }
    
    
    
    // Release vertex and fragment shaders
    if (vertShader)
        glDeleteShader(vertShader);
    if (fragShader)
        glDeleteShader(fragShader);
    
    return renderer->mProgramHandle;
}

#ifdef __cplusplus
}
#endif

#endif /* re_opengl_const_h */
