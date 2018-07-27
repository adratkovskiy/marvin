#include "tpca.h"
#include "src/pca9685.h"
#include <QDebug>

tPCA::tPCA(QObject *parent, Dialog *dia) : QObject(parent)
{
    ui = dia;
    wiringPiSetup();
    // Setup with pinbase 300 and i2c location 0x40
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0)
    {
        printf("Error in setup\n" + fd);
        //return fd;
    }
    qDebug() << fd;
    // Reset all output
    pca9685PWMReset(fd);


    // Set servo to neutral position at 1.5 milliseconds
    // (View http://en.wikipedia.org/wiki/Servo_control#Pulse_duration)
    float millis = 1.5;
    int pinNum = 16;
    int tick = calcTicks(millis, HERTZ);
    pwmWrite(PIN_BASE + pinNum, tick);
    qDebug() << "mullis:" << millis << " tick:" << tick;
    delay(2000);

    /*int active = 0;
    while (active < 10)
    {
        // That's a hack. We need a random number < 1
        float r = rand();
        while (r > 1)
            r /= 10;

        millis = map(r, 1, 2);
        tick = calcTicks(millis, HERTZ);
        qDebug() << "mullis:" << millis << " tick:" << tick;
        pwmWrite(PIN_BASE + pinNum, tick);

        delay(500);
        active++;
    }

    tick = calcTicks(1.5, HERTZ);*/
    qDebug() << "mullis default:" << millis << " tick:" << tick;
    pwmWrite(PIN_BASE + pinNum, tick);

    /*move(1.5);
    qDebug() << "default";
    delay(1000);
    float angle_move = 0.1;
    for (angle_move = 1.1; angle_move < 3; angle_move += 0.1)
    {
        move(angle_move);
    }*/

}

void tPCA::move(float mil, int joy)
{
    //int pinNum = 4;
    int tick = calcTicks(mil, HERTZ);
    pwmWrite(PIN_BASE + joy, tick);
    qDebug() << "millis:" << mil << " tick:" << tick;
    delay(20);
}

int tPCA::calcTicks(float impulseMs, int hertz)
{
    float cycleMs = 1000.0f / hertz;
    return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

/**
 * input is [0..1]
 * output is [min..max]
 */

float tPCA::map(float input, float min, float max)
{
    return (input * max) + (1 - input) * min;
}
