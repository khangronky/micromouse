#include <Arduino.h>
#include "InfraredSensor.h"
#include "UltrasonicSensor.h"
#include "Motor.h"

#include "Controller.h"

int sensorPinA = A0;
int sensorPinB = A1;

int trigPin = 3;
int echoPin = 11;

int threshold = 5;

int ENA = 10;
int IN1 = 9;
int IN2 = 8;
int IN3 = 7;
int IN4 = 6;
int ENB = 5;

InfraredSensor irSensorA(sensorPinA);
InfraredSensor irSensorB(sensorPinB);
UltrasonicSensor ultrasonicSensor(trigPin, echoPin);
Motor motorA(IN1, IN2, ENA);
Motor motorB(IN3, IN4, ENB);

void Controller::begin() {
    Serial.begin(9600);
    irSensorA.begin();
    irSensorB.begin();
    ultrasonicSensor.begin();
    motorA.begin();
    motorB.begin();
}

String Controller::action(String command) {
    if (command == "moveForward") {
        motorA.action(255);
        motorB.action(255);
        delay(500);
        motorA.action(0);
        motorB.action(0);
        return "ack";
    }
    if (command == "turnRight") {
        motorA.action(255);
        motorB.action(-255);
        delay(500);
        motorA.action(0);
        motorB.action(0);
        return "ack";
    }
    if (command == "turnLeft") {
        motorA.action(-255);
        motorB.action(255);
        delay(500);
        motorA.action(0);
        motorB.action(0);
        return "ack";
    }

    if (command == "wallFront") {
        float ultrasonicDistance = ultrasonicSensor.getDistance();
        if (ultrasonicDistance < threshold) return "true";
        else return "false";
    }
    if (command == "wallRight") {
        int irSensorBValue = irSensorB.getValue();
        if (irSensorBValue < threshold) return "true";
        else return "false";
    }
    if (command == "wallLeft") {
        int irSensorAValue = irSensorA.getValue();
        if (irSensorAValue < threshold) return "true";
        else return "false";
    }
    return "undefined";
}