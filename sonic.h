#ifndef SONIC_H
#define SONIC_H
#include <Arduino.h>

const int echo = 2;
const int trig = 15;
const float speed = 0.034;
int prevDistance = 0;
int motionThreshold = 5;

void ss() {
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);
    Serial.begin(115200);
}

void sl(float* distanceOut, bool* motionOut) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    float duration = pulseIn(echo, HIGH);
    float distance = (duration * speed) / 2;

    bool withinRange = (distance >= 10 && distance <= 100);
    bool motionDetected = withinRange && (abs(distance - prevDistance) > motionThreshold);

    prevDistance = distance;

    // Output values via pointer arguments
    *distanceOut = distance;
    *motionOut = motionDetected;

    delay(100);
}

#endif
