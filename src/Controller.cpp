#include "controller.h"

// Sensor and motor instances
InfraredSensor irSensorA(sensorPinA);
InfraredSensor irSensorB(sensorPinB);
UltrasonicSensor ultrasonicSensor(trigPin, echoPin);

void Controller::begin() {
    irSensorA.begin();
    irSensorB.begin();
    ultrasonicSensor.begin();
    motorA.begin();
    motorB.begin();
}

String Controller::manualAction(char command) { // For manual control
    Serial.print("Controller action received command: ");
    Serial.println(command);

    if (command == 'Q') {
        motorA.action(0);
        motorB.action(150); // Motor B forward
        Serial.println("Action: Q - Motor A stop, Motor B forward");
    } else if (command == 'F') {
        motorA.action(147);
        motorB.action(150);
        Serial.println("Action: F - Motor A forward, Motor B forward");
    } else if (command == 'E') {
        motorA.action(147);
        motorB.action(0);
        Serial.println("Action: E - Motor A forward, Motor B stop");
    } else if (command == 'L') {
        motorA.action(-147);
        motorB.action(150);
        Serial.println("Action: L - Motor A backward, Motor B forward");
    } else if (command == 'S') {
        motorA.action(0);
        motorB.action(0);
        Serial.println("Action: S - Motor A stop, Motor B stop");
    } else if (command == 'R') {
        motorA.action(170);
        motorB.action(-150);
        Serial.println("Action: R - Motor A forward, Motor B backward");
    } else if (command == 'Z') {
        motorA.action(0);
        motorB.action(-150);
        Serial.println("Action: Z - Motor A stop, Motor B backward");
    } else if (command == 'B') {
        motorA.action(-147);
        motorB.action(-150);
        Serial.println("Action: B - Motor A backward, Motor B backward");
    } else if (command == 'C') {
        motorA.action(-147);
        motorB.action(0);
        Serial.println("Action: C - Motor A backward, Motor B stop");
    } else {
        Serial.println("Unknown command");
    }
    return "Command executed";
}

void Controller::automationTestRun() {
    Serial.println("Starting automation test run...");
    delay(2000); // Delay for 2 second

    // Example sequence of commands for automation test run
    manualAction('F'); // Move forward
    delay(1000);       // Delay for 1 second
    manualAction('R'); // Turn left
    delay(250 );        // Delay for 0.5 seconds
    manualAction('F'); // Move forward
    delay(700);       // Delay for 1 second
    manualAction('R'); // Turn right
    delay(250);        // Delay for 0.5 seconds
    manualAction('F'); // Move forward
    delay(500);       // Delay for 1 second
    manualAction('S'); // Stop

    Serial.println("Automation test run completed.");
}