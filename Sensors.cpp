#include "Sensors.h"

#ifdef ANDROID
  #include <android/log.h>
  #include "../SDL/src/core/android/SDL_android.h"

  #ifndef LOG_TAG
    #define  LOG_TAG    "org.ivci.qwrt"
  #endif
  #ifndef LOGI
    #define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
  #endif
#endif

Sensors::Sensors(){
#ifdef ANDROID
  /*
  sensorManager = ASensorManager_getInstance();
  accelerometerSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
  sensorEventQueue = ASensorManager_createEventQueue(sensorManager, state->looper, LOOPER_ID_USER, NULL, NULL);

  if (accelerometerSensor != NULL) {
    ASensorEventQueue_enableSensor(sensorEventQueue, accelerometerSensor);

    // We'd like to get 120 events per second (in us).
    ASensorEventQueue_setEventRate(sensorEventQueue, accelerometerSensor, (1000L/120)*1000);
  }
  */
#endif
}

void Sensors::checkSensors(float* accelX, float* accelY, float* accelZ){
#ifdef ANDROID
  float accelValues[3];
  while(1){
    bool hasNewValues = Android_JNI_GetAccelerometerValues(accelValues);
    if(!hasNewValues)
      break;
  }

  *accelX = accelValues[0];
  *accelY = accelValues[1];
  *accelZ = accelValues[2];

  /*
  int ident;
  int events;

  struct android_poll_source* source;

  while(ident = ALooper_pollAll(-1, NULL, &events, (void**)&source)) >= 0) {
    // If a sensor has data, process it now.
    if (ident == LOOPER_ID_USER) {
      if(accelerometerSensor != NULL) {
        ASensorEvent event;
        while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {
          LOGI("accelerometer: x=%f y=%f z=%f", event.acceleration.x, event.acceleration.y, event.acceleration.z);
        }
      }
    }
  }
  */
#endif


}
