#include <InfraredSensor.h>

InfraredSensor::InfraredSensor(int sensorPin) 
    : sensorPin(sensorPin) {}

void InfraredSensor::begin() {
    pinMode(sensorPin, INPUT);
}

bool InfraredSensor::isObstacleDetected() {
    int sensorValue = digitalRead(sensorPin); 
    return sensorValue == LOW; 
}
