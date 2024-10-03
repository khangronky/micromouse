#ifndef InfraredSensor_h
#define InfraredSensor_h

#include <Arduino.h>

class InfraredSensor {
public:
    InfraredSensor(int sensorPin, int sensitivityThreshold); // Constructor with pin and threshold
    void begin(); // Function to initialize the sensor pin
    bool isObstacleDetected(); // Function to check for obstacle detection based on sensitivity
    int getDistance(); // Function to return raw analog value (distance)

private:
    int sensorPin; // Variable to store sensor pin
    int sensitivityThreshold; // Variable to store sensitivity threshold
};

#endif
