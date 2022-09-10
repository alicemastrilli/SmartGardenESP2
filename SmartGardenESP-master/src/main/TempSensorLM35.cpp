#include "TempSensorLM35.h"
#include "Arduino.h"
#define VALUES_RANGE 5
#define VCC 3.3

TempSensorLM35::TempSensorLM35(int p) : pin(p){
} 
  
float TempSensorLM35::getTemperature(){
    int16_t adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
  //int16_t adc0; // 16 bit interger to store output of analog channel zero

 // read ANO values
    float temp = (adcVal * 0.1875)/1000; 
    temp = temp * 100; 

  // print the temperature in the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(temp);   // print the temperature in °C
  Serial.print("°C");
  
  Serial.println("Temperature value in celsius: " + String(valueInCelsius) + "°");

  //ritorna un valore mappato su 5 valori
  float valueMapped = map(adcVal, 0, 4095, 0, VALUES_RANGE);
  return valueMapped;
}
