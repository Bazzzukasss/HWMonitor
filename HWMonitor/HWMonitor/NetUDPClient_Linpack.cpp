#include "NetUDPClient_Linpack.h"

NetUDPClient_Linpack::NetUDPClient_Linpack(const QString& _ip, int _port,QObject *parent = 0)
    :NetUDPClient(_ip,_port,parent)
{
    setBuffer(reinterpret_cast<char*>(netPacket.getPacket()),netPacket.getPacketSize());
    cout<<netDevice<<endl;
}

NetUDPClient_Linpack::~NetUDPClient_Linpack()
{
}

void NetUDPClient_Linpack::CMD_SET_handler()
{

}

void NetUDPClient_Linpack::CMD_GET_handler()
{

}

void NetUDPClient_Linpack::send_CMD_SET(bool _is_emulation)
{
    if(!_is_emulation)
    {
        QMutexLocker locker(&mutex);
        //for(int m=0;m<netDevice.getLPModulesCount();m++)
            //netPacket.fill(m,netDevice.getPCModule(m));
        for(auto m:netDevice.getSendModulesId())
            netPacket.fill(m,netDevice.getPCModule(m));
        send_CMD(CMD_SET);
    }
}
void NetUDPClient_Linpack::send_CMD_GET(bool _is_emulation)
{
    if(_is_emulation)
    {
        genNetPacket(CMD_GET);
        handler();
    }
    else
        send_CMD(CMD_GET);
}
void NetUDPClient_Linpack::genLPModuleIOValues(LinPackModule& _module)
{
    for(int i=0;i<_module.io_values_count;i++)
        _module.value[i]=(i*i)&0x21;
}

void NetUDPClient_Linpack::genLPModule(LinPackModule& _module)
    {
        static int m=0;
        static int t=0;
        static int n=0;
        _module.io_values_count=IO8*(m+2);
        _module.name=(++n);//*1000;
        _module.mode=m;
        _module.type=t;
        genLPModuleIOValues(_module);
        if(++m>=3)
        {
            m=0;
            t=(t==1)?0:(1);
        }
    }
void NetUDPClient_Linpack::genNetPacket(int _cmd)
    {
        netPacket.fill(_cmd,RES_OK,netDevice.getPCModulesCount());
        netPacket.getHeader()->modules_count=15;//sizeof(netPacket.getData()->modules)/sizeof(LinPackModule);
        for(int m=0;m<netPacket.getHeader()->modules_count;m++)
            genLPModule(netPacket.getData()->modules[m]);
    }
void NetUDPClient_Linpack::send_CMD(int _cmd, bool _isWaitForAnswer)
{
    netPacket.fill(_cmd,0,netDevice.getPCModulesCount());
    //cout<<netPacket;
    send(reinterpret_cast<char*>(netPacket.getPacket()),netPacket.getPacketSize(),_isWaitForAnswer);
}
void NetUDPClient_Linpack::handler()
{
    //cout<<netPacket;
    if(netPacket.getRes()==(int)RES_ERROR)
    {
        qDebug()<<"NetUDPClient_Rustavi: RES_ERROR!";
    }
    else
    {
        netDevice.setData(netPacket.getData()->modules,netPacket.getHeader()->modules_count);
        //cout<<netDevice;
        switch(netPacket.getCmd())
        {
            case CMD_SET:
                CMD_SET_handler();
                break;
            case CMD_GET:
                CMD_GET_handler();
                break;
        }
    }
    //cout<<netPacket;
}
