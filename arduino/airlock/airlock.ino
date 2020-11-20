#include "melodies.h"
#include "control.h"
#include "tools.h"
#include "communication.h"

int touchPin = 7;

bool touch = false;

Operation op;

void setup()
{
    getPasswd();
//    resetPasswd();
    
    Serial.begin(9600);
    mySerial.begin(9600);
    
    pinMode(touchPin, INPUT);
    initServo();

    Serial.println("Init Successful");
}

void loop()
{
    touch = digitalRead(touchPin);
    if (touch)
    {
        playMelody(0);
        openLock();
        playMelody(1);
        while (touch)
        {
            delay(5);
            touch = digitalRead(7);
        }
        delay(1500);
        closeLock();
    }

    if (Serial.available())
    {
        int newAngle = serialReadInt();
        Serial.print("Received ");
        Serial.println(newAngle);
        setAngle(newAngle, defaultDelay);
        playMelody(2);
    }

    if (mySerial.available())
    {
        op = getMessage();
        
        if (op == ChangePassword)
        {
            sendMessage(Processing);
            translatePasswd(1);
            for (int i = 0; i < passwdLen; i++)
            {
                passwd[i] = receivedPasswd[i];
            }
            setPasswd();
            sendMessage(Success);
        }
        
        if (op == OneClickOpen)
        {
            sendMessage(Processing);
            oneClickOpen();
            sendMessage(Success);
        }
        
        if (op == SetAngle)
        {
            int tar = receivedMessage[4];
            int requestDelay = receivedMessage[5];
            sendMessage(Processing);
            setAngle(tar, requestDelay);
            sendMessage(Success);
        }

        if (op == PlayMelody)
        {
            sendMessage(Processing);
            int tar = receivedMessage[4];
            playMelody(tar);
            sendMessage(Success);
        }

        if (op == WrongPassword)
        {
            sendMessage(WrongPassword);
        }

        if (op == Invalid)
        {
            sendMessage(Invalid);
        }
    }
}
