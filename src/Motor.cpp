#include "Motor.h"

Motor::Motor(int ENA, int IN1, int IN2, int IN3, int IN4, int ENB)
    : ENA(ENA), IN1(IN1), IN2(IN2), IN3(IN3), IN4(IN4), ENB(ENB) {}

void Motor::begin() {
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);
}

void Motor::action(int speedA, int speedB) {
    if (speedA > 0) {
        analogWrite(ENA, speedA);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    } else if (speedA < 0) {
        analogWrite(ENA, -speedA);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    } else {
        analogWrite(ENA, 0);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
    }

    if (speedB > 0) {
        analogWrite(ENB, speedB);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    } else if (speedB < 0) {
        analogWrite(ENB, -speedB);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    } else {
        analogWrite(ENB, 0);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
    }
}