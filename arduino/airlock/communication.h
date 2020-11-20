#include <SoftwareSerial.h>
#include "password.h"

int btTx = 2, btRx = 3;
SoftwareSerial mySerial(btTx, btRx);

int receivedMessageLen = 10;
int sentMessageLen = 3;
byte receivedMessage[10];
byte sentMessage[3];

enum Operation
{
    OneClickOpen = 1,
    SetAngle = 2,
    PlayMelody = 3,
    ChangePassword = 4,
};

enum Response
{
    Processing = 11,
    Success = 12,
    WrongPassword = 13,
    Invalid = 14,
    Failed = 15
};

int checkMessage()
{
    int res = 0;
    for (int i = 0; i < 8; i++)
    {
        res += receivedMessage[i];
        res %= 256;
    }
    if (res == receivedMessage[8])
        return 1;
    return 0;
}

void translatePasswd(int pos)
{
    // pos == 1: change passwd
    if (pos == 1)
        pos = 4;
    receivedPasswd[0] = receivedMessage[pos + 0] / 16;
    receivedPasswd[1] = receivedMessage[pos + 0] % 16;
    receivedPasswd[2] = receivedMessage[pos + 1] / 16;
    receivedPasswd[3] = receivedMessage[pos + 1] % 16;
    receivedPasswd[4] = receivedMessage[pos + 2] / 16;
    receivedPasswd[5] = receivedMessage[pos + 2] % 16;

    Serial.println("Received password:");
    for (int i = 0; i < 6; i++)
    {
        Serial.println(receivedPasswd[i]);
    }
}

void clearMySerial()
{
    while (mySerial.available())
    {
        mySerial.read();
        delay(1);
    }
}

int getMessage()
{
    byte cur;

    for (int i = 0; i < receivedMessageLen; i++)
    {
        if (mySerial.available())
        {
            cur = mySerial.read();
            receivedMessage[i] = cur;
        }
        else
        {
            return Invalid;
        }
        delay(5);
    }
    clearMySerial();

    if (receivedMessage[9] != 0xEF)
    {
        return Invalid;
    }
    if (!checkMessage())
    {
        return Invalid;
    }

    translatePasswd(0);
    if (!checkPasswd())
    {
        return WrongPassword;
    }

    if (receivedMessage[3] == 0x01)
        return OneClickOpen;
    if (receivedMessage[3] == 0x02)
        return SetAngle;
    if (receivedMessage[3] == 0x03)
        return PlayMelody;
    if (receivedMessage[3] == 0x04)
        return ChangePassword;

    return Invalid;
}

void sendMessage(int res)
{
    if (res == Processing)
    {
        sentMessage[0] = 0x01;
    }
    if (res == Success)
    {
        sentMessage[0] = 0x02;
    }
    if (res == Failed)
    {
        sentMessage[0] = 0x03;
    }
    if (res == WrongPassword)
    {
        sentMessage[0] = 0x04;
    }
    if (res == Invalid)
    {
        sentMessage[0] = 0x05;
    }

    sentMessage[1] = (sentMessage[0] + 1) % 256;
    sentMessage[2] = 0xEF;

    for (int i = 0; i < sentMessageLen; i++)
    {
        mySerial.write(sentMessage[i]);
        delay(1);
    }
}
