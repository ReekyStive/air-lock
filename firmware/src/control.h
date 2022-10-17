#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <Arduino.h>
#include <Servo.h>

#include "melodies.h"
#include "utils.h"

const int servoPin = 6;
Servo myServo;

int minAngle = 0;
int maxAngle = 115;
int curAngle = minAngle;
int defaultDelay = 20;

void initServo() {
    playMelody(START_INIT);
    myServo.attach(servoPin);
    delay(100);
    curAngle = minAngle;
    myServo.write(minAngle);
    delay(3000);
    myServo.detach();
    delay(100);
    playMelody(INIT_DONE);
}

void setAngle(int tarAngle, int servoDelay = defaultDelay,
              bool deattachOrNot = true) {
    if (tarAngle < minAngle) tarAngle = minAngle;
    if (tarAngle > maxAngle) tarAngle = maxAngle;
    if (tarAngle == curAngle) return;

    myServo.attach(servoPin);
    if (tarAngle > curAngle) {
        printLog("Setting angle to ", false);
        printLog(String(tarAngle));
        for (int i = curAngle; i <= tarAngle; i++) {
            myServo.write(i);
            delay(servoDelay);
        }
        printLog("Angle set");
    } else {
        printLog("Setting angle to ", false);
        printLog(String(tarAngle));
        for (int i = curAngle; i >= tarAngle; i--) {
            myServo.write(i);
            delay(servoDelay);
        }
        printLog("Angle set");
    }
    curAngle = tarAngle;

    if (deattachOrNot) myServo.detach();
}

void openLock() { setAngle(maxAngle, defaultDelay, false); }

void closeLock() { setAngle(minAngle, (int)defaultDelay / 2, true); }

void openAndClose() {
    printLog("OpenAndClose");
    playMelody(OPEN);

    printLog("Opening");
    openLock();

    printLog("Opened");
    playMelody(OPEN_DONE);
    delay(2000);

    printLog("Closing");
    closeLock();
    printLog("Closed");
}

#endif
