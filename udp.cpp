#include "udp.h"

udp::udp(QObject *parent, Dialog *dia, int _port) : QObject(parent)
{
    ui = dia;
    udpPort = _port;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, udpPort);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void udp::sendMess(QString mess)
{
    QByteArray Data;
    Data.append(mess);
    socket->writeDatagram(Data, QHostAddress::LocalHost, udpPort - 1);
}

void udp::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    quint16 senderPort;
    QHostAddress *address = new QHostAddress();
    socket->readDatagram(buffer.data(), buffer.size(), address);
    ui->setCmd(buffer);
    delete(address);
}
