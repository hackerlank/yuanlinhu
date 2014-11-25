


//·þÎñÆ÷ÍøÂçÄ£¿é


#ifndef _YLH_NET_MANAGER_H_
#define _YLH_NET_MANAGER_H_

#include "YLH_Acceptor.h"
#include "YLH_Connector.h"

class YLH_Server;

class YLH_Net_Manager : public ACE_Event_Handler
{
public:
    YLH_Net_Manager(YLH_Server* owner_server);


    virtual int handle_timeout (const ACE_Time_Value &current_time,
        const void *act = 0);


    void open();

    int Open_Accept(YLH_Acceptor_Info& acceptor_info);

    void add_connnection_info(YLH_Connect_Info& connect_info);


    void run();
    
    ACE_Reactor*    get_Reactor();

    void del_handler(YLH_Sock_Handler* handler);


private:
    int Open_Connect(YLH_Connect_Info& connect_info);

private:
    ACE_Reactor*    m_Reactor;

    YLH_Acceptor*   m_acceptor;
    YLH_Connector*  m_connector;

    YLH_Server*     m_owner_server;
};



#endif  //_YLH_NET_MANAGER_H_