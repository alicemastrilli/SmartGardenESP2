#include "PhotoresistorImpl.h"
#include "Arduino.h"
#define PHOTORESISTOR_RANGE 8
#define LIMIT_LUMONISTY_VALUE 5
PhotoresistorImpl:: PhotoresistorImpl(int photoResistorPin){
    this->photoResistorPin = photoResistorPin;
    this->lightInit = analogRead(photoResistorPin);
}

int PhotoresistorImpl::getLuminosity(){
    int valueRead = analogRead(this->photoResistorPin);
    Serial.println("Luminosity value read: " + String(valueRead));
    int valueMapped = map(valueRead, 0, 4095, 0, PHOTORESISTOR_RANGE-1);
    return valueMapped;
}
