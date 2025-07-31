#ifndef serverThread_H
#define serverThread_H
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <nlohmann/json.hpp>


class TestThread{
    public:
        TestThread(int id);

        void Run(int cmd_number);
        void showInfo();

        // ----------------------
        void Run_broadcast(uint16_t Port);
        void Run_BroadcastJson(uint16_t Port);
        
        void Run_BroadcastJson_codePart( std::string servercode , uint16_t Port = 12345);

        int m_broadcast_socket;
        // ---------------------

        bool m_flag = true;

    private:
        
        void setDataSocket(std::string server_ip,uint16_t data_port);
        void setPacket(int header , std::string message);
        void sendPacket();


        void setBroadcastSocket();

        int m_id;
        int m_data_socket;

        int m_packet_index = 0;
        sockaddr_in m_server_addr{};
        unsigned char m_packet[512];
};

#endif