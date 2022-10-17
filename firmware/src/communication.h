#include <SoftwareSerial.h>
#include "password.h"
#include "tools.h"

int btTx = 2, btRx = 3;
SoftwareSerial btSerial(btTx, btRx);

int receivedMessageLen = 10;
int sentMessageLen = 3;
byte receivedMessage[10];
byte sentMessage[3];

enum Status
{
    OneClickOpen = 101,
    SetAngle = 102,
    PlayMelody = 103,
    ChangePassword = 104,
    Processing = 201,
    Success = 202,
    WrongPassword = 203,
    Invalid = 204,
    Failed = 205
};

int verifyMessage()
{
    return 1;
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

void storePasswd(int offset)
{
    // offset == 0: verify password
    // offset == 4: change passwd (in params)
    receivedPasswd[0] = receivedMessage[offset + 0] / 16;
    receivedPasswd[1] = receivedMessage[offset + 0] % 16;
    receivedPasswd[2] = receivedMessage[offset + 1] / 16;
    receivedPasswd[3] = receivedMessage[offset + 1] % 16;
    receivedPasswd[4] = receivedMessage[offset + 2] / 16;
    receivedPasswd[5] = receivedMessage[offset + 2] % 16;
}

void clearBtSerial()
{
    while (btSerial.available())
    {
        btSerial.read();
        delay(1);
    }
}

Status getMessage()
{
    byte cur;

    for (int i = 0; i < receivedMessageLen; i++)
    {
        if (btSerial.available())
        {
            cur = btSerial.read();
            receivedMessage[i] = cur;
        }
        else
        {
            return Invalid;
        }
        if (!btSerial.available())
            delay(10);
    }
    clearBtSerial();

    if (receivedMessage[9] != 0xEF)
    {
        return Invalid;
    }
    if (!verifyMessage())
    {
        return Invalid;
    }

    storePasswd(0);
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

    sentMessage[1] = (sentMessage[0] + 1) % 256; // verify bit
    sentMessage[2] = 0xEF;

    for (int i = 0; i < sentMessageLen; i++)
    {
        btSerial.write(sentMessage[i]);
        delay(1);
    }
}
