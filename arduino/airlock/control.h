#include <Servo.h>

int servoPin = 6;
Servo myServo;

int minAngle = 0;
int maxAngle = 120;
int curAngle = minAngle;
int defaultDelay = 30;

void setAngle(int tarAngle, int speedDelay)
{
    if (tarAngle < minAngle)
        tarAngle = minAngle;
    if (tarAngle > maxAngle)
        tarAngle = maxAngle;

    if (curAngle == tarAngle)
        return;

    myServo.attach(servoPin);

    if (curAngle < tarAngle)
    {
        for (int i = curAngle; i <= tarAngle; i++)
        {
            myServo.write(i);
            curAngle = i;
            Serial.print("Angle set to ");
            Serial.println(i);
            delay(speedDelay);
        }
    }
    else // curAngle > tarAngle
    {
        for (int i = curAngle; i >= tarAngle; i--)
        {
            myServo.write(i);
            curAngle = i;
            Serial.print("Angle set to ");
            Serial.println(i);
            delay(speedDelay);
        }
    }

    myServo.detach();
}

void initServo()
{
    curAngle = minAngle;
    myServo.attach(servoPin);
    myServo.write(minAngle);
    myServo.detach();
}

void openLock()
{
    setAngle(maxAngle, defaultDelay);
}

void closeLock()
{
    setAngle(minAngle, defaultDelay);
}

void oneClickOpen()
{
    Serial.println("OneClickOpen");
    playMelody(0);
    openLock();
    playMelody(1);
    delay(1500);
    closeLock();
}
