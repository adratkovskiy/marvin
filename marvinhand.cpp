#include "marvinhand.h"

#define PIN RPI_V2_GPIO_P1_03

marvinHand::marvinHand(QObject *parent, Dialog *dia)
{
    ui = dia;
    ui->logMe("marvinHand connecter");
    bcm2835_init();
    bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RPI_GPIO_P1_13, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RPI_GPIO_P1_15, BCM2835_GPIO_FSEL_OUTP);
}

marvinHand::~marvinHand()
{
    bcm2835_close();
}

void marvinHand::joyStatus(QString status)
{
    int iter = 0;
    bool space = false;
    int joyState[20];
    for (int i = 0; status.length() < i; i++)
    {
        if (space == true) {
            space = false;
        }
        else {
            if (status.mid(i, 1) == "-") {
                joyState[iter] = QString::toInt("-" + status.mid((i + 1), 1));
                space = true;
            }
            else {
                joyState[iter] = status.mid(i, 1);
            }
            iter++;
        }
    }
    ioStatus(joyState);
}

void marvinHand::ioStatus(int joyState[20])
{
    if (joyState[0] > 0) {
        setOn(11);
    }
    else {
        setOff(11);
    }
    if (joyState[1] > 0) {
        setOn(13);
    }
    else {
        setOff(13);
    }
    if (joyState[5] > 0) {
        setOn(15);
    }
    else {
        setOff(15);
    }
}

void marvinHand::setOn(int numBCM)
{
    if (statusIO[numBCM] == false) {
        ui->logMe("set on RPI_GPIO_P1_" + QString::number(numBCM));
        switch (numBCM) {
        case 11:
            bcm2835_gpio_write(RPI_GPIO_P1_11, HIGH);
            break;
        case 13:
            bcm2835_gpio_write(RPI_GPIO_P1_13, HIGH);
            break;
        case 15:
            bcm2835_gpio_write(RPI_GPIO_P1_15, HIGH);
            break;
        default:
            break;
        }
        statusIO[numBCM] = true;
    }
    else {

    }
}

void marvinHand::setOff(int numBCM)
{
    if (statusIO[numBCM] == true) {
        ui->logMe("set on RPI_GPIO_P1_" + QString::number(numBCM));
        switch (numBCM) {
        case 11:
            bcm2835_gpio_write(RPI_GPIO_P1_11, LOW);
            break;
        case 13:
            bcm2835_gpio_write(RPI_GPIO_P1_13, LOW);
            break;
        case 15:
            bcm2835_gpio_write(RPI_GPIO_P1_15, LOW);
            break;
        default:
            break;
        }
        statusIO[numBCM] = false;
    }
    else {

    }
}
