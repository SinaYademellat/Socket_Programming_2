#ifndef server_H
#define server_H

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Server{
    public:
        Server(bool flag);
        ~Server();

        void Run();
        
    private:
        void set(string path);
        void show();
        
        void converIp();
        void setSocket();
        
        string m_Username;
        string m_Password;
        string m_ipServer;

        int m_portConfigServer;
        int m_portChartServer;

        struct in_addr ipv4_addr;
        struct sockaddr_in m_address;
        int m_server_fd;

        int m_counter = 0 ;

};


#endif
