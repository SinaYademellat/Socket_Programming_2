#include "server.h"

Server::Server(string configPath, bool is_displayConfig)
{
    setUpConfig(configPath);
    if (is_displayConfig) {
        showConfig();
    }
}

Server::~Server() {}


void Server::setUpConfig(string path)
{
    json data;
    readConfigFile(path, data);
    assignConfigValues(data);
}

void Server::readConfigFile(string path, json& data)
{
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cerr << "Failed to open config file: " << path << std::endl;
        return;
    }

    if (f.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Config file is empty!" << std::endl;
        return;
    }

    try {
        data = json::parse(f);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return;
    }
}

void Server::assignConfigValues(const json& data)
{
    if (data.find("userName") != data.end()) {
        m_Username = data["userName"];
    } else {
        std::cerr << "userName not found in config file!" << std::endl;
    }
    // ++++++++++++++++++++++++++++++++++
    if (data.find("passWord") != data.end()) {
        m_Password = data["passWord"];
    } else {
        std::cerr << "passWord not found in config file!" << std::endl;
    }
    // ++++++++++++++++++++++++++++++++++
    if (data.find("ipServer") != data.end()) {
        m_ipServer = data["ipServer"];
    } else {
        std::cerr << "ipServer not found in config file!" << std::endl;
    }
    // ++++++++++++++++++++++++++++++++++
    if (data.find("portCmd") != data.end()) {
        m_portCMD = data["portCmd"];
    } else {
        std::cerr << "portCmd not found in config file!" << std::endl;
    }
}

void Server::showConfig()
{
    cout << " ------------------ " << endl;
    cout << "m_Username: " << m_Username << endl;
    cout << "m_Password: " << m_Password << endl;
    cout << " " << endl;
    cout << "m_ipServer: " << m_ipServer << endl;
    cout << "m_portCMD : " << m_portCMD << endl;
    cout << " ------------------ " << endl;
}
