#ifndef _HEADTRACKING_H
#define _HEADTRACKING_H

#include <stdio.h>
#include "Engine.h"
#ifdef ANDROID
  #include <jni.h>
#endif

class HeadTracking{
  public:
    HeadTracking();
    ~HeadTracking();

    void getHeadOrientationQuaternion(double* x, double* y, double* z, double* w);

  private:
    void init();
    void initZeissVRone();
    void initGoogleCardBoard();

#ifdef ANDROID
    JNIEnv* env;
    jmethodID zeissVRoneMethodID;
    jobject zeissVRoneActivity;
#endif
};


#endif
