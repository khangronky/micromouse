#include <Arduino.h>
#include <InfraredSensor.h>
#include <Motor.h>

int sensorPin = A0;
int sensorValue = 0;
float threshold = 5;

InfraredSensor irSensor(sensorPin);

int IN1 = 2;
int IN2 = 4;
int IN3 = 7;
int IN4 = 8;
int ENA = 9;
int ENB = 10;

Motor motorA(IN1, IN2, ENA);
Motor motorB(IN3, IN4, ENB);

float convertToCM(int sensorValue) {
  float cm = (sensorValue / 45.0) * 5.0;
  return cm;
}

void setup() {
  Serial.begin(9600);
  irSensor.begin();
  motorA.begin();
  motorB.begin();
}

void loop() {
  sensorValue = irSensor.getValue();

  float distance = convertToCM(sensorValue);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance >= threshold) {
    motorA.action(255);
    motorB.action(255);
    Serial.print("Object detected at ");
    Serial.print(distance);
    Serial.println(" cm.");
  } else {
    motorA.action(0);
    motorB.action(0);
    Serial.println("No object detected.");
  }

  delay(500);
}