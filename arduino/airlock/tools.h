#ifndef __TOOLS_H__
#define __TOOLS_H__

int __debug_mode__ = 0;

void debugOn()
{
    Serial.println("Debug on");
    __debug_mode__ = 1;
}

void debugOff()
{
    Serial.println("Debug off");
    __debug_mode__ = 0;
}

void console(const char *str, int newline = 1)
{
    if (__debug_mode__)
    {
        if (newline)
            Serial.println(str);
        else
            Serial.print(str);
    }
}

void console(byte out, int newline = 1)
{
    if (__debug_mode__)
    {
        if (newline)
            Serial.println(out);
        else
            Serial.print(out);
    }
}

void console(int out, int newline = 1)
{
    if (__debug_mode__)
    {
        if (newline)
            Serial.println(out);
        else
            Serial.print(out);
    }
}

void clearSerial()
{
    while (Serial.available())
    {
        Serial.read();
        delay(1);
    }
}

int serialReadInt()
{
    int res = 0;
    int flag = 1;
    if (Serial.available())
    {
        for (int i = 0; i < 100; i++)
        {
            if (Serial.available())
            {
                int cur = Serial.read();
                if (cur == 10 || cur == 13)
                    break;
                if (cur == '-')
                    flag = -1;
                else
                {
                    res *= 10;
                    res += (cur - 48);
                }
            }
            delay(1);
        }
        res *= flag;
    }
    return res;
}

#endif
