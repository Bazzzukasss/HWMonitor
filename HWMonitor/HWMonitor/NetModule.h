#ifndef NETMODULE_H
#define NETMODULE_H

#include <iostream>
#include <vector>
#include "NetCommand.h"

using namespace std;

enum NetModuleIOValueCount{IO8=8,IO24=24,IO16=16,IO32=32};
enum NetModuleTypeEnum{MDL_TYPE_DIGITAL,MDL_TYPE_ANALOG};
enum NetModuleModeEnum{MDL_MODE_INOUT,MDL_MODE_IN,MDL_MODE_OUT};
enum NetModuleModifyEnum{MODIFY_READ,MODIFY_WRITE=1};
class NetModule{
    public:
        NetModule(const string& _name,int _type,int _mode,int _io_values_count):name(_name),type(_type),mode(_mode)
            {
                io_values.resize(_io_values_count);
            }
        NetModule(const NetModule& _module)
        {
            if(this!=&_module)
                *this=_module;
        }

        virtual ~NetModule(){}
        friend ostream& operator<<(ostream& os,NetModule& rhv)
            {
                os<<hex<<"\tNetModule:\t["<<rhv.getName()<<"]\t["<<rhv.getModeString()<<"]\t[ "<<dec;
                for(auto v:rhv.io_values)
                    os<<v<<" ";
                os<<"]";
                return os;
            }
        const vector<short int>& getIOValues() const
        {
            return io_values;
        }

        void setIOValues(short int* _io_values)
        {
            short int* pVal=_io_values;
            for(auto& v:io_values)
                v=*pVal++;
        }
        void setIOValue(int _io_mask,int _value)
        {
            io_values[_io_mask]=(short int)_value;
        }

        const string& getName()const{return name;}
        int getType()const {return type;}
        int getMode()const {return mode;}
        string getModeString()
            {
                switch(mode)
                {
                    case MDL_MODE_INOUT:return "INOUT";break;
                    case MDL_MODE_IN:return "IN";break;
                    case MDL_MODE_OUT:return "OUT";break;
                    default: return "UNKNOWN";break;
                }
            }
        int getIOValue(int _ind) const
            {
                if(_ind<(int)io_values.size())
                    return io_values[_ind];
                else
                    return 0;
            }
        bool applyCommand(int _io_mask,int _value)
            {
                setIOValue(_io_mask,_value);
                return true;
            }
        int getIOValuesCount()const {return io_values.size();}

    protected:
        string name;
        int type;
        int mode;
        vector<short int> io_values;
};

#endif // NETMODULE_H
