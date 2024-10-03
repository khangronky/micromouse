#ifndef InfraredSensor_h
#define InfraredSensor_h

#include <Arduino.h>

class InfraredSensor {
public:
    InfraredSensor(int sensorPin); // Constructor with sensor pin initialization
    void begin(); // Function to initialize the sensor pin
    bool isDetected(); 

private:
    int sensorPin; // Variable to store sensor pin
};

#endif
