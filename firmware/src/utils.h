#ifndef __UTILS_H__
#define __UTILS_H__

#include <Arduino.h>

bool __debug_mode__ = true;

void enableDebugging() {
    Serial.println("Debugging Enabled");
    __debug_mode__ = 1;
}

void disableDebugging() {
    Serial.println("Debugging Disabled");
    __debug_mode__ = 0;
}

void printLog(String msg, bool newline = true) {
    if (__debug_mode__) {
        Serial.print(msg);
        if (newline) Serial.println();
    }
}

#endif
