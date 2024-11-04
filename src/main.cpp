#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "controller.h"
#include "motor.h" // Assuming motor.h defines the Motor class

// Pin definitions
int sensorPinA = A0; // Infrared sensor left
int sensorPinB = A1; // Infrared sensor right
int trigPin = 3;     // Ultrasonic sensor trigger
int echoPin = 11;    // Ultrasonic sensor echo

int ultrasonicThresholdCm = 3;  // Ultrasonic threshold in centimeters
int infraredThreshold = 120;     // Infrared threshold (analog value)

int ENA = 5; // Motor A speed control
int IN1 = 6; // Motor A direction control
int IN2 = 7; // Motor A direction control
int IN3 = 9; // Motor B direction control
int IN4 = 8; // Motor B direction control
int ENB = 10; // Motor B speed control

SoftwareSerial bluetooth(2, 3); // RX, TX for Bluetooth module

// Motor instances
Motor motorA(IN1, IN2, ENA);
Motor motorB(IN3, IN4, ENB);

// Controller instance
Controller controller;

void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);

    // Initialize controller
    controller.begin();

    // Ensure motors are stopped initially
    motorA.action(0);
    motorB.action(0);

    // controller.automationTestRun15();

    // controller.printSensorData();
    
    controller.automationTest18();
}

void processCommand(char command) {
    Serial.print("Received command: ");
    Serial.println(command);
    controller.manualAction(command);
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        processCommand(command);
    }

    
}