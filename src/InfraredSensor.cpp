#include "InfraredSensor.h"
#include <Arduino.h>

InfraredSensor::InfraredSensor(int pin) : pin(pin) {}

void InfraredSensor::begin() {
    pinMode(pin, INPUT);
}

int InfraredSensor::read() {
    return analogRead(pin);
}