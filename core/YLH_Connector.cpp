#include "YLH_Connector.h"
#include <sstream>

YLH_Connector::YLH_Connector( ACE_Reactor* Owner_Reactor, YLH_Server* owner_server)
:m_Owner_Reactor(Owner_Reactor)
,m_owner_server(owner_server)
{

}

int YLH_Connector::Open_Connect( YLH_Connect_Info& connect_info )
{
    connector_super::reactor(m_Owner_Reactor);

    //YLH_Sock_Handler::addr_type connect_port(connect_info.connect_port);
    ACE_INET_Addr connect_port(connect_info.connect_port, "127.0.0.1");
    YLH_Sock_Handler* p = NULL;// = new YLH_Sock_Handler();
    //p->reactor(m_Owner_Reactor);
    //p->m_Connect_info = connect_info;
    //p->open();
    if (-1 == connector_super::connect(p, connect_port))
    {
        return -1;
    }

    p->set_owner_sever(m_owner_server);
    p->set_port(connect_info.connect_port);

    add_connect_handler(p->get_handle(), p);
    
    
    return 0;
}

void YLH_Connector::add_connnection_info(YLH_Connect_Info& connect_info)
{
    m_connection_config_list.push_back(connect_info);
}

void YLH_Connector::open_connect()
{
    std::vector<YLH_Connect_Info>::iterator iter;
    for (iter = m_connection_config_list.begin(); iter != m_connection_config_list.end(); ++iter)
    {
        if (NULL == get_connect_handler(iter->connect_port))
        {
            Open_Connect(*iter);
        }
        
    }
}

void YLH_Connector::send_test_buff()
{
    std::map<ACE_HANDLE, YLH_Sock_Handler*>::iterator iter;
    for (iter = m_connect_handler_list.begin(); iter != m_connect_handler_list.end(); ++iter)
    {
        static int kk = 0;
        kk++;
        std::stringstream oo;
        oo.clear();
        oo<<"YLH_Connector send buff "<<kk<<" "<<std::endl;
        std::string str_buff_1 = oo.str();
        iter->second->peer().send_n(str_buff_1.c_str(), str_buff_1.size());
    }
}

int YLH_Connector::make_svc_handler (YLH_Sock_Handler *&sh)
{
    if (sh == 0)
        ACE_NEW_RETURN (sh,
        YLH_Sock_Handler(),
        -1);

    sh->reactor (m_Owner_Reactor);

    add_connect_handler(sh->get_handle(), sh);

    ////sh->set_timer(1);
    //sh->set_buff(("YLH_Connector send_buff")); //testcode

    //const std::string  str("YLH_Connector::make_svc_handler nihao ");
    //sh->peer().send_n(str.c_str(), str.size());
    return 1;
}


void YLH_Connector::add_connect_handler(ACE_HANDLE handle, YLH_Sock_Handler* accept_handler)
{
    std::map<ACE_HANDLE, YLH_Sock_Handler*>::iterator iter = m_connect_handler_list.find(handle);
    if (iter != m_connect_handler_list.end())
    {
        //ACE_ERROR();
    }

    m_connect_handler_list[handle] = accept_handler;
}

YLH_Sock_Handler* YLH_Connector::get_connect_handler(int port)
{
    std::map<ACE_HANDLE, YLH_Sock_Handler*>::iterator iter;
    for (iter = m_connect_handler_list.begin(); iter != m_connect_handler_list.end(); ++iter)
    {
        if (iter->second->get_port() == port)
        {
            return iter->second;
        }
    }

    return NULL;
}


void YLH_Connector::del_connect_handler(ACE_HANDLE handle, YLH_Sock_Handler* accept_handler)
{
    std::map<ACE_HANDLE, YLH_Sock_Handler*>::iterator iter = m_connect_handler_list.find(handle);
    if (iter != m_connect_handler_list.end())
    {
        //ACE_ERROR();
        m_connect_handler_list.erase(iter);
    }
}

ACE_Reactor* YLH_Connector::get_Owner_Reactor()
{
    return m_Owner_Reactor;
}

int YLH_Connector::do_connect(YLH_Sock_Handler* connect_handler, YLH_Connect_Info connect_info)
{
    ACE_INET_Addr connect_port(connect_info.connect_port, "192.168.1.224");
    return connector_super::connect(connect_handler, connect_port);
}