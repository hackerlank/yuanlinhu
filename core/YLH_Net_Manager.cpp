

#include "YLH_Net_Manager.h"
#include "YLH_Server_Info.h"
#include "ace/TP_Reactor.h"
#include "ace/Log_Msg.h"

#define CONNECT_SERVER_TIME_ID  -1      //定时连接服务器

#define SEND_BUFF_TIME_ID -2        //发送buff

YLH_Net_Manager::YLH_Net_Manager(YLH_Server* owner_server)
:m_Reactor(NULL)
,m_owner_server(owner_server)
{
    ACE_TP_Reactor*  reactor_imp = new ACE_TP_Reactor();
    ACE_NEW_NORETURN(m_Reactor,ACE_Reactor(reactor_imp,1));

    m_acceptor = new YLH_Acceptor(m_Reactor, m_owner_server);
    m_connector = new YLH_Connector(m_Reactor, m_owner_server);
}

void YLH_Net_Manager::open()
{
    ACE_Time_Value send_interval(10, 10*1000);
    get_Reactor()->schedule_timer(this,
        reinterpret_cast<const void*>(CONNECT_SERVER_TIME_ID),
        send_interval, send_interval);

    ACE_Time_Value send_buff_interval(5, 5*1000);
    get_Reactor()->schedule_timer(this,
        reinterpret_cast<const void*>(SEND_BUFF_TIME_ID),
        send_buff_interval, send_buff_interval);
}

int YLH_Net_Manager::handle_timeout (const ACE_Time_Value &current_time,const void *act/* = 0*/)
{
    if(act == reinterpret_cast<const void *>(CONNECT_SERVER_TIME_ID))
    {
        m_connector->open_connect();
        m_connector->send_test_buff();
        return 0;
    }
    else if (act == reinterpret_cast<const void *>(SEND_BUFF_TIME_ID))
    {
        if( rand() % 2)
        {
            //m_acceptor->send_test_buff();
        }
    }

    return 0;
}

int YLH_Net_Manager::Open_Accept(YLH_Acceptor_Info& acceptor_info)
{
    return m_acceptor->Open_Accept(acceptor_info);
    ////开启监听
    //YLH_Sock_Handler::addr_type acceptor_addr(acceptor_info.acceptor_port);
    //if (-1 == m_acceptor.open(acceptor_addr, m_Reactor))
    //{
    //    return -1;
    //}

    //return 0;
}

void YLH_Net_Manager::add_connnection_info(YLH_Connect_Info& connect_info)
{
    m_connector->add_connnection_info(connect_info);
}

int YLH_Net_Manager::Open_Connect(YLH_Connect_Info& connect_info)
{
    //开启监听
    //YLH_Sock_Handler::addr_type acceptor_addr(connect_info.acceptor_port);
    //if (-1 == m_acceptor.open(acceptor_addr, m_Reactor))
    //{
    //    return -1;
    //}
    ACE_Time_Value send_interval(0, 10*1000);
    get_Reactor()->schedule_timer(this,
        reinterpret_cast<const void*>(CONNECT_SERVER_TIME_ID),
        send_interval, send_interval);
    return 0;
    //return m_connector->Open_Connect(connect_info);
}


void YLH_Net_Manager::run()
{
    printf("YLH_Net_Manager::run() \n");
    m_Reactor->run_reactor_event_loop();
}

ACE_Reactor* YLH_Net_Manager::get_Reactor()
{
    return m_Reactor;
}

void YLH_Net_Manager::del_handler(YLH_Sock_Handler* handler)
{
    m_connector->del_connect_handler(handler->get_handle(), handler);
    m_acceptor->del_accept_handler(handler->get_handle(), handler);
}