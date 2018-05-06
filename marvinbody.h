#ifndef MARVINBODY_H
#define MARVINBODY_H

#include <QTcpServer>
#include <QDebug>
#include "trillianbody.h"

class Dialog;
class trillianBody;

class marvinBody : public QTcpServer
{
    Q_OBJECT

public:
    explicit marvinBody(QWidget *widget = 0, QObject *parent = 0);

    bool doStartServer(QHostAddress addr, qint16 port);
    void doSendToAllUserJoin(QString name); //уведомить о новом пользователе
    void doSendToAllUserLeft(QString name);
    void doSendToAllMessage(QString message, QString fromUsername); //разослать сообщение
    void doSendToAllServerMessage(QString message);//серверное сообщение
    void doSendServerMessageToUsers(QString message, const QStringList &users); //приватное серверное сообщение
    void doSendMessageToUsers(QString message, const QStringList &users, QString fromUsername);
    QStringList getUsersOnline() const; //узнать список пользователей
    bool isNameValid(QString name) const; //проверить имя
    bool isNameUsed(QString name) const; //проверить используется ли имя
    void setDia(Dialog *_dialog);

signals:
    void addLogToGui(QString string, QColor color = Qt::black);

public slots:
    void onMessageFromGui(QString message, const QStringList &users);
    void onRemoveUser(trillianBody *client);

protected:
    void incomingConnection(int handle);

private:
    QList<trillianBody *> _clients; //список пользователей
    QWidget *_widget; //ссылка на виджет для подключения к нему сигналов от trillianBody
    Dialog *ui;
};

#endif // MARVINBODY_H
