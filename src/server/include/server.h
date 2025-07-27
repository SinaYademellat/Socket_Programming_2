#ifndef server_H
#define server_H

#include <iostream>
#include <string>
#include <cstring>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <fstream>

#include <vector>
#include <nlohmann/json.hpp>

#include <memory>

// Openssl
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
// --------

#include "serverThread.h"


using namespace std;
using json = nlohmann::json;

class Server{
    public:
        Server(string configPath, bool is_displayConfig);
        ~Server();

        void Run();
        void Run_SSL(uint16_t PORT);
        
    private:

        void setUpConfig(string path);
        void readConfigFile(string path, json& data);
        void assignConfigValues(const json& data);

        void showConfig();
        
        void createCmdSocket ();
        void convertIpToIPv4();
        int  createTcpSocket();
        void bindCmdSocket();

        void processClientCommand(const string& message);

        // ++++++++++++++++++++++++++++
        void InitSSL();
        SSL_CTX* CreateContext();
        void ConfigureContext(SSL_CTX* ctx);
        // . . . . . . .  . . .
        SSL_CTX* m_ctx;
        // // ------------------------------
        
        string m_Username;
        string m_Password;
        string m_ipServer;

        int m_portConfigServer;
        int m_portChartServer;

        struct in_addr ipv4_addr;
        struct sockaddr_in m_address;
        int m_server_fd;

        int m_counter = 0 ;

        std::vector<std::shared_ptr<TestThread>> m_dataListIs;

};


#endif
