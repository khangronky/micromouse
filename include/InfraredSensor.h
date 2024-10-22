#ifndef InfraredSensor_H
#define InfraredSensor_H

class InfraredSensor {
public:
    InfraredSensor(int sensorPin);
    void begin();
    int getValue();

private:
    int sensorPin, sensorValue;
};

#endif
