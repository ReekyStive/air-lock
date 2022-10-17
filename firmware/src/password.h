#include <EEPROM.h>

int passwdLen = 6;
byte passwd[6] =
{
    1, 2, 3, 4, 5, 6
};

byte receivedPasswd[6] =
{
    -1, -1, -1, -1, -1, -1
};

void getPasswd()
{
    for (int i = 0; i < passwdLen; i++)
    {
        passwd[i] = EEPROM.read(i);
    }
}

void setPasswd()
{
    for (int i = 0; i < passwdLen; i++)
    {
        EEPROM.write(i, passwd[i]);
    }
}

void resetPasswd()
{
    passwd[0] = 1;
    passwd[1] = 2;
    passwd[2] = 3;
    passwd[3] = 4;
    passwd[4] = 5;
    passwd[5] = 6;
    setPasswd();
}

int checkPasswd()
{
    for (int i = 0; i < passwdLen; i++)
    {
        if (passwd[i] != receivedPasswd[i])
        {
            return 0;
        }
    }
    return 1;
}
