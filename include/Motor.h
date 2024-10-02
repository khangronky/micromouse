#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
    Motor(int ENA, int IN1, int IN2, int IN3, int IN4, int ENB);
    void begin();
    void action(int speedA, int speedB);

private:
    int ENA, IN1, IN2, IN3, IN4, ENB;
};

#endif