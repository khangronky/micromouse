#include "Motor.h"

Motor::Motor(int IN1, int IN2, int EN)
    : IN1(IN1), IN2(IN2), EN(EN) {}

void Motor::begin() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(EN, OUTPUT);
}

void Motor::action(int speed) {
    if (speed > 0) {     
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(EN, speed);
    } else if (speed < 0) {      
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(EN, -speed);
    } else { 
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        analogWrite(EN, 0);
    }
}