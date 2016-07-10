#include "NetUDPClient.h"
NetUDPClient::NetUDPClient(const QString& _ip, int _port,QObject *parent)
    :QObject(parent),ip(_ip),port(_port)
{
    socket = new QUdpSocket(this);
    host_ip.setAddress(ip);
}

NetUDPClient::~NetUDPClient()
{
    delete socket;
}
bool NetUDPClient::reconnect(const QString& _ip, int _port)
{
    ip=_ip;
    host_ip.setAddress(_ip);
    port=_port;
    qDebug()<<"connect socket to ip:"<<ip<<" port:"<<port;
    if(!socket->bind(host_ip, port))
    {
        connect(socket, SIGNAL(readyRead()), this, SLOT(slotRecive()));
        qDebug()<<"done";
        return true;
    }
    else
    {
        qDebug()<<"fail";
        return false;
    }
}
bool NetUDPClient::reconnect()
{
    qDebug()<<"connect socket to ip:"<<ip<<" port:"<<port;
    if(!socket->bind(host_ip, port))
    {
        connect(socket, SIGNAL(readyRead()), this, SLOT(slotRecive()));
        qDebug()<<"done";
        return true;
    }
    else
    {
        qDebug()<<"fail";
        return false;
    }
}
void NetUDPClient::selfTest()
{
    QByteArray Data;
    Data.append("selfTest UDPClient");
    socket->writeDatagram(Data, host_ip, port);
}

int NetUDPClient::getReceivedSize()
{
    return receivedSize;
}

void NetUDPClient::setBuffer(char *_buffer, int _buffer_size)
{
    buffer=_buffer;
    bufferSize=_buffer_size;
}
void NetUDPClient::slotRecive()
{
    QHostAddress sender;
    quint16 senderPort;
    if((buffer!=nullptr)&&(bufferSize>0))
    {
        receivedSize=socket->pendingDatagramSize();
        if(receivedSize<=bufferSize)
            socket->readDatagram(buffer,receivedSize,&sender, &senderPort);
        else
            socket->readDatagram(buffer,bufferSize,&sender, &senderPort);
/*
            qDebug() << "[UDP Client reciveHandler]";
            qDebug() << "   received size: "<<receivedSize << " bytes";
            qDebug() << "   buffer size: "<<bufferSize << " bytes";
            qDebug() << "   host: " << sender.toString();
            qDebug() << "   port: " << senderPort << hex <<" (0x"<< senderPort <<")";
*/
            if(receivedSize>0)
                handler();
    }
    else
        qDebug()<<"UDPClient: buffer is not alocated!";

}
void NetUDPClient::send(char* _data,int _size,bool _isWaitForAnswer=true)
{
    socket->writeDatagram(_data,_size,host_ip, port);
    socket->waitForBytesWritten(500);
    if(_isWaitForAnswer)
        if(!socket->waitForReadyRead(500))
            qDebug()<<"UDPClient: wait timeout!";
}
