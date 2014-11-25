

#ifndef _ROLE_SERVER_H_
#define _ROLE_SERVER_H_

#include "YLH_Server.h"

class ACE_Time_Value;


class Role_Server : public YLH_Server
{
public:

    Role_Server();
    void open_server();

    virtual void collect_msg(char* recvbuf, int buff_size);
    
    virtual int  handle_timeout(const ACE_Time_Value &now, const void *act);

};



#endif  //_ROLE_SERVER_H_