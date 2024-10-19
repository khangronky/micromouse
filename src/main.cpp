#include <Arduino.h>
#include <InfraredSensor.h>
#include <UltrasonicSensor.h>
#include <Motor.h>

int sensorPinA = A0;
int sensorPinB = A1;

int trigPin = 3;
int echoPin = 11;

int threshold = 5;

int ENA = 10;
int IN1 = 9;
int IN2 = 8;
int IN3 = 7;
int IN4 = 6;
int ENB = 5;

InfraredSensor irSensorA(sensorPinA);
InfraredSensor irSensorB(sensorPinB);
UltrasonicSensor ultrasonicSensor(trigPin, echoPin);
Motor motorA(IN1, IN2, ENA);
Motor motorB(IN3, IN4, ENB);

void setup() {
  Serial.begin(9600);
  irSensorA.begin();
  irSensorB.begin();
  ultrasonicSensor.begin();
  motorA.begin();
  motorB.begin();
}

void loop() {
  int irValueA = irSensorA.getValue();
  float irDistanceA = (irValueA / 45.0) * 5.0;
  Serial.print("Infrared A distance: ");
  Serial.print(irDistanceA);
  Serial.println(" cm");

  int irValueB = irSensorB.getValue();
  float irDistanceB = (irValueB / 45.0) * 5.0;
  Serial.print("Infrared B distance: ");
  Serial.print(irDistanceB);
  Serial.println(" cm");

  float ultrasonicDistance = ultrasonicSensor.getDistance();
  Serial.print("Ultrasonic distance: ");
  Serial.print(ultrasonicDistance);
  Serial.println(" cm");

  bool hasFrontWall = ultrasonicDistance < threshold;
  bool hasLeftWall = irDistanceB < threshold;
  bool hasRightWall = irDistanceA < threshold;

  if (!hasFrontWall && hasLeftWall && hasRightWall) {
    // Move forward
    motorA.action(255);
    motorB.action(255);
    delay(500);
  }
  if (hasFrontWall && !hasLeftWall && hasRightWall) {
    // Turn left
    motorA.action(-255);
    motorB.action(255);
    delay(500);
  }
  if (hasFrontWall && hasLeftWall && !hasRightWall) {
    // Turn right
    motorA.action(255);
    motorB.action(-255);
    delay(500);
  }
  if (hasFrontWall && hasLeftWall && hasRightWall) {
    // Turn back (right)
    motorA.action(255);
    motorB.action(-255);
    delay(1000);
  }
  delay(500); //for serial monitor speed supervision
}