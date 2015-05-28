#include "HeadTracking.h"

HeadTracking::HeadTracking(){
  if(Engine::headTrackingMethod == HeadTrackingMethods::OFF)
    return;

#ifdef ANDROID
  env = NULL;
  zeissVRoneMethodID = 0;
  zeissVRoneActivity = NULL;
#endif

  init();
}

HeadTracking::~HeadTracking(){
}

void HeadTracking::init(){
  if (Engine::headTrackingMethod == HeadTrackingMethods::ZEISS_VR_ONE)
    initZeissVRone();
  else if(Engine::headTrackingMethod == HeadTrackingMethods::ZEISS_VR_ONE)
    initGoogleCardBoard();
  else
    cout << "No head tracking." << endl;
}

void HeadTracking::initZeissVRone(){
#ifdef ANDROID
  // retrieve the JNI environment.
  if(!env){
    env = (JNIEnv*)SDL_AndroidGetJNIEnv();
  }

  if(zeissVRoneMethodID == 0){
    // retrieve the Java instance of the SDLActivity
    zeissVRoneActivity = (jobject)SDL_AndroidGetActivity();

    // find the Java class of the activity. It should be SDLActivity or a subclass of it.
    jclass clazz(env->GetObjectClass(zeissVRoneActivity));

    // find the identifier of the method to call
    zeissVRoneMethodID = env->GetMethodID(clazz, "getRotation", "()[D");
  }

  // clean up the local references. - skip this for now
  //env->DeleteLocalRef(activity);
  //env->DeleteLocalRef(clazz);
#endif
}

void HeadTracking::initGoogleCardBoard(){

}

void HeadTracking::getHeadOrientationQuaternion(double* x, double* y, double* z, double* w){
#ifdef ANDROID
  // is CallDoubleMethodA    A = array ????????????      DOES NOT COMPILE, SO I COMMENTED THIS OUT FOR NOW
  //double* returnedQuaternion = env->CallDoubleMethodA(zeissVRoneActivity, zeissVRoneMethodID);
  //*x = returnedQuaternion[0];
  //*y = returnedQuaternion[1];
  //*z = returnedQuaternion[2];
  //*w = returnedQuaternion[3];
#endif
}
