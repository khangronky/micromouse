#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "InfraredSensor.h"
#include "UltrasonicSensor.h"
#include "Motor.h"

extern int sensorPinA;
extern int sensorPinB;
extern int trigPin;
extern int echoPin;
extern int threshold;
extern int ENA;
extern int IN1;
extern int IN2;
extern int IN3;
extern int IN4;
extern int ENB;

extern Motor motorA;
extern Motor motorB;

class Controller {
public:
    void begin();
    String manualAction(char command);
    void automationTestRun();
    void automationTest2(); // Declaration of the new automation test function
    bool isObstacleFront();
    bool isObstacleLeft();
    bool isObstacleRight();
};

#endif // CONTROLLER_H