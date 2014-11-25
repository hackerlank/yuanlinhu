
#include "Sub_Thread.h"
#include "ace/Reactor.h"
#include "ace/Select_Reactor.h"
#include "ace/Reactor_Notification_Strategy.h"
#include <iostream>

Sub_Thread::Sub_Thread(ACE_Reactor* owner_reactor)
{
    ACE_Select_Reactor*   select_reactor = new ACE_Select_Reactor();
    m_self_reactor = new ACE_Reactor(select_reactor);

    reactor(m_self_reactor);

    m_notify = new ACE_Reactor_Notification_Strategy(NULL, NULL, ACE_Event_Handler::READ_MASK);
    m_notify->event_handler(this);
    m_notify->reactor(m_self_reactor);
    msg_queue_->notification_strategy(m_notify);

    
}

ACE_THR_FUNC_RETURN Sub_Thread::thread_func (void *arg)
{

    Sub_Thread* p_sub_world_thread = (Sub_Thread*) arg;
    ACE_Reactor* thread_reactor = p_sub_world_thread->reactor();

    //THREAD_REACTOR.ts_object(thread_reactor);

    //初始化自己的

    thread_reactor->owner (ACE_OS::thr_self ());
    thread_reactor->run_reactor_event_loop();

    return 0;
}

void Sub_Thread::thread_start()
{
    ACE_Thread_Manager::instance()->spawn_n(1, thread_func, this);
}

int Sub_Thread::handle_input(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */)
{
     printf("Sub_Thread::handle_input  thread_id[%d]\n", GetCurrentThreadId() );

     while(1) 
     {
         //if (msg_queue_.is_empty()) 
         //{
         //    break;
         //}
         ACE_Message_Block* message = NULL;
         
         if (getq(message, NULL) == -1) 
         {
             ACE_DEBUG((LM_ERROR, "%T (%t)getq(message,NULL) == -1\n"));
             return 0;
         }      

         //分发数据包
         this->collect_msg(message);

         ACE_Message_Block::release(message);
         message = NULL;
     }
     return 1;
}

void Sub_Thread::collect_msg(ACE_Message_Block* message)
{
    ACE_Data_Block * tmp_data_block = message->data_block();
    if (NULL == tmp_data_block)
    {
        return;
    }

    std::string str(tmp_data_block->base());
    std::cout<<"Sub_Thread::collect_msg msg[ "<<str<<" ] "<<std::endl;
}

int Sub_Thread::handle_output(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */)
{
    printf("Sub_Thread::handle_output  thread_id[%d]\n", GetCurrentThreadId() );

    return 1;
}