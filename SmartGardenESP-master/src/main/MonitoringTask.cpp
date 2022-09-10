#include <WiFi.h>
#include <HTTPClient.h>
#include <iostream>
#include <cstring>
#include "MonitoringTask.h"
#include "Arduino.h"
#include "config.h"
#include "Led.h"
#include "PhotoresistorImpl.h"
#include "TempSensorLM35.h"

MonitoringTask::MonitoringTask(String serviceURI, const String* ssid, const String* password){
    this->serviceURI = serviceURI;
    this->ssid = (char*) ssid->c_str();
    this->password = (char*) password->c_str();
  
  this-> temp = 0;
  this-> lum = 0;
  this->state = CONNECTING_WIFI;
  this->led = new Led(LED_PIN);
  this->photoresistor = new PhotoresistorImpl(PHOTORESISTOR_PIN);
  this->tempSensor = new TempSensorLM35(TEMPSENSOR_PIN); 

}

void MonitoringTask::connectToWifi(){
  WiFi.begin(this->ssid, this->password);
  Serial.print("Connecting to ");
  Serial.println(this->ssid);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("*");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

int MonitoringTask::sendData(){  
   HTTPClient http;    
   http.begin(this->serviceURI + "/api/inputData");      
   http.addHeader("Content-Type", "application/json");    
    
   String msg = 
    String("{ \"temp\": ") + this->temp + 
    String(",\"lum\":") + this->lum +
    String (" }");
   Serial.print(msg);
   int retCode = http.POST(msg);   
   http.end();  
   return retCode;
}

String MonitoringTask::readData(){  
  HTTPClient http;
  String payload;
  String servicePath = this->serviceURI + "/api/gardenState";
  http.begin(servicePath);
      
    // Send HTTP GET request
    int httpResponseCode = http.GET();
      
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      payload= "Error";
    }
    http.end();
    return payload;
}

void MonitoringTask::tick()
{
switch (state) {

    case CONNECTING_WIFI:
    this->connectToWifi();
    this->state = READING;
    break;

    case READING:
      this->led->switchOn();
      this->lum = this->photoresistor->getLuminosity();
      this->temp = (int)this->tempSensor->getTemperature();
      Serial.print("Luminosity: ");
      Serial.println(this->lum);
      Serial.print("Temperature: ");
      Serial.println(this->temp); 
      this->state = SENDING;
    break;
   
    case SENDING:
    if (WiFi.status()== WL_CONNECTED){        
      int code = this->sendData();
      if (code == 200){
        Serial.println("ok");   
      } else {
        Serial.println(String("error: ") + code);
      }
    } else {
      Serial.println("WiFi Disconnected... Reconnect.");
      this->state = CONNECTING_WIFI;
    }
    delay(5000);
    this->state = CHECK_STATE;
    break;

    case CHECK_STATE:  
    if(WiFi.status() == WL_CONNECTED){  
          String gardenState = this->readData();
          if ( gardenState == "ALARM"){
            this->state = ALARM;
          } else if( gardenState == "Error") {
            Serial.println("Errore ricezione dello stato dal service");
          } else {
            this-> state = READING;
          }
         } else {
         Serial.println("WiFi Disconnected... Reconnect.");
         this->state = CONNECTING_WIFI;
        }
      break;

    case ALARM:
      led->switchOn(); 
      this->state = CHECK_STATE;
    break;
  }

}
