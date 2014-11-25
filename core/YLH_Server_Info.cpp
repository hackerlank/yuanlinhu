

#include "YLH_Server_Info.h"

YLH_Server_Info::YLH_Server_Info()
:m_Server_Type(SERVER_TYPE_NULL)
{

}

YLH_Acceptor_Info::YLH_Acceptor_Info()
:can_acceptor(false)
{

}

void YLH_Acceptor_Info::set_port( int port )
{
    can_acceptor = true;
    acceptor_port = port;
}

YLH_Connect_Info::YLH_Connect_Info()
{

}