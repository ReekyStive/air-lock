#include "melodies.h"
#include "control.h"
#include "communication.h"
#include "tools.h"

int touchPin = 7;
int ledPin = 13;

bool touch = false;

void setup()
{
    getPasswd();
    // resetPasswd();

    Serial.begin(9600);
    btSerial.begin(9600);

    pinMode(ledPin, OUTPUT);
    pinMode(touchPin, INPUT);
    pinMode(tonePin, OUTPUT);
    pinMode(btTx, INPUT);
    pinMode(btRx, OUTPUT);
    pinMode(servoPin, OUTPUT);
    digitalWrite(tonePin, HIGH);

    Serial.println("Reseting Servo");
    initServo();
    Serial.println("Init Successful");
}

void loop()
{
    bool new_touch = digitalRead(touchPin);
    if (new_touch != touch)
    {
        if (new_touch)
            console("Touched");
        else
            console("Released");
    }
    touch = new_touch;

    // touched
    if (touch)
    {
        digitalWrite(ledPin, HIGH);
        playMelody(0);
        openLock();
        playMelody(1);
        while (touch)
        {
            delay(10);
            touch = digitalRead(7);
        }
        console("Released");
        digitalWrite(ledPin, LOW);
        delay(1500);
        closeLock();
    }

    // set angle from serial
    if (Serial.available())
    {
        playMelody(5);
        String command;
        while (Serial.available())
        {
            command += char(Serial.read());
            if (!Serial.available())
                delay(10);
        }
        command.trim();
    
        int index = command.indexOf(' ');
        String operation = command.substring(0, index);
        command = command.substring(index + 1, command.length());
    
        if (operation == "debug")
        {
            String param = command;
            if (param == "on")
                debugOn();
            else if (param == "off")
                debugOff();
            else
                Serial.println("Invalid");
        }
        else if (operation == "set")
        {
            int newAngle = command.toInt();
            setAngle(newAngle, defaultDelay, 1);
            playMelody(2);
        }
        else if (operation == "passwd")
        {
            String param = command;
            for (int i = 0; i < passwdLen; i++)
                passwd[i] = (byte)(param[i] - '0');
            setPasswd();
            Serial.print("Password set to: ");
            for (int i = 0; i < passwdLen; i++)
                Serial.print(passwd[i]);
            Serial.println();
        }
        else
        {
            Serial.println("Invalid command");
        }
    }

    if (btSerial.available())
    {
        Status code = getMessage();

        if (code == ChangePassword)
        {
            sendMessage(Processing);
            storePasswd(4);
            for (int i = 0; i < passwdLen; i++)
                passwd[i] = receivedPasswd[i];
            setPasswd();
            sendMessage(Success);
        }
        if (code == OneClickOpen)
        {
            sendMessage(Processing);
            oneClickOpen();
            sendMessage(Success);
        }
        if (code == SetAngle)
        {
            int tar = receivedMessage[4];
            int requestDelay = receivedMessage[5];
            int deAtt = receivedMessage[6];
            playMelody(2);
            sendMessage(Processing);
            setAngle(tar, requestDelay, deAtt);
            sendMessage(Success);
        }
        if (code == PlayMelody)
        {
            sendMessage(Processing);
            int variant = receivedMessage[4];
            playMelody(variant);
            sendMessage(Success);
        }
        if (code == WrongPassword)
        {
            sendMessage(WrongPassword);
        }
        if (code == Invalid)
        {
            sendMessage(Invalid);
        }
    }
}
