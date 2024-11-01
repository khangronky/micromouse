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

int ENA = 5;
int IN1 = 6;
int IN2 = 7;
int IN3 = 9;
int IN4 = 8;
int ENB = 10;

InfraredSensor irSensorA(sensorPinA);
InfraredSensor irSensorB(sensorPinB);
UltrasonicSensor ultrasonicSensor(trigPin, echoPin);
Motor motorA(IN1, IN2, ENA);
Motor motorB(IN3, IN4, ENB);

void Controller::begin() {
    irSensorA.begin();
    irSensorB.begin();
    ultrasonicSensor.begin();
    motorA.begin();
    motorB.begin();
}

String Controller::manualAction(char command) { // For manual control
    if (command == 'F') {
        motorA.action(255);
        motorB.action(255);
        delay(500);
        motorA.action(0);
        motorB.action(0);
        return "ack";
    }
    if (command == 'R') {
        motorA.action(255);
        motorB.action(-255);
        delay(500);
        motorA.action(0);
        motorB.action(0);
        return "ack";
    }
    if (command == 'L') {
        motorA.action(-255);
        motorB.action(255);
        delay(500);
        motorA.action(0);
        motorB.action(0);
        return "ack";
    }
    return "unknown";
}

void Controller::autoAction(char command) { // For automation
    if (command == 'F') {
        motorA.action(255);
        motorB.action(255);
        delay(500);
        motorA.action(0);
        motorB.action(0);
    }
    if (command == 'R') {
        motorA.action(255);
        motorB.action(-255);
        delay(500);
        motorA.action(0);
        motorB.action(0);
    }
    if (command == 'L') {
        motorA.action(-255);
        motorB.action(255);
        delay(500);
        motorA.action(0);
        motorB.action(0);
    }
}

bool Controller::wallFront() {
    // Implement sensor reading for front wall detection
    return false; // Placeholder
}

bool Controller::wallLeft() {
    // Implement sensor reading for left wall detection
    return false; // Placeholder
}

bool Controller::wallRight() {
    // Implement sensor reading for right wall detection
    return false; // Placeholder
}

// void Controller::begin() {
//     // Initialize motors and sensors
//     motorA.begin();
//     motorB.begin();
// }

void Controller::ackReset() {
    // Implement reset acknowledgment
    Serial.println("ackReset");
}

void Controller::moveForward() {
    autoAction('F');
}

void Controller::turnRight() {
    autoAction('R');
}

void Controller::turnLeft() {
    autoAction('L');
}