#ifndef __PHOTORESISTOR_IMPL__
#define __PHOTORESISTOR_IMPL__
#include "Photoresistor.h"
class PhotoresistorImpl:public Photoresistor{
    
public:
    PhotoresistorImpl(int photoResistorPin);
    int getLuminosity();
private:
    int photoResistorPin;
    int lightInit;
};

#endif