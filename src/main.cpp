#include <InfraredSensor.h>

InfraredSensor irSensor(A0); // Pin A0 for the infrared sensor (analog pin)

void setup() {
    Serial.begin(9600);
    irSensor.begin();
}

void loop() {
    int distance = irSensor.getDistance(); // Get the analog distance value
    Serial.print("Distance reading: ");
    Serial.println(distance); // Print the distance value to the Serial Monitor
    delay(500); // Add delay to avoid flooding the serial monitor
}
