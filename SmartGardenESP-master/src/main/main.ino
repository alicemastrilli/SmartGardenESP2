#include <cstring>
#include "config.h"
#include "MonitoringTask.h"
#include "Task.h"


String ssid = "";
String password = "";
String serviceURI = "";
Task* monitoringTask;
void readWifi()
{
  Serial.println("Enter SSID: ");  
  while(Serial.available() == 0) {     
  } 
  ssid  = Serial.readString();
  ssid = ssid.substring(0, ssid.length() - 1);
  Serial.println("Enter password: ");  
  while(Serial.available() == 0) {     
  } 
  password  = Serial.readString();
  password = password.substring(0, password.length() - 1);
}

void readUrl(){
  Serial.println("Enter url: ");  
  while(Serial.available() == 0) {     
  } 
  serviceURI  = Serial.readString();
  serviceURI = serviceURI.substring(0, serviceURI.length() - 1);
}

void setup() {
  Serial.begin(115200); 
  
  readWifi();
  Serial.println("ssid: " + ssid);
  Serial.println("password: " + password);
  readUrl();
  Serial.println("Service URI: " + serviceURI);
  
  monitoringTask = new MonitoringTask(serviceURI, &ssid, &password);

}

void loop() {
  monitoringTask->tick();
  delay(500);
}
