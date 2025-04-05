#ifndef FS_H
#define FS_H
#include <Arduino.h>

#define TRIG_PIN 13  
#define ECHO_PIN 12 
#define TANK_HEIGHT 9.0 
#define SOUND_SPEED 34300

void fs() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.begin(115200);
}

void fl(float* fuelLevelOut, float* fuelPercentageOut) {
    float duration, distance, fuelLevel, fuelPercentage;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration * 0.0343) / 2;  

    fuelLevel = TANK_HEIGHT - distance;
    if (fuelLevel < 0) fuelLevel = 0;
    if (fuelLevel > TANK_HEIGHT) fuelLevel = TANK_HEIGHT;
    fuelPercentage = (fuelLevel / TANK_HEIGHT) * 100;

    *fuelLevelOut = fuelLevel;
    *fuelPercentageOut = fuelPercentage;

    Serial.print("Fuel Level: ");
    Serial.print(fuelLevel);
    Serial.print(" cm | Fuel Percentage: ");
    Serial.print(fuelPercentage);
    Serial.println(" %");

    delay(1000); 
}
#endif
