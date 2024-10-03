#include <InfraredSensor.h>

InfraredSensor::InfraredSensor(int sensorPin, int sensitivityThreshold)
    : sensorPin(sensorPin), limit(sensitivityThreshold) {}

void InfraredSensor::begin() {
    pinMode(sensorPin, INPUT); // Initialize the analog input pin
}

bool InfraredSensor::isDetected() {
   
    int sensorValue = getDistance(); // Get the raw analog reading
    return sensorValue >= limit;
}

int InfraredSensor::getDistance(){
    return digitalRead(sensorPin);
}