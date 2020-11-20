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
