#include "Role_Server.h"
#include "ace/Time_Value.h"
#include "ace/Reactor.h"

#define  TIMER_SEND -1

Role_Server::Role_Server()
{

}

void Role_Server::open_server()
{
    //ACE_Time_Value send_interval(0, 5*1000);
    //get_Reactor()->schedule_timer(this,
    //    reinterpret_cast<const void*>(TIMER_SEND),
    //    send_interval, send_interval);
}

int  Role_Server::handle_timeout(const ACE_Time_Value &now, const void *act)
{
    if (reinterpret_cast<const void *>(TIMER_SEND) == act)
    {
        int kk = 0;
        /*if(now.sec() < get_activity_start_sec())
        {
            send_notice(SPECIAL_PEOPEN_NOTICE);
        }*/
    }
    
    return 0;
}

void Role_Server::collect_msg(char* recvbuf, int buff_size)
{

}