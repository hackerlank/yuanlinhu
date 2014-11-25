

#ifndef _GAME_SERVER_H_
#define _GAME_SERVER_H_

#include "YLH_Server.h"
#include <vector>

class Sub_Thread;

class Game_Server : public YLH_Server
{
public:
    
    Game_Server();
    virtual void collect_msg(char* recvbuf, int buff_size);


    std::vector<Sub_Thread*>     m_sub_thread_list;
};



#endif  //_GAME_SERVER_H_