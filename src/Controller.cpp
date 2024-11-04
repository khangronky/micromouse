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
        motorA.action(150);
        motorB.action(138);
        Serial.println("Action: F - Motor A forward, Motor B forward");
    } else if (command == 'E') {
        motorA.action(127);
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
        motorA.action(140);
        motorB.action(-170);
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
    manualAction('F'); // Move forward one cell is 20cm
    delay(430);       // Cell 

    manualAction('R'); // Turn left
    delay(250 );        // 
    manualAction('F'); // Move forward
    delay(430);       
    manualAction('L'); // Turn right
    delay(250);        
    manualAction('F'); // Move forward
    delay(430);       
    manualAction('L'); // Stop
    delay(250);
    manualAction('S'); // Move forward
    Serial.println("Automation test run completed.");
}


bool Controller::isObstacleFront() {
    long distance = ultrasonicSensor.getDistance();
    Serial.print("Front distance: ");
    Serial.println(distance);
    return distance < ultrasonicThresholdCm;
}

bool Controller::isObstacleLeft() {
    int value = irSensorA.read();
    Serial.print("Left sensor value: ");
    Serial.println(value);
    return value < infraredThreshold;
}

bool Controller::isObstacleRight() {
    int value = irSensorB.read();
    Serial.print("Right sensor value: ");
    Serial.println(value);
    return value < infraredThreshold;
}

void Controller::automationTestRun15 () {
    delay(2000); // Delay for 2 second

    // Example sequence of commands for automation test run
    manualAction('F'); // Move forward one cell is 20cm
    delay(410); 

    manualAction('S'); // Stop
    delay(250 );

    manualAction('F'); // Move forward one cell is 20cm
    delay(410); 

    manualAction('S'); // Stop
    delay(250 );

    manualAction('R'); // Turn right
    delay(210);

    manualAction('F'); // Move forward one cell is 20cm
    delay(410); 
        
    manualAction('S'); // Stop
    delay(250);

    manualAction('F'); // Move forward
    delay(410);

    manualAction('S'); // Stop
    delay(250 );

    manualAction('R'); // Turn right
    delay(210);
            
    manualAction('F'); // Move forward
    delay(410);

    manualAction('S'); // Stop
    delay(250 );

    manualAction('R'); // turn right
    delay(210);

    manualAction('F'); // Move forward
    delay(410); 
    manualAction('S'); // Turn left
}

void Controller::automationTest18() { //Threshold Distance Check
    Serial.println("Starting automation test run with wall-right method...");

    while (true) {
        bool frontObstacle = isObstacleFront();
        bool leftObstacle = isObstacleLeft();
        bool rightObstacle = isObstacleRight();

        if (!frontObstacle && !leftObstacle && !rightObstacle) {
            manualAction('S'); // Stop
            delay(200); // Delay between sensor reads
            manualAction('R'); // Turn right
            delay(220);        // Adjusted delay for 90-degree turn
            manualAction('F'); // Move forward one cell
            delay(420);        // Calibrated delay for moving forward one cell (20 cm)
        } else if (!frontObstacle && !rightObstacle && leftObstacle) {
            manualAction('S'); // Stop
            delay(1000);        // Calibrated delay for moving forward one cell (20 cm)
            break;
        } else if (!frontObstacle && !leftObstacle && rightObstacle) {
            manualAction('S'); // Stop
            delay(1000);
            break;         // Calibrated delay for moving forward one cell (20 cm)
        } else if (frontObstacle && !leftObstacle && !rightObstacle) {
           manualAction('F'); // Move forward one cell
            delay(420);
            break;
        } else if (frontObstacle && leftObstacle && rightObstacle) {
            manualAction('S'); // Stop
            delay(500);        // Delay before moving backward
            break;       // Calibrated delay for moving forward one cell (20 cm)
        } else {
            manualAction('F'); // Move forward
            delay(420);        // Calibrated delay for moving forward one cell (20 cm)
        }
        
        delay(100); // Delay between sensor reads
    }

    Serial.println("Automation test run with wall-right method completed.");
}

void Controller::automationTest2() {
    Serial.println("Starting automation test run with wall-right method...");

    while (true) {
        bool frontObstacle = isObstacleFront();
        bool leftObstacle = isObstacleLeft();
        bool rightObstacle = isObstacleRight();

        if (!frontObstacle && !leftObstacle && !rightObstacle) {
            manualAction('S'); // Stop
            delay(200); // Delay between sensor reads
            manualAction('R'); // Turn right
            delay(220);        // Adjusted delay for 90-degree turn
            manualAction('F'); // Move forward one cell
            delay(420);        // Calibrated delay for moving forward one cell (20 cm)
        } else if (!frontObstacle && !rightObstacle && leftObstacle) {
            manualAction('S'); // Stop
            delay(200);
            manualAction('R'); // Turn right
            delay(220);        // Adjusted delay for 90-degree turn
            manualAction('F'); // Move forward one cell
            delay(420);        // Calibrated delay for moving forward one cell (20 cm)
        } else if (!frontObstacle && !leftObstacle && rightObstacle) {
            manualAction('L'); // Turn left
            delay(210);        // Adjusted delay for 90-degree turn
            manualAction('F'); // Move forward one cell
            delay(420);        // Calibrated delay for moving forward one cell (20 cm)
        } else if (frontObstacle && !leftObstacle && !rightObstacle) {
            manualAction('R'); // Turn right
            delay(210);        // Adjusted delay for 90-degree turn
        } else if (frontObstacle && leftObstacle && rightObstacle) {
            manualAction('S'); // Stop
            delay(500);        // Delay before moving backward
            manualAction('B'); // Move backward
            delay(210);        // Delay for moving backward a bit
            manualAction('S'); // Stop
            delay(500);        // Delay before moving forward
            manualAction('R'); // Move forward
            delay(400);        // Calibrated delay for moving forward one cell (20 cm)
        } else {
            manualAction('F'); // Move forward
            delay(420);        // Calibrated delay for moving forward one cell (20 cm)
        }
        manualAction('S'); // Stop
        delay(200); // Delay between sensor reads
    }

    Serial.println("Automation test run with wall-right method completed.");
}

void Controller::printSensorData() {
    long frontDistance = ultrasonicSensor.getDistance();
    int leftValue = irSensorA.read();
    int rightValue = irSensorB.read();

    Serial.print("Front distance: ");
    Serial.print(frontDistance);
    Serial.println(" cm");

    Serial.print("Left sensor value: ");
    Serial.print(leftValue);
    Serial.println(" (analog)");

    Serial.print("Right sensor value: ");
    Serial.print(rightValue);
    Serial.println(" (analog)");
}