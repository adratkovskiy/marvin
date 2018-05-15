#include "marvinhand.h"

#define PIN RPI_V2_GPIO_P1_03

marvinHand::marvinHand(QObject *parent, Dialog *dia)
{
    ui = dia;
    ui->logMe("marvinHand connecter");
    bcm2835_init();
    bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RPI_GPIO_P1_23, BCM2835_GPIO_FSEL_OUTP);
}

marvinHand::~marvinHand()
{
    bcm2835_close();
}

void marvinHand::ioStatus(QString status)
{

}

void marvinHand::setOn(int numBCM)
{
    switch (numBCM) {
    case 11:
        if (status11 == false) {
            bcm2835_gpio_write(RPI_GPIO_P1_11, HIGH);
            status11 = true;
        }
        break;
    case 23:
        if (status23 == false) {
            bcm2835_gpio_write(RPI_GPIO_P1_23, HIGH);
            status23 = true;
        }
        break;
    default:
        break;
    }
    ui->logMe("set on RPI_GPIO_P1_" + QString::number(numBCM));
}

void marvinHand::setOff(int numBCM)
{
    switch (numBCM) {
    case 11:
        if (status11)
        {
            bcm2835_gpio_write(RPI_GPIO_P1_11, LOW);
            status11 = false;
        }
        break;
    case 23:
        if (status23)
        {
            bcm2835_gpio_write(RPI_GPIO_P1_23, LOW);
            status23 = false;
        }
        break;
    default:
        break;
    }
    ui->logMe("set off RPI_GPIO_P1_" + QString::number(numBCM));
}
