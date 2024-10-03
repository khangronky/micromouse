#include <InfraredSensor.h>

InfraredSensor irSensor(7, 500);

void setup() {
    Serial.begin(9600);
    irSensor.begin();
}

void loop() {
    if (irSensor.isDetected()) {
        Serial.println("Obstacle detected!");
    } else {
        Serial.println("No obstacle.");
    }
      int distance = irSensor.getDistance();
    Serial.print("Distance reading: ");
    Serial.println(distance); // Print the raw analog value (for monitoring)

    delay(500); // Delay to avoid flooding the serial monitor
}
