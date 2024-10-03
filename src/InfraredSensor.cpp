#include "InfraredSensor.h"

InfraredSensor::InfraredSensor(int sensorPin, int sensitivityThreshold)
    : sensorPin(sensorPin), sensitivityThreshold(sensitivityThreshold) {}

void InfraredSensor::begin() {
    pinMode(sensorPin, INPUT); // Initialize the analog input pin
}

int InfraredSensor::getDistance() {
    return analogRead(sensorPin); // Read and return the raw analog value from the sensor
}

bool InfraredSensor::isObstacleDetected() {
    int sensorValue = getDistance(); // Get the raw analog reading
    return sensorValue >= sensitivityThreshold; // Return true if value exceeds the threshold (object detected)
}
