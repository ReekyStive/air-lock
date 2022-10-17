#ifndef __PASSWORD_H__
#define __PASSWORD_H__

#include <Arduino.h>
#include <EEPROM.h>

const int passwdLen = 6;
String passwdFromRom = "xxxxxx";

void readPasswdFromRom() {
    for (int i = 0; i < passwdLen; i++) {
        passwdFromRom[i] = (char)EEPROM.read(i) + '0';
    }
}

void setPasswd(String passwd) {
    if (passwd.length() != 6) {
        Serial.println("Invalid Password Length");
        return;
    }
    for (int i = 0; i < passwdLen; i++) {
        EEPROM.write(i, (byte)(passwd[i] - '0'));
    }
    passwdFromRom = passwd;
}

void resetPasswd() { setPasswd(String("123456")); }

int validatePasswd(String received) {
    if (received.length() != passwdLen) {
        Serial.println("Invalid Password Length");
        return false;
    }

    for (int i = 0; i < passwdLen; i++) {
        if (received[i] != passwdFromRom[i]) {
            return false;
        }
    }
    return true;
}

#endif
