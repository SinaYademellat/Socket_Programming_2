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
#include <vector>

#include "serverThread.h"


using namespace std;
using json = nlohmann::json;

class Server{
    public:
        Server(string configPath, bool is_displayConfig);
        ~Server();

        void Run();
        
    private:

        void setUpConfig(string path);
        void readConfigFile(string path, json& data);
        void assignConfigValues(const json& data);

        void showConfig();
        
        void createCmdSocket ();
        void convertIpToIPv4();
        int  createTcpSocket();
        void bindCmdSocket();

        
        string m_Username;
        string m_Password;
        string m_ipServer;

        int m_portConfigServer;
        int m_portChartServer;

        struct in_addr ipv4_addr;
        struct sockaddr_in m_address;
        int m_server_fd;

        int m_counter = 0 ;

        vector< TestThread *> dataListIs;
};


#endif
