
#include "YLH_Acceptor.h"
#include <sstream>

YLH_Acceptor::YLH_Acceptor( ACE_Reactor* Owner_Reactor, YLH_Server* owner_server )
:m_Owner_Reactor(Owner_Reactor)
,m_owner_server(owner_server)
{
    
}

int YLH_Acceptor::Open_Accept( YLH_Acceptor_Info& acceptor_info )
{
    //¿ªÆô¼àÌý
    YLH_Sock_Handler::addr_type acceptor_addr(acceptor_info.acceptor_port);
    if (-1 == acceptor_super::open(acceptor_addr, m_Owner_Reactor))
    {
        return -1;
    }

    return 0;
}

int YLH_Acceptor::make_svc_handler (YLH_Sock_Handler *&sh)
{
    if (sh == 0)
        ACE_NEW_RETURN (sh,
        YLH_Sock_Handler(),
        -1);

    sh->set_owner_sever(m_owner_server);
    sh->reactor (m_Owner_Reactor);


    add_accept_handler(sh->get_handle(), sh);

    //sh->set_timer(3);
    //sh->set_buff(std::string("YLH_Acceptor send_buff")); //testcode

    const std::string  str("YLH_Acceptor::make_svc_handler nihao ");
    //sh->peer().send_n(str.c_str(), str.size());
    return 0;
}

void YLH_Acceptor::add_accept_handler(ACE_HANDLE handle, YLH_Sock_Handler* accept_handler)
{
    std::map<ACE_HANDLE, YLH_Sock_Handler*>::iterator iter = m_accept_handler_list.find(handle);
    if (iter != m_accept_handler_list.end())
    {
        //ACE_ERROR();
    }

    m_accept_handler_list[handle] = accept_handler;
}

void YLH_Acceptor::del_accept_handler(ACE_HANDLE handle, YLH_Sock_Handler* accept_handler)
{
    std::map<ACE_HANDLE, YLH_Sock_Handler*>::iterator iter = m_accept_handler_list.find(handle);
    if (iter != m_accept_handler_list.end())
    {
        m_accept_handler_list.erase(iter);
    }
}
ACE_Reactor* YLH_Acceptor::get_Owner_Reactor()
{
    return m_Owner_Reactor;
}

void YLH_Acceptor::send_test_buff()
{
    std::map<ACE_HANDLE, YLH_Sock_Handler*>::iterator iter;
    for (iter = m_accept_handler_list.begin(); iter != m_accept_handler_list.end(); ++iter)
    {
        static int kk = 10000;
        kk++;
        std::stringstream oo;
        oo.clear();
        oo<<"YLH_Acceptor send buff "<<kk<<" "<<std::endl;
        iter->second->peer().send_n(oo.str().c_str(), oo.str().size());
    }
}