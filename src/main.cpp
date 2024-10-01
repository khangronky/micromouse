#include <Arduino.h>

int trigPin = A0; // Define trigPin as A0
int echoPin = A1; // Define echoPin as A1

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Set trigPin as OUTPUT
  pinMode(echoPin, INPUT);  // Set echoPin as INPUT
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  double duration = pulseIn(echoPin, HIGH);
  double distance = (duration * 0.0343) / 2;
  Serial.println(distance);
  delay(500);
}