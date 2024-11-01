#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller {

public:
    static void begin();
    static String manualAction(char command); // For manual control
    static void autoAction(char command); // For automation
    static bool wallFront();
    static bool wallLeft();
    static bool wallRight();
    static void ackReset();
    static void moveForward();
    static void turnRight();
    static void turnLeft();
};

#endif