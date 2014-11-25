


//���������࣬ ���еķ��������ɴ�����
//����
//1.������������Ϣ
//2.�������
//3.���ݿ����
//4.��־����


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

    //������Ϣ
    virtual void collect_msg(char* recvbuf, int buff_size) = 0;


    void del_handler(YLH_Sock_Handler* handler);
private:
    YLH_Net_Manager*    m_Net_Manager;  //����
    YLH_Server_Info*    m_Server_Info;  //������������Ϣ
    YLH_Log_Manager*    m_Log_Manager;  //��־
    YLH_DB_Manager*     m_DB_Manager;   //���ݿ�
};



#endif  //_YLH_SERVER_H_
