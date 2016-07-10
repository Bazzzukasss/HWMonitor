#ifndef NETUDPCLIENTLINPACK_H
#define NETUDPCLIENTLINPACK_H

#include <QObject>
#include <QString>
#include <QUdpSocket>
#include "NetUDPClient.h"
#include "NetPacket.h"
#include "NetDevice.h"

#define ADD_STATE(STATE,MODULE,MASK)    netDevice.addState( STATE ,new NetState(""#STATE,MODULE,MASK))
#define ADD_CMD(CMD,MODULE,MASK)        netDevice.addCommand( CMD ,new NetCommand(""#CMD,MODULE,MASK))
#define ADD_MODULE( NAME )              netDevice.addModule( NAME ,new NetModule(""#NAME,MDL_TYPE_DIGITAL,MDL_MODE_INOUT,IO32));

enum HWCmdResultsEnum{
    RES_OK=0x0,
    RES_ERROR=0xEEEEEEEE
};
enum HWServerCmdEnum{
    CMD_SET=0x24534554,//'$SET',
    CMD_GET=0x24474554//'$GET'
};

class NetUDPClient_Linpack : public NetUDPClient
{
    Q_OBJECT
    public:
        explicit NetUDPClient_Linpack(const QString& _ip, int _port,QObject *parent);
        virtual ~NetUDPClient_Linpack();
        NetDevice*  getNetDevice()  {return &netDevice;}
        virtual void send_CMD_SET(bool _is_emulation=false);
        virtual void send_CMD_GET(bool _is_emulation=false);

    protected:
        virtual void genLPModuleIOValues(LinPackModule& _module);
        virtual void genLPModule(LinPackModule& _module);
        virtual void genNetPacket(int _cmd);
        virtual void handler();
        virtual void CMD_SET_handler();
        virtual void CMD_GET_handler();

        void send_CMD(int _cmd, bool _isWaitForAnswer=true);
        NetPacket netPacket;
        NetDevice netDevice;
};

#endif // NETUDPCLIENTLINPACK_H
