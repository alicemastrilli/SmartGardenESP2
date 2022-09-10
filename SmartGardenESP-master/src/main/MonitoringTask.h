#ifndef __MONITORING_TASK__
#define __MONITORING_TASK__

#include "Task.h"
#include "Led.h"
#include "PhotoresistorImpl.h"
#include "TempSensorLM35.h"

class MonitoringTask: public Task {

public:
  MonitoringTask(String serviceURI, const String* ssid, const String* password);
  void tick();
  String readData();
  int sendData();
  void connectToWifi();

private:  
 String serviceURI;

 const char* ssid;
 const char* password;
 int temp;
 int lum;
 enum {CONNECTING_WIFI, CHECK_STATE, READING, SENDING, ALARM} state;

 PhotoresistorImpl *photoresistor;
 Led *led; 
 TempSensor *tempSensor;
};

#endif
