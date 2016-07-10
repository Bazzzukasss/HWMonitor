#ifndef NETCMD_H
#define NETCMD_H

#include <iostream>

using namespace std;

enum NetCommandTypeEnum{CMD_DIGIT,CMD_ANALOG};

class NetCommand
{
public:
    NetCommand(const string& _name,int _module_id,int _io_mask):name(_name),module_id(_module_id),io_mask(_io_mask){}
    friend ostream& operator<<(ostream& os,NetCommand& rhv)
        {
            os<<"\tNetCommand:\t[ name:"<<rhv.name<<"\tmodule:"<<rhv.module_id<<"\tmask:"<<rhv.io_mask<<"]";
            return os;
        }
    int getModuleId(){return module_id;}
    int getMask(){return io_mask;}
private:
    string name;
    int module_id;
    int io_mask;
};

#endif // NETCMD_H
