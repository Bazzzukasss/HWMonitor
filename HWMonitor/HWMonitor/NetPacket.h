/* 
 * File:   HWNetPacket.h
 * Author: Baza
 *
 * Created on March 20, 2015, 10:44 AM
 */

#ifndef HWNETPACKET_H
#define	HWNETPACKET_H
#include <string.h>
#include <iostream>
#include "HWPacket.h"
using namespace std;
#include "NetDevice.h"
class NetPacket
{
    public:
        NetPacket(){}
        ~NetPacket(){}

        void clear()                                {memset(&hwpacket,0,getPacketSize());}
        int getPacketSize()                         {return sizeof(HWPacket);}
        int getPacketHeaderSize()                   {return sizeof(HWPacketHeader);}
        int getPacketDataSize()                     {return sizeof(HWPacketData);}
        int getSendDataSize()                       {return sizeof(HWPacketData);}
        int getSendSize()                           {return (getSendDataSize()+getPacketHeaderSize());}

        HWPacket* getPacket()                       {return &hwpacket;}
        HWPacketHeader* getHeader()                 {return &hwpacket.Header;}
        HWPacketData* getData()                     {return &hwpacket.Data;}
        void clearHeader()                          {memset(&hwpacket.Header,0,getPacketHeaderSize());}
        hwpacket_t getCmd()const                    {return hwpacket.Header.cmd;}
        char* getCmdName()const                     {return (char*)&hwpacket.Header.cmd;}
        hwpacket_t getRes()const                    {return hwpacket.Header.res;}

        void fill(int _id,const NetModule* pNetModule)
        {
            if((pNetModule!=nullptr)&&(_id<MODULES_COUNT))
            {
                hwpacket.Data.modules[_id].modify=MODIFY_WRITE;
                for(int v=0;v<MODULES_VALUE_COUNT;v++)
                    hwpacket.Data.modules[_id].value[v]=pNetModule->getIOValue(v);
            }
        }
        void fill(int _cmd,int _res,int _modules_count)
            {
                hwpacket.Header.cmd=_cmd;
                hwpacket.Header.res=_res;
                hwpacket.Header.modules_count=_modules_count;
            }
        void fill(int _cmd,int _res,int _data_size,void* _data)
            {
                hwpacket.Header.cmd=_cmd;
                hwpacket.Header.res=_res;

                if(_data_size>getPacketDataSize())
                {
                    _data_size=getPacketDataSize();
                    cout<<"Error:packet data size is to big!"<<endl;
                }
                if(_data)
                    memcpy(&hwpacket.Data,_data,_data_size);
                else
                    memset(&hwpacket.Data,0,getPacketDataSize());
            }
        friend ostream& operator<<(ostream& os,const NetPacket& rhv)
            {
                const LinPackModule* pM;
                os<<dec<< "Packet:"<<endl;
                os<<hex<<"\tcmd: 0x"<<rhv.getCmd()<<"("<<rhv.getCmdName()<<")"<<endl;
                os<<hex<<"\tres: 0x"<<rhv.hwpacket.Header.res<<endl;
                os<<dec<<"\tlocal_id:"<<rhv.hwpacket.Header.local_id<<endl;
                os<<dec<<"\thost_id:"<<rhv.hwpacket.Header.local_id<<endl;
                os<<dec<<"\tmodules_count:"<<rhv.hwpacket.Header.modules_count<<endl;
                os<<"\tMODULES:"<<endl;
                for(int m=0;m<rhv.hwpacket.Header.modules_count;m++)
                {
                    pM=&rhv.hwpacket.Data.modules[m];
                    os<<"["<<m<<"]["<<pM->name<<"]["<<(int)pM->type<<"]["<<(int)pM->mode<<"]\t[";
                    for(int v=0;v<pM->io_values_count;v++)
                        os<<pM->value[v]<<" ";
                    os<<"]"<<endl;
                }
                return os;
            }
    private:
        HWPacket hwpacket;
};

#endif	/* HWSERVERPACKET_H */

