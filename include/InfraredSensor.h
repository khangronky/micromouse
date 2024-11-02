#ifndef InfraredSensor_H
#define InfraredSensor_H
#include <Arduino.h>

class InfraredSensor {
public:
    InfraredSensor(int sensorPin);
    void begin();
    int read();

private:
    int pin;
};

#endif
