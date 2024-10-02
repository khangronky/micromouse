#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int trigPin, int echoPin);
    void begin();
    double getDistance(); // cm

private:
    int trigPin;
    int echoPin;
    const double speedOfSound = 0.0343; // cm/us
};

#endif