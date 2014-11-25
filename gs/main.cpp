

#include "Game_Server.h"
#include "ace/OS_main.h"

bool ret()
{
    return false;
}


bool ret1()
{
    return true;
}
int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
    Game_Server game_server;
    game_server.Init();

    YLH_Acceptor_Info acceptor_info;
    acceptor_info.set_port(GAME_SERVER_ACCEPT_PORT);
    game_server.Open_Accept(acceptor_info);
    game_server.Run();

    //game_server.close();


    return 0;
};