#ifndef TPCA_H
#define TPCA_H

#include <QObject>
#include <wiringPi.h>
#include "dialog.h"
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

class tPCA : public QObject
{
    Q_OBJECT
public:
    explicit tPCA(QObject *parent = nullptr, Dialog *dia = nullptr);
    int calcTicks(float impulseMs, int hertz);
    float map(float input, float min, float max);
    void move(float mil, int joy);
private:
    Dialog *ui;
};

#endif // TPCA_H
