#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QString>
#include <QMutex>
#include <QUdpSocket>
#include <QMutexLocker>
#include <QScopedPointer>
#include "unistd.h"
#include "HWConnection.h"

class NetUDPClient : public QObject
{
    Q_OBJECT
    public:
        explicit NetUDPClient(const QString& _ip,int _port,QObject *parent = 0);
        explicit NetUDPClient(const HWConnection& _session,QObject *parent = 0);
        virtual ~NetUDPClient();
        void selfTest();
        int getReceivedSize();
        void setBuffer(char* _buffer,int _buffer_size);
        bool reconnect(const QString& _ip, int _port);
        bool reconnect();

    protected:
        virtual void handler()=0;
        void send(char* _data,int _size,bool _isWaitForAnswer);
        QMutex mutex;
    private:
        QString ip;
        int port;
        QUdpSocket *socket;
        QHostAddress host_ip;

        int receivedSize;
        int bufferSize;
        char* buffer;
    public slots:
        void slotRecive();

};

#endif // UDPCLIENT_H
