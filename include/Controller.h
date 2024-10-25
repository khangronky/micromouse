#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller {

public:
    static void begin();
    static void action(char command);
    static String action(String command);
};

#endif