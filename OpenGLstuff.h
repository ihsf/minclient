#ifndef _OPENGLSTUFF_H
#define _OPENGLSTUFF_H

#define GL_GLEXT_PROTOTYPES

#include "Engine.h"
#include "Font.h"
#include "Profiler.h"
#include "Etc1.h"
#include "OpenGLES2stuff.h"
#include "Sensors.h"

#ifndef COMPRESSED_RGBA_S3TC_DXT1_EXT
	#define COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#endif
class OpenGLstuff{
	public:
		OpenGLstuff(SDL_Window* mainWindow_);
		~OpenGLstuff();

		void init();

		void render();
		void swapBuffers();
    void printCompressedTextureAvailability();

		void setExitKeyPressedTime(float time);	

		unsigned char *frameBufferPointer;
    unsigned char *frameBufferPointerRect[MAX_SERVERS];
    unsigned int framebufferTexIDRect[MAX_SERVERS];  

    unsigned char *rectCopyBuffers[MAX_SERVERS];

#ifndef ANDROID
    PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
    PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;
#endif

	private:		
    SDL_Window* mainWindow;

		void generateFramebufferTexture();
    void generateFramebufferTextureNoRect();
    void generateFramebufferTextureRect();
		unsigned int framebufferTexID;  
    

    void drawFrameBufferNoRect();
    void drawFrameBufferRect();
    void drawFPS();
    void drawProfilerOutput();
    void drawHUD();
    
    bool isPVRTCSupported();
    bool isPVRTC2Supported();
    bool isS3TCSupported();
    bool isETCSupported();
    bool isDXT1Supported();
    bool isFrontBufferSupported();
};

#endif
