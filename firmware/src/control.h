#include <Servo.h>
#include "tools.h"

int servoPin = 6;
Servo myServo;

int minAngle = 0;
int maxAngle = 120;
int curAngle = minAngle;
int defaultDelay = 30;

void initServo()
{
    playMelody(3);
    myServo.attach(servoPin);
    delay(100);
    curAngle = minAngle;
    myServo.write(minAngle);
    delay(3000);
    myServo.detach();
    delay(100);
    playMelody(4);
}

void setAngle(int tarAngle, int servoDelay, int deAtt)
{
    if (tarAngle < minAngle)
        tarAngle = minAngle;
    if (tarAngle > maxAngle)
        tarAngle = maxAngle;

    if (!myServo.attached())
    {
        myServo.attach(servoPin);
        delay(100);
    }

    if (curAngle < tarAngle)
    {
        console("Setting angle to ", 0);
        console(tarAngle);
        for (int i = curAngle; i <= tarAngle; i++)
        {
            myServo.write(i);
            curAngle = i;
            delay(servoDelay);
        }
        console("Angle set to ", 0);
        console(tarAngle);
    }
    else // curAngle > tarAngle
    {
        console("Setting angle to ", 0);
        console(tarAngle);
        for (int i = curAngle; i >= tarAngle; i--)
        {
            myServo.write(i);
            curAngle = i;
            delay(servoDelay);
        }
        console("Angle set to ", 0);
        console(tarAngle);
    }

    delay(100);

    if (deAtt)
    {
        myServo.detach();
        delay(100);
    }
}

void openLock()
{
    setAngle(maxAngle, defaultDelay, 0);
}

void closeLock()
{
    setAngle(minAngle, defaultDelay, 1);
}

void oneClickOpen()
{
    console("OneClickOpen");
    playMelody(0);
    console("Opening");
    openLock();
    console("Opened");
    playMelody(1);
    delay(1500);
    console("Closing");
    closeLock();
    console("Closed");
}
