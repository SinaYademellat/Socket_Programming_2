#ifndef server_H
#define server_H

#include <arpa/inet.h>

#include <cstring>
#include <fstream>
#include <iostream>

#include <netinet/in.h>
#include <nlohmann/json.hpp>

#include <string>

using namespace std;
using json = nlohmann::json;

class Server
{
public:
    Server(string configPath, bool is_displayConfig);
    ~Server();

private:
    // phase-1 : << Setup >>
    void setUpConfig(string path);
    void readConfigFile(string path, json& data);
    void assignConfigValues(const json& data);
    void showConfig();

    // ------------------------------
    string m_Username;
    string m_Password;
    string m_ipServer;
    int    m_portCMD;
};

#endif // ifndef server_H
