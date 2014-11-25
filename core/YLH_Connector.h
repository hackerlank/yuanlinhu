


//服务器网络链接模块


#ifndef _YLH_CONNECT_H_
#define _YLH_CONNECT_H_

#include "ace/Connector.h"
#include "ace/SOCK_Connector.h"


#include "YLH_Server_Info.h"
#include "YLH_Sock_Handler.h"
#include "YLH_Sock_Handler.h"


typedef ACE_Connector<YLH_Sock_Handler, ACE_SOCK_CONNECTOR> connector_super;

class YLH_Connector : public connector_super
{
public:
    YLH_Connector(ACE_Reactor* Owner_Reactor, YLH_Server* owner_server);
    virtual int make_svc_handler (YLH_Sock_Handler *&sh);

public:
    void add_connnection_info(YLH_Connect_Info& connect_info);

    void open_connect();
    void send_test_buff();

    void add_connect_handler(ACE_HANDLE handle, YLH_Sock_Handler* connect_handler);
    void del_connect_handler(ACE_HANDLE handle, YLH_Sock_Handler* accept_handler);
    YLH_Sock_Handler* get_connect_handler(int port);

    ACE_Reactor* get_Owner_Reactor();

    int do_connect(YLH_Sock_Handler* connect_handler, YLH_Connect_Info connect_info);

private:
    int Open_Connect(YLH_Connect_Info& connect_info);

private:
    YLH_Server*     m_owner_server;
    ACE_Reactor*    m_Owner_Reactor;
    //ACE_Connector<YLH_Connector_Handler, ACE_SOCK_CONNECTOR>    m_connector;

    std::map<ACE_HANDLE, YLH_Sock_Handler*>          m_connect_handler_list;

    std::vector<YLH_Connect_Info>      m_connection_config_list;   //配置信息

private:
    YLH_Connector();
};

#endif  //_YLH_CONNECT_H_