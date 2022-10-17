#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "password.h"
#include "utils.h"

int btTx = 2, btRx = 3;
SoftwareSerial btSerial(btTx, btRx);

void clearSerialBuffer() {
    while (Serial.available()) {
        Serial.read();
    }
}

String readBtMessage() {
    String msg;
    while (btSerial.available()) {
        char c = (char)btSerial.read();
        if (c == '\n') break;
        msg += c;
        if (!btSerial.available()) delay(50);
    }
    return msg;
}

void sendBtMessage(String msg) { btSerial.println(msg); }

#endif
