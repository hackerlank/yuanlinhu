


//


#ifndef _YLH_SOCK_HANDLER_H
#define _YLH_SOCK_HANDLER_H

#include "ace/Global_Macros.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Stream.h"
#include "ace/Event_Handler.h"

class YLH_Server;

class YLH_Sock_Handler : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
    typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH> super;

public:
    YLH_Sock_Handler();
    void set_owner_sever(YLH_Server* owner_server);

    virtual int open (void * = 0);

    virtual int handle_input(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);

    virtual int handle_output(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);

    virtual int handle_close (ACE_HANDLE = ACE_INVALID_HANDLE, ACE_Reactor_Mask = ACE_Event_Handler::ALL_EVENTS_MASK);

    virtual int handle_timeout (const ACE_Time_Value &time, const void *);

    virtual int handle_signal (int signum, siginfo_t * = 0, ucontext_t * = 0);

    void set_timer(int second);

    void set_buff(std::string send_buff) { m_send_buff = send_buff; }

    void set_port(int port);
    int  get_port();

private:
    //YLH_Sock_Handler();
    std::string m_send_buff;

    YLH_Server*     m_owner_server;
    int             m_port;
};



#endif  //_YLH_SOCK_HANDLER_H