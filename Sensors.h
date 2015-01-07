#ifndef _SENSORS_H
#define _SENSORS_H


#include <iostream>
//#include "Font.h"

#ifdef ANDROID
  #include <android/sensor.h>
#endif

using namespace std;

class Sensors {
	public:
    Sensors();
    ~Sensors();

    static void checkSensors(float* accelX, float* accelY, float* accelZ);

  private:
#ifdef ANDROID
    /*
    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    struct saved_state state;
    */
#endif

};



#endif
