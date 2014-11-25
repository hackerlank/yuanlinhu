


//服务器基类， 所有的服务器都由此派生
//包含
//1.服务器描述信息
//2.网络管理
//3.数据库管理
//4.日志管理


#ifndef _YLH_SERVER_H_
#define _YLH_SERVER_H_

#include "ace/Event_Handler.h"
#include "YLH_Server_Info.h"

class YLH_Server_Info;

class YLH_Net_Manager;
class YLH_Server_Info;
class YLH_Log_Manager;
class YLH_DB_Manager; 
class YLH_Sock_Handler;

class YLH_Server : public ACE_Event_Handler
{
public:
    YLH_Server();

    void Load_File();

    void Init();

    int Open_Accept(YLH_Acceptor_Info& acceptor_info);


    //int Open_Connect(YLH_Connect_Info& connect_info);

    void Run();

    ACE_Reactor* get_Reactor();
    YLH_Net_Manager* get_net_manager();

    //处理消息
    virtual void collect_msg(char* recvbuf, int buff_size) = 0;


    void del_handler(YLH_Sock_Handler* handler);
private:
    YLH_Net_Manager*    m_Net_Manager;  //网络
    YLH_Server_Info*    m_Server_Info;  //服务器描述信息
    YLH_Log_Manager*    m_Log_Manager;  //日志
    YLH_DB_Manager*     m_DB_Manager;   //数据库
};



#endif  //_YLH_SERVER_H_
