#include "InfraredSensor.h"

InfraredSensor irSensor(A0, 500); // Initialize the sensor on pin A0 with a sensitivity threshold of 500

void setup() {
    Serial.begin(9600);
    irSensor.begin();
}

void loop() {
    if (irSensor.isObstacleDetected()) {
        Serial.println("Obstacle detected!");
    } else {
        Serial.println("No obstacle.");
    }

    int distance = irSensor.getDistance();
    Serial.print("Distance reading: ");
    Serial.println(distance); // Print the raw analog value (for monitoring)

    delay(500); // Delay to avoid flooding the serial monitor
}
