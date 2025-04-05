#ifndef VIBRATION_SENSOR_H
#define VIBRATION_SENSOR_H
#include <Arduino.h>
#include <Wire.h>

float maxval = 0.0;
float prev = 0.0;

void vss() {
    Serial.begin(115200);
    Wire.begin();
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission();
}

void vsl(float* vibrationOut, float* maxVibrationOut) {
    int16_t ax, ay, az;
    
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 6, true);

    ax = Wire.read() << 8 | Wire.read();
    ay = Wire.read() << 8 | Wire.read();
    az = Wire.read() << 8 | Wire.read();

    float accelX = ax / 16384.0;
    float accelY = ay / 16384.0;
    float accelZ = az / 16384.0;

    float vibration = abs(sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ) - 1.0);
    prev = vibration;

    if (prev > maxval) {
        maxval = prev;
    }

    *vibrationOut = vibration;
    *maxVibrationOut = maxval;

    delay(100);
}

#endif
