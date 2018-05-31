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
    int tick = calcTicks(millis, HERTZ);
    pwmWrite(PIN_BASE + 16, tick);
    delay(2000);


    int active = 1;
    while (active < 5)
    {
        // That's a hack. We need a random number < 1
        qDebug() << active;
        float r = rand();
        while (r > 1)
            r /= 10;

        millis = map(r, 1, 2);
        tick = calcTicks(millis, HERTZ);

        pwmWrite(PIN_BASE + 16, tick);
        delay(1000);
        active++;
    }
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
