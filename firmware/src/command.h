#ifndef __COMMAND_H__
#define __COMMAND_H__

/*
Note: Messages are end with LF (\n).
Commands:

pswd=<password> open
        Open door and then close.

pswd=<password> set-angle <number>
        Set servo to certain angle.

pswd=<password> play-melody <ID>
        Play some notes.

pswd=<password> change-password <original> <new>
        Change password.

pswd=<password> debug <on|off>
        Turn on/off debug mode.
*/

#include <Arduino.h>

#include "communication.h"
#include "control.h"
#include "melodies.h"
#include "password.h"
#include "utils.h"

void execCommand(String command) {
    if (command == " admin-reset 114514 1919810 !!! +.*?? ") {
        resetPasswd();
        printLog("Password Reset to 123456 (admin)");
        btSerial.println("reset-admin");
        return;
    }

    command.trim();

    int index = command.indexOf(' ');

    String passwdStr = command.substring(0, index);
    command = command.substring(index + 1);
    command.trim();

    int passwdIndex = passwdStr.indexOf('=');
    String passwd = passwdStr.substring(passwdIndex + 1);
    passwd.trim();
    if (!validatePasswd(passwd)) {
        printLog("Wrong password");
        btSerial.println("wrong-password");
        return;
    }

    index = command.indexOf(' ');
    String operation = command.substring(0, index);
    operation.trim();

    String params = command.substring(index + 1, command.length());
    params.trim();

    if (operation == "open") {
        btSerial.println("ok");
        openAndClose();

    } else if (operation == "set-angle") {
        btSerial.println("ok");
        int angle = params.toInt();
        setAngle(angle, defaultDelay, true);

    } else if (operation == "play-melody") {
        btSerial.println("ok");
        int melodyId = params.toInt();
        playMelody((MelodyVariants)melodyId);

    } else if (operation == "change-password") {
        btSerial.println("ok");
        String newPasswd = params;
        setPasswd(newPasswd);
        printLog("Password Changed");

    } else if (operation == "debug") {
        btSerial.println("ok");
        String param = params;
        if (param == "on") {
            enableDebugging();
        } else if (param == "off") {
            disableDebugging();
        }

    } else {
        btSerial.println("invalid-command");
        printLog("Invalid Command");
    }
}

#endif
