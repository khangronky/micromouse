#include "InfraredSensor.h"

InfraredSensor irSensor(5);

void setup() {
    Serial.begin(9600);
    irSensor.begin();
}

void loop() {
    int distance = irSensor.getValue();
    Serial.print("Distance reading: ");
    Serial.println(distance); // Print the raw analog value (for monitoring)

    delay(500); // Delay to avoid flooding the serial monitor
}
