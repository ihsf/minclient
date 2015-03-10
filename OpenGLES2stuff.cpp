#include "OpenGLES2stuff.h"

// Functions loadShader() and createProgram(), define LOGI from Android NDK with the follwing license:
//  * Copyright (C) 2009 The Android Open Source Project
//  * Licensed under the Apache License, Version 2.0 (the "License");
//  * http://www.apache.org/licenses/LICENSE-2.0

#ifdef ANDROID
  #include <android/log.h>
  #ifndef LOG_TAG
    #define  LOG_TAG    "org.ivci.qwrt"
  #endif
  #ifndef LOGI
    #define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
  #endif

  PFN_GVR_FrontBuffer OpenGLES2stuff::egl_GVR_FrontBuffer;
  EGLSurface OpenGLES2stuff::windowSurface = NULL;
  EGLDisplay OpenGLES2stuff::display = NULL;
#endif

unsigned int OpenGLES2stuff::programID = 0;
int OpenGLES2stuff::gPositionHandle = 0;
int OpenGLES2stuff::gTexCoordHandle = 0;
int OpenGLES2stuff::uMatrixLocation = 0;
int OpenGLES2stuff::uTextureUnitLocation = 0;
vector<GLuint> OpenGLES2stuff::programIDs;
vector<GLuint> OpenGLES2stuff::shaderIDs;

OpenGLES2stuff::~OpenGLES2stuff(){
  for (int i = 0; i < (int)shaderIDs.size(); i++){
    glDeleteShader(shaderIDs[i]);
  }

  for (int i = 0; i < (int)programIDs.size(); i++){
    glDeleteProgram(programIDs[i]);
  }
}

void OpenGLES2stuff::init(){
#ifdef ANDROID
  programID = createProgram(gVertexShader, gFragmentShader);
  gPositionHandle = glGetAttribLocation(programID, "a_Position");
  gTexCoordHandle = glGetAttribLocation(programID, "a_TextureCoordinates");
  uMatrixLocation = glGetUniformLocation(programID, "u_Matrix");
  uTextureUnitLocation = glGetUniformLocation(programID, "u_TextureUnit");
#else
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    cerr << "GLEW init failed!" << std::endl;
    exit(EXIT_FAILURE);
}
#endif
}

bool OpenGLES2stuff::setFrontBuffer(){
#ifdef ANDROID
  if(!Engine::useGVRFrontBuffer)
    return false;

  // Galaxy Note 4
  display = eglGetDisplay( EGL_DEFAULT_DISPLAY );
  windowSurface = eglGetCurrentSurface( EGL_DRAW );		// swapbuffers will be called on this

  // look for the extension
  egl_GVR_FrontBuffer = (PFN_GVR_FrontBuffer)eglGetProcAddress("egl_GVR_FrontBuffer");

  if(egl_GVR_FrontBuffer){
    LOGI("egl_GVR_FrontBuffer address succeeded");
    printf("egl_GVR_FrontBuffer address succeeded\n"); 
    strcat(Engine::debugMessage, "egl_GVR_FB address succ. ");

    void* ret = egl_GVR_FrontBuffer( windowSurface );
    if(ret){
      LOGI("egl_GVR_FrontBuffer call succeeded");
      printf("egl_GVR_FrontBuffer call succeeded\n");
      strcat(Engine::debugMessage, "egl_GVR_FB call succ. ");
    } else {
      strcat(Engine::debugMessage, "egl_GVR_FB call NOT succ. ");
    }

    glEnable(GL_WRITEONLY_RENDERING_QCOM);
 
    return true;
  } else {
    Engine::useGVRFrontBuffer = false;
    LOGI("egl_GVR_FrontBuffer address failed");
    printf("egl_GVR_FrontBuffer address failed\n");
    strcat(Engine::debugMessage, "egl_GVR_FB address failed. ");
    return false;
  }
#endif

  return false;
}

void OpenGLES2stuff::swapBuffer(){
#ifdef ANDROID
  eglSwapBuffers(display, windowSurface);	// swap buffer will operate que/deque related process internally
#endif
}


GLuint OpenGLES2stuff::loadShader(GLenum shaderType, const char* source) {
  GLuint shader = glCreateShader(shaderType);
  if(shader){
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled) {
      GLint infoLength = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

      if(infoLength) {
        char* buf = (char*)malloc(infoLength);
        if (buf) {
          glGetShaderInfoLog(shader, infoLength, NULL, buf);
          printf("Error compiling %u:\n%s\n", shaderType, buf);
#ifdef ANDROID
          LOGI("Error compiling %u:\n%s\n", shaderType, buf);
#endif
          free(buf);
        }
        glDeleteShader(shader);
        shader = 0;

        SDL_Delay(1000);
        exit(7);
      }
    }
  }

  shaderIDs.push_back(shader);

  return shader;
}

GLuint OpenGLES2stuff::createProgram(const char* pVertexSource, const char* pFragmentSource) {
  GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
  if(!vertexShader){
    return 0;
  }

  GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
  if(!pixelShader){
    return 0;
  }

  GLuint program = glCreateProgram();
  if(program){
    glAttachShader(program, vertexShader);
    glAttachShader(program, pixelShader);

    glLinkProgram(program);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if(linkStatus != GL_TRUE) {
      exit(8);
      GLint bufLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);

      if (bufLength) {
        char* buf = (char*) malloc(bufLength);
        if(buf) {
          glGetProgramInfoLog(program, bufLength, NULL, buf);
          printf("Could not link program: %s\n", buf);
          free(buf);
        }
      }
      glDeleteProgram(program);
      program = 0;
    }
  }

  programIDs.push_back(program);

  return program;
}
