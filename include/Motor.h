#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
    Motor(int IN1, int IN2, int EN);
    void begin();
    void action(int speed);

private:
    int IN1, IN2, EN;
};

#endif