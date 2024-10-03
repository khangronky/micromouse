#include <Arduino.h>
#include <UltrasonicSensor.h>

UltrasonicSensor us1(A0, A1);
UltrasonicSensor us2(A4, A5);

void setup() {
    Serial.begin(9600);
    us1.begin();
    us2.begin();
}

void loop() {
    double distance1 = us1.getDistance();
    double distance2 = us2.getDistance();
    Serial.println("Distance 1: " + String(distance1) + " cm");
    Serial.println("Distance 2: " + String(distance2) + " cm");
    delay(1000);
}