#include "eye.h"

eye::eye(QObject *parent,  Dialog *dia) : QObject(parent)
{
    ui = dia;
    ui->logMe("eye module connected");
}

