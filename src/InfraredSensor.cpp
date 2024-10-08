#include "InfraredSensor.h"

InfraredSensor::InfraredSensor(int sensorPin)
    : sensorPin(sensorPin) {}

void InfraredSensor::begin() {
    pinMode(sensorPin, INPUT);
}

int InfraredSensor::getValue() {
    sensorValue = analogRead(sensorPin);
    return sensorValue;
}