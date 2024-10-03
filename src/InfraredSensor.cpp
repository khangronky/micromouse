#include <InfraredSensor.h>

InfraredSensor::InfraredSensor(int sensorPin) 
    : sensorPin(sensorPin) {}

void InfraredSensor::begin() {
    pinMode(sensorPin, INPUT);
}

bool InfraredSensor::isDetected() {
    int sensorValue = digitalRead(sensorPin); 
    return sensorValue == LOW; 
}
