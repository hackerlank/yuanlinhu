
#ifndef _SUB_THREAD_H_
#define _SUB_THREAD_H_

#include "ace/Task.h"

class ACE_Reactor_Notification_Strategy;

class Sub_Thread : public ACE_Task<ACE_MT_SYNCH>
{
public:

    Sub_Thread(ACE_Reactor* owner_reactor);

    void thread_start();

    virtual int handle_input(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);

    virtual int handle_output(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);

private:
    static ACE_THR_FUNC_RETURN thread_func (void *arg);
    void collect_msg(ACE_Message_Block* message);

private:
    Sub_Thread();


    ACE_Reactor_Notification_Strategy*  m_notify;

    ACE_Reactor*    m_self_reactor;
};

#endif  //_SUB_THREAD_H_

