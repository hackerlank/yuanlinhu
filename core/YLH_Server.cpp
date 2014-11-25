#include "YLH_Server.h"
#include "YLH_Net_Manager.h"


YLH_Server::YLH_Server()
:m_Net_Manager(NULL)
{
    m_Net_Manager = new YLH_Net_Manager(this);
}

void YLH_Server::Load_File()
{

}

void YLH_Server::Init()
{
}

int YLH_Server::Open_Accept(YLH_Acceptor_Info& acceptor_info)
{
    return m_Net_Manager->Open_Accept(acceptor_info);
}

//int YLH_Server::Open_Connect(YLH_Connect_Info& connect_info)
//{
//    return m_Net_Manager->Open_Connect(connect_info);
//}

void YLH_Server::Run()
{
    m_Net_Manager->run();
}

ACE_Reactor* YLH_Server::get_Reactor()
{
    return m_Net_Manager->get_Reactor();
}

YLH_Net_Manager* YLH_Server::get_net_manager()
{
    return m_Net_Manager;
}

void YLH_Server::del_handler(YLH_Sock_Handler* handler)
{
    m_Net_Manager->del_handler(handler);
}