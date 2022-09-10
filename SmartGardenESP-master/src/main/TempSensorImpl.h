
#ifndef __TEMP_SENSOR_IMPL__
#define __TEMP_SENSOR_IMPL__
#include "TempSensor.h"

class TempSensorLM35: public TempSensor {

public:
  TempSensorLM35(int pin);	
  virtual float getTemperature();
  
private:
  int pin;
};


#endif
