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
extern int ultrasonicThresholdCm; // Ultrasonic threshold in centimeters
extern int infraredThreshold;     // Infrared threshold (analog value)
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
    void automationTestRun15();
    void automationTest18();
    void automationTest2(); 
    bool isObstacleFront();
    bool isObstacleLeft();
    bool isObstacleRight();
    void printSensorData(); // Declaration of the function to print sensor data
    void automationTest3(); // Automation journey cell by cell
};

#endif // CONTROLLER_H