#include <Arduino.h>
#include <Motor.h>

Motor motor(5, 6, 7, 8, 9, 10);

void forward() {
  motor.action(255, 255);
}

void backward() {
  motor.action(-255, -255);
}

void left() {
  motor.action(255, -255);
}

void right() {
  motor.action(-255, 255);
}

void stop() {
  motor.action(0, 0);
}

void setup() {
  motor.begin();
}

void loop() {
  forward();
  delay(1000);
  backward();
  delay(1000);
  left();
  delay(1000);
  right();
  delay(1000);
  stop();
  delay(1000);
}