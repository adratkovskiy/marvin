#include "marvinhand.h"

//#define PIN RPI_V2_GPIO_P1_03

marvinHand::marvinHand(QObject *parent, Dialog *dia)
{
    /*
     *
    pinMode(0, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(0, HIGH);
    */
    ui = dia;
    ui->logMe("marvinHand connecter");
    wiringPiSetup();
    /*bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RPI_GPIO_P1_19, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RPI_GPIO_P1_15, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(RPI_GPIO_P1_11, LOW);
    bcm2835_gpio_write(RPI_GPIO_P1_19, LOW);
    bcm2835_gpio_write(RPI_GPIO_P1_15, LOW);*/

    for (int i = 0; i < 40; i++ )
    {
        statusIO.append(false);
    }
}

marvinHand::~marvinHand()
{
    /*bcm2835_gpio_write(RPI_GPIO_P1_11, LOW);
    bcm2835_gpio_write(RPI_GPIO_P1_19, LOW);
    bcm2835_gpio_write(RPI_GPIO_P1_15, LOW);
    bcm2835_close();*/
}

void marvinHand::joyStatus(QString status)
{
    int iter = 0;
    bool space = false;
    int joyState[24];
    QString statusView = "";
    for (int i = 0; i < status.size(); i++)
    {
        if (space == true) {
            space = false;
        }
        else {
            if (status.mid(i, 1) == "-") {
                QString tmpStr = "-" + status.mid((i + 1), 1);
                joyState[iter] = tmpStr.toInt();
                space = true;
            }
            else {
                joyState[iter] = status.mid(i, 1).toInt();
            }
            statusView.append(QString::number(joyState[iter]));
            iter++;
        }
    }
    QString tmpStr;
    for (int b = 0; b < iter; b++) {
        tmpStr.append(QString::number(joyState[b]));
        tmpStr.append('|');
    }
    //ui->logMe("2");
    ui->viewJoyState(tmpStr);
    moveAngle(joyState[1], 4);
    moveAngle(joyState[0], 1);
    //ui->logMe(joyState);
    //ioStatus(joyState);
}

void marvinHand::moveAngle(int ang, int joy)
{
    int base = 544;
    int mod = 103;
    int angle = base - mod + (mod * (ang +10));
    float angle_float = angle / 1000.0;
    //ui->logMe(QString::number(angle / 1000));
    ui->move(angle_float, joy);
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
        setOn(19);
    }
    else {
        setOff(19);
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
        ui->logMe("try set ON p_" + QString::number(numBCM));
        switch (numBCM) {
        case 11:
            //bcm2835_gpio_write(RPI_GPIO_P1_11, HIGH);
            break;
        case 19:
            //bcm2835_gpio_write(RPI_GPIO_P1_19, HIGH);
            break;
        case 15:
            //bcm2835_gpio_write(RPI_GPIO_P1_15, HIGH);
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
    if (statusIO.at(numBCM) == true) {
        ui->logMe("try set OFF p_" + QString::number(numBCM));
        switch (numBCM) {
        case 11:
            //bcm2835_gpio_write(RPI_GPIO_P1_11, LOW);
            break;
        case 19:
            //bcm2835_gpio_write(RPI_GPIO_P1_19, LOW);
            break;
        case 15:
            //bcm2835_gpio_write(RPI_GPIO_P1_15, LOW);
            break;
        default:
            break;
        }
        statusIO[numBCM] = false;
    }
    else {

    }
}
