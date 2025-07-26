#include "server.h"

Server::Server(string configPath , bool is_displayConfig){
    setUpConfig(configPath);
    if(is_displayConfig){
        showConfig();
    }   
}

Server::~Server(){};

// +++++++++++++++++++++++++++++++++++
void Server::Run(){
    
    createCmdSocket();
    int addrlen = sizeof(m_address);

    while(true){
        if (listen(m_server_fd, 1) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        // *************************************
        std::cout << "Server listening on " << m_ipServer << ":" << m_portConfigServer << "\n";
        std::cout<<"["<<m_counter <<"] >> \n";
        //  ------------------------------
        int new_socket = accept(m_server_fd, (struct sockaddr *)&m_address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
         // *************************************
        auto tmp = std::make_shared<TestThread>(m_counter);
        std::thread T(std::bind(&TestThread::Run, tmp, m_counter));
        T.detach();
        this->m_dataListIs.push_back(tmp);
        // *************************************
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        string message(buffer);

        // cout <<"["<< m_counter  <<"] Message from client: " << message << endl;

        close(new_socket);
        // *************************************
        processClientCommand(message);
        m_counter +=1;
        // *************************************
        cout<<" ------------- \n ";

    }
}

// +++++++++++++++++++++++++++++++++++

void Server::setUpConfig(string path) {
    json data;
    readConfigFile(path, data);
    assignConfigValues(data);
}

void Server::readConfigFile(string path, json& data) {
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

void Server::assignConfigValues(const json& data) {
    // ++++++++++++++++++++++++++++++++++
    if (data.find("Username") != data.end())
        m_Username = data["Username"];
    else
        std::cerr << "Username not found in config file!" << std::endl;
    // ++++++++++++++++++++++++++++++++++
    if (data.find("Password") != data.end())
        m_Password = data["Password"];
    else
        std::cerr << "Password not found in config file!" << std::endl;
    // ++++++++++++++++++++++++++++++++++
    if (data.find("ipServer") != data.end())
        m_ipServer = data["ipServer"];
    else
        std::cerr << "ipServer not found in config file!" << std::endl;
    // ++++++++++++++++++++++++++++++++++
    if (data.find("portConfigServer") != data.end())
        m_portConfigServer = data["portConfigServer"];
    else
        std::cerr << "portConfigServer not found in config file!" << std::endl;
    // ++++++++++++++++++++++++++++++++++
    if (data.find("portChartServer") != data.end())
        m_portChartServer = data["portChartServer"];
    else
        std::cerr << "portChartServer not found in config file!" << std::endl;
}

void Server::showConfig(){
    cout << " ------------------ "<<endl;
    cout << m_Username<< endl;
    cout << m_Password << endl;
    cout << m_ipServer << endl;
    cout << m_portConfigServer << endl;
    cout << m_portChartServer  << endl;
    cout << " ------------------ "<<endl;

}

// ***************************

void Server::createCmdSocket(){
    convertIpToIPv4();
    m_server_fd = createTcpSocket();
    bindCmdSocket();
}

void Server::convertIpToIPv4(){
    int result_ipv4 = inet_pton(AF_INET, m_ipServer.c_str(), &ipv4_addr);
    if (result_ipv4 == 1) {
        cout << "Successfully converted IPv4: " << m_ipServer << endl;
    } else if (result_ipv4 == 0) {
        cerr << "Invalid IPv4 address format: " << m_ipServer << endl;
        exit(EXIT_FAILURE);
    } else {
        perror("inet_pton for IPv4 failed"); 
        exit(EXIT_FAILURE);
    }
    
}

int Server::createTcpSocket() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    return server_fd;
}

void Server::bindCmdSocket() {
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = ipv4_addr.s_addr;
    m_address.sin_port = htons(m_portConfigServer);

    if (bind(m_server_fd, (struct sockaddr *)&m_address, sizeof(m_address)) < 0){
        perror("Bind failed");
        close(m_server_fd);
        exit(EXIT_FAILURE);
    }
}


void Server::processClientCommand(const std::string& message) {
    cout<<"$: ";

    if (message == "ls") {
        std::cout << "Listing all threads:\n";
        for (int i = 0; i < this->m_dataListIs.size(); i++) {
            std::cout << "Thread index [" << i << "] : ";
            this->m_dataListIs[i]->showInfo();
        }
    }
    else if (message == "stop-0"){
        this->m_dataListIs[0]->m_flag = false;
    }
    else {
        std::cout << "Unknown command: " << message << std::endl;
    }
}
