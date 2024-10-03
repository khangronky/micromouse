#include <InfraredSensor.h>

InfraredSensor irSensor(7);

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
    delay(500); 
}
