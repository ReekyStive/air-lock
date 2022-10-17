#include <Arduino.h>
#include <SoftwareSerial.h>

#include "command.h"
#include "communication.h"
#include "control.h"
#include "firstrun.h"
#include "melodies.h"
#include "utils.h"

const int touchPin = 7;
const int ledPin = 13;

bool touchPressed = false;

void setup() {
    if (isFirstRun()) {
        resetPasswd();
        flagFirstRun();
    }

    readPasswdFromRom();

    Serial.begin(9600);
    btSerial.begin(9600);

    Serial.println(passwdFromRom);

    pinMode(ledPin, OUTPUT);
    pinMode(touchPin, INPUT);
    pinMode(tonePin, OUTPUT);
    pinMode(btTx, INPUT);
    pinMode(btRx, OUTPUT);
    pinMode(servoPin, OUTPUT);
    digitalWrite(tonePin, HIGH);

    Serial.println("Initing Servo Angle");
    initServo();
    Serial.println("Init Successful");
}

void loop() {
    if (Serial.available()) {
        clearSerialBuffer();
    }

    bool newTouchPressed = digitalRead(touchPin);
    if (newTouchPressed != touchPressed) {
        touchPressed = newTouchPressed;
        if (touchPressed) {
            Serial.println("Touch Pressed");
            playMelody(OPEN);
            openLock();
            playMelody(OPEN_DONE);
            while (digitalRead(touchPin)) {
                delay(50);
            }
            touchPressed = false;
            printLog("Touch Released");
            delay(2000);
            closeLock();
        }
    }

    if (btSerial.available()) {
        String msg = readBtMessage();
        printLog("Received From BT Serial: " + msg);
        execCommand(msg);
    }
}
