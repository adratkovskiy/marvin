#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QtGui>
#include <QtCore>
#include "marvinbody.h"
#include "eye.h"
#ifdef Q_OS_WIN

#else
    #include "marvinhand.h"
#endif
#include "udp.h"

namespace Ui {
    class Dialog;
}

class eye;
class marvinHand;
class udp;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void logMe(QString toLog);
    void setCmd(QString cmd);
    void joyState(QString cmd);

private:
    Ui::Dialog *ui;
    marvinBody *_serv;
    eye *marvinEye;
    marvinHand *hand;
    void addToLog(QString text, QColor color);
    udp *udpSock;

signals:
    void messageFromGui(QString message, const QStringList &users);

public slots:
    void onAddUserToGui(QString name);
    void onRemoveUserFromGui(QString name);
    void onMessageToGui(QString message, QString from, const QStringList &users);
    void onAddLogToGui(QString string, QColor color);

private slots:
    void on_pbSend_clicked();
    void on_cbToAll_clicked();
    void on_pbStartStop_toggled(bool checked);
    void on_pbStartStop_clicked();
    void on_btnOn_clicked();
    void on_btnOff_clicked();
};

#endif // DIALOG_H
