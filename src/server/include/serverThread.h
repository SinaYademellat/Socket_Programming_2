#ifndef serverThread_H
#define serverThread_H
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class TestThread{
    public:
        TestThread(int id);

        void Run(int cmd_number);
        void showInfo();
        bool m_flag = true;

    private:
        
        void setDataSocket(std::string server_ip,uint16_t data_port);
        void setPacket(int header , std::string message);
        void sendPacket();

        int m_Id;
        int m_data_socket;

        int m_packet_index = 0;
        sockaddr_in m_server_addr{};
        unsigned char m_packet[512];
};

#endif