


//服务器描述信息


#ifndef _SERVER_INFO_H_
#define _SERVER_INFO_H_

#include "Define.h"

enum SERVER_TYPE
{
    SERVER_TYPE_NULL,

    SERVER_TYPE_MANAGER,
    SERVER_TYPE_GATEWAY,
    SERVER_TYPE_LOGIN,
    SERVER_TYPE_ROLE,
    SERVER_TYPE_GAME,
    SERVER_TYPE_UTILITY,
    SERVER_TYPE_CHAT,
    SERVER_TYPE_GM,

    SERVER_TYPE_MAX
};

class YLH_Server_Info
{
public:
    YLH_Server_Info();


private:
    SERVER_TYPE     m_Server_Type;
};

//服务器监听信息， 从配置表读取
struct YLH_Acceptor_Info
{
    YLH_Acceptor_Info();

    void set_port(int port);

    bool    can_acceptor;
    int     acceptor_port;
};

//服务器链接信息， 从配置表读取
struct YLH_Connect_Info
{
    YLH_Connect_Info();

    int connect_port;
};

#endif  //YLH_SERVER_H_