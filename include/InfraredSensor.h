#ifndef InfraredSensor_h
#define InfraredSensor_h

#include <Arduino.h>

class InfraredSensor {
public:
    InfraredSensor(int sensorPin);
    void begin();
    int getValue();

private:
    int sensorPin, sensorValue;
};

#endif
