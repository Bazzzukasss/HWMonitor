#ifndef NETDEVICE_H
#define NETDEVICE_H

#include <map>
#include <vector>
#include <sstream>
#include "NetCommand.h"
#include "NetState.h"
#include "NetModule.h"
#include "HWPacket.h"
//RUSTAVI
class NetDevice
{
    public:
        NetDevice(){}
        ~NetDevice()
        {
            for(auto cmd:commands)
                delete cmd.second;
            for(auto s:states)
                delete s.second;
            clearPCModules();
            clearLPModules();
        }
        friend ostream& operator<<(ostream& os,const NetDevice& rhv)
            {
                os<<"NetDevice:"<<endl;

                os<<" PCModules:"<<endl;
                for(auto m:rhv.pcModules)
                    os<<*m.second<<endl;

                os<<" LPModules:"<<endl;
                for(auto m:rhv.lpModules)
                    os<<*m<<endl;

                os<<" Commands:"<<endl;
                for(auto cmd:rhv.commands)
                    os<<*cmd.second<<endl;

                os<<" States:"<<endl;
                int state_id=0;
                for(auto s:rhv.states)
                    os<<*s.second<<"["<<rhv.getState(state_id++)<<"]"<<endl;

                return os;
            }
        void addModule(int _id,NetModule* _module)
            {
                pcModules.insert(pair<int,NetModule*>(_id,_module));
            }
        void addCommand(int _id,NetCommand* _command)
            {
                commands.insert(pair<int,NetCommand*>(_id,_command));
            }
        void addState(int _id,NetState* _state)
            {
                states.insert(pair<int,NetState*>(_id,_state));
            }
        int getState(int _state_id) const
            {
                map<int,NetState*>::const_iterator st_it;
                NetState* pState;
                NetModule* pModule;

                st_it=states.find(_state_id);
                if(st_it!=states.end())
                {
                    pState=st_it->second;
                    if((int)lpModules.size()>pState->getModuleId())
                    {
                        pModule=lpModules.at(pState->getModuleId());
                        return pModule->getIOValue(pState->getMask());
                    }
                }
                return 0;
            }
        void setCommand(int _cmd_id,int _value=1)
            {
                map<int,NetCommand*>::iterator cmd_it;
                map<int,NetModule*>::iterator mdl_it;
                NetCommand* pCmd;

                cmd_it=commands.find(_cmd_id);
                if(cmd_it!=commands.end())
                {
                    pCmd=cmd_it->second;
                    mdl_it=pcModules.find(pCmd->getModuleId());
                    if(mdl_it!=pcModules.end())
                        mdl_it->second->applyCommand(pCmd->getMask(),_value);
                    else
                        qDebug()<<"Module id not found!";
                }
                else
                    qDebug()<<"Command id not found!";
            }
        void setPCModuleValue(int _id,int _io_mask,int _value)
        {
            map<int,NetModule*>::iterator mdl_it;
            mdl_it=pcModules.find(_id);
            if(mdl_it!=pcModules.end())
                mdl_it->second->setIOValue(_io_mask,_value);
            else
                qDebug()<<"Module id not found!";
        }

        void setData(LinPackModule* pModules,int _modules_count)
            {
                NetModule* pM;
                clearLPModules();
                for(int i=0;i<_modules_count;i++)
                {
                    stringstream sstream;
                    sstream << hex << pModules->name;
                    pM=new NetModule(sstream.str(),pModules->type,pModules->mode,pModules->io_values_count);
                    pM->setIOValues(pModules->value);
                    lpModules.push_back(pM);
                    pModules++;
                }
            }
        void clearLPModules()
            {
                for(auto m:lpModules)
                    delete m;
                lpModules.clear();
            }
        void clearPCModules()
            {
                for(auto m:pcModules)
                    delete m.second;
                pcModules.clear();
            }
        void clearSendModulesId()
            {
                sendModulesId.clear();
            }
        void addSendModuleId(int _id)
        {
            sendModulesId.push_back(_id);
        }

        int getPCModulesCount() const
            {
                return pcModules.size();
            }
        int getLPModulesCount() const
            {
                return lpModules.size();
            }
        const NetModule* getPCModule(int _id)
            {
                map<int,NetModule*>::iterator mdl_it;

                mdl_it=pcModules.find(_id);
                if(mdl_it!=pcModules.end())
                    return mdl_it->second;
                else
                    return nullptr;
            }
        const NetModule* getLPModule(int _id)
            {
                if(_id<(int)lpModules.size())
                    return lpModules[_id];
                else
                    return nullptr;
            }
        void genPCModules()
        {
            int i(0);
            clearPCModules();
            for(auto m:lpModules)
                addModule(i++,new NetModule(*m));
        }
        const vector<int>& getSendModulesId()
        {
            return sendModulesId;
        }

    protected:
        int host_id;
        int local_id;
        map<int,NetCommand*> commands;
        map<int,NetState*> states;
        map<int,NetModule*> pcModules;
        vector<NetModule*> lpModules;
        vector<int> sendModulesId;

};

#endif // NETDEVICE_H
