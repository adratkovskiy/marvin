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

public slots:

private:
    Dialog *ui;
    bool status11 = false;
    bool status23 = false;
};

#endif // MARVINHAND_H
