#ifndef InfraredSensor_h
#define InfraredSensor_h

#include <Arduino.h>

class InfraredSensor {
public:
    InfraredSensor(int sensorPin, int limit); // Constructor with sensor pin initialization
    void begin(); // Function to initialize the sensor pin
    bool isDetected(); 
    int getDistance();

private:
    int sensorPin; // Variable to store sensor pin
    int limit;
};

#endif
