#include <InfraredSensor.h>

InfraredSensor::InfraredSensor(int sensorPin) 
    : sensorPin(sensorPin) {}

void InfraredSensor::begin() {
    pinMode(sensorPin, INPUT); // Analog pins are automatically set to input, but it’s good practice
}

int InfraredSensor::getDistance() {
    int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor pin
    return sensorValue; // Return the raw analog value (0-1023)
}
