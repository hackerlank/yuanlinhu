
#include "YLH_Sock_Handler.h"
#include <sstream>

#include "YLH_Server.h"

static const int timer_id = -1;


YLH_Sock_Handler::YLH_Sock_Handler()
:m_owner_server(NULL)
,m_port(0)
{
    
}

void YLH_Sock_Handler::set_owner_sever(YLH_Server* owner_server)
{
    m_owner_server = owner_server;
}

void YLH_Sock_Handler::set_port(int port)
{
    m_port = port;
} 

int  YLH_Sock_Handler::get_port()
{
    return m_port;
}

int YLH_Sock_Handler::open( void * p/*= 0*/ )
{
    super::open(p);

    peer().enable(ACE_NONBLOCK);
    
    //reactor()->register_handler(this, ACE_Event_Handler::READ_MASK | WRITE_MASK | SIGNAL_MASK);
    reactor()->register_handler(SIGINT, this);
    return 0;
}

int YLH_Sock_Handler::handle_input( ACE_HANDLE fd /* = ACE_INVALID_HANDLE */ )
{
    printf("YLH_Sock_Handler::handle_input\n");

    static const size_t RECV_BUF_SIZE = 1024 * 4;

    static int  get_length = 0;

    // local receive buffer.
    char recvbuf[RECV_BUF_SIZE] = { 0 };

    // If has prev message then prepend to local receive buffer.

    // actually received size.
    int s_recv = 0;

    // read socket buffer as much as possible.

    // read data into local buffer from socket.

    //s_recv = this->peer().recv(recvbuf, RECV_BUF_SIZE);
    //if (-1 == s_recv)
    //{
    //    return -1;
    //}

    for (; (s_recv = this->peer().recv(recvbuf, RECV_BUF_SIZE)) > 0;)
    {

        //get_length += s_recv;
        printf("recv:%s\n", recvbuf);
        
        m_owner_server->collect_msg(recvbuf, s_recv);

        //static int kk = 10000;
        //kk++;
        //std::stringstream oo;
        //oo<<"socket_handler send buff "<<kk<<" "<<std::endl;
        //peer().send_n(oo.str().c_str(), oo.str().size());
        //process_received_buffer(recvbuf, s_recv);

        return 0;
    }

    if (s_recv == 0)
    {
        //close socket
        return -1;
    }

    // MF_ERROR("length = %d!..... \n", get_length);

    int last_err = ACE_OS::last_error();

    if (s_recv == -1 &&  last_err == EWOULDBLOCK) 
    {
        return 0;
    }
    return -1;
}

int YLH_Sock_Handler::handle_output( ACE_HANDLE fd /* = ACE_INVALID_HANDLE */ )
{
    ACE_ASSERT(0);
    printf("YLH_Sock_Handler::handle_output\n");

    static const int MF_IOV_MAX = 4*1024;
    ACE_Message_Block *chunk[MF_IOV_MAX];
    // gather message from message queue.
    size_t msg_index = 0;
    // total message length in chunk
    size_t chunk_length = 0;
    // number of messages remains in queue
    ssize_t remains = this->msg_queue_->message_count();
    bool no_dequeue_error = true;
    bool no_fatal_error = true;
    for (; remains > 0 && msg_index < MF_IOV_MAX && no_dequeue_error;) 
    {
        ACE_Message_Block* mblk = 0;
        remains = this->msg_queue_->dequeue_head(mblk);
        if (remains >= 0)
        {
            chunk[msg_index] = mblk;
            chunk_length += mblk->length();
            ++msg_index;
        }
        // error
        else if (ACE_OS::last_error() == EWOULDBLOCK)
        {
            //MF_ERROR("dequeue_head EWOULDBLOCK, read: %B", msg_index);
            no_dequeue_error = false;
        }
        else
        {
            //MF_ERROR("dequeue_head error %B, read: %B\n", remains, msg_index);
            no_dequeue_error = false;
            no_fatal_error = false;
        }

        printf("recv: %s \n", chunk);

    }


    // chunk must be released after exit this scope
    //release_chunk release(chunk, msg_index);

    //if (remains == 0) {
    //    // clear write mask
    //    this->reactor()->mask_ops(this, ACE_Event_Handler::WRITE_MASK,
    //        ACE_Reactor::CLR_MASK);
    //    //write_mask_flag = 0;
    //}

    if (no_fatal_error)
    {
        // send all messages at once.
        this->reactor()->mask_ops(this, ACE_Event_Handler::WRITE_MASK,
                    ACE_Reactor::CLR_MASK);
        return 0;
    }
    else
    {
        //ServiceId peer_id = this->hub_->get_handler_id(this);
        //MF_ERROR("%d:%d:%d handle_output error, close socket.\n",
        //    peer_id.main_type, peer_id.sub_type, peer_id.port);
        return -1;
    }

    return 1;
}

int YLH_Sock_Handler::handle_close( ACE_HANDLE /*= ACE_INVALID_HANDLE*/, ACE_Reactor_Mask /*= ACE_Event_Handler::ALL_EVENTS_MASK*/ )
{
    printf("YLH_Sock_Handler::handle_close\n");
    if (NULL != m_owner_server)
    {
        m_owner_server->del_handler(this);
    }
    return 0;
}

int YLH_Sock_Handler::handle_timeout( const ACE_Time_Value &time, const void * act)
{
    printf("YLH_Sock_Handler::handle_timeout\n");
    std::string send_buff = m_send_buff;
    int act_id(static_cast<int>(reinterpret_cast<const intptr_t>(act)));
    //if(act_id == timer_id)
    {
        //int  send_size = peer().send(send_buff.c_str(), send_buff.size());

        //printf("send:[%s]\n", send_buff.c_str());
    }

    return 0;
}

void YLH_Sock_Handler::set_timer(int second)
{
    //reactor()->schedule_timer(this, (void*)(timer_id), ACE_Time_Value(second), ACE_Time_Value(second));

    int kk = 9;
}

int YLH_Sock_Handler::handle_signal( int signum, siginfo_t * info /*= 0*/, ucontext_t * context/*= 0*/ )
{
    printf("YLH_Sock_Handler::handle_signal\n");

    //switch(signum) 
    //{ 
    //case SIGINT: 
    //    ACE_DEBUG((LM_DEBUG, "You pressed SIGINT \n"));

    //    break; 

    //} 


    return 0;
}