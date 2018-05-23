#ifndef MARVINHAND_H
#define MARVINHAND_H
#include <QObject>
#ifdef Q_OS_WIN

#else
    #include "bcm2835.h"
#endif

#include "dialog.h"

class marvinHand : public QObject
{

public:
    marvinHand(QObject *parent = nullptr, Dialog *dia = nullptr);
    ~marvinHand();
    void setOn(int numBCM);
    void setOff(int numBCM);
    void ioStatus(int joyState[20]);
    void joyStatus(QString status);

public slots:

private:
    Dialog *ui;
    bool statusIO[40];
};

#endif // MARVINHAND_H
