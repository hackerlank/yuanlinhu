

#include "Role_Server.h"
#include "ace/OS_main.h"
#include "YLH_Net_Manager.h"

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
    Role_Server role_server;
    role_server.Init();
    role_server.open_server();

    YLH_Connect_Info connector_info;
    connector_info.connect_port = (GAME_SERVER_ACCEPT_PORT);
    role_server.get_net_manager()->add_connnection_info(connector_info);

    role_server.get_net_manager()->open();
    //if (-1 == role_server.open_server(connector_info))
    //{
    //    return -1;
    //}
    //
    role_server.Run();

    //role_server.close();
    return 0;
};