#include "server.h"

Server::Server(bool flag){
    set("data.json");
    if(flag){
        show();
    }
    converIp();
}

Server::~Server(){};

// +++++++++++++++++++++++++++++++++++

void Server::Run(){
    setSocket();
    int addrlen = sizeof(m_address);

    while(true){
        if (listen(m_server_fd, 1) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        // *************************************
        std::cout << "Server listening on " << m_ipServer << ":" << m_portConfigServer << "\n";
        std::cout<<"["<<m_counter <<"] >> \n";
        int new_socket = accept(m_server_fd, (struct sockaddr *)&m_address, (socklen_t *)&addrlen);
         // *************************************
        // std::thread t(handleData, m_counter );
        // t.detach();
        // ~~~~~~~~~~~~~
        TestThread tmp;
        std::thread B(&TestThread::Run, &tmp, m_counter);
        B.detach();

        this->dataListIs.push_back(&tmp);
        // *************************************
       
        // *************************************
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        // *************************************
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        std::cout <<"["<< m_counter  <<"] Message from client: " << buffer << std::endl;
        std::string message(buffer);
        if(message =="c0"){
            this->dataListIs[0]->flag=false;
            std::cout<< "[[[[[[[[[[[]]]]]]]]]]]\n";
        }
        std::cout<<" ------------- \n ";
        close(new_socket);
        // *************************************
        m_counter +=1;
    }
}

// +++++++++++++++++++++++++++++++++++

void Server::set(string path){
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cerr << "Failed to open data.json" << std::endl;
        return;
    }

    if (f.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "File is empty!" << std::endl;
        return;
    }

    json data = json::parse(f);

    // std::ifstream f(path);
    // json data = json::parse(f);

    m_Username          = data["Username"];
    m_Password          = data["Password"];
    m_ipServer          = data["ipServer"];
    m_portConfigServer  = data["portConfigServer"];
    m_portChartServer   = data["portChartServer"] ;
}


void Server::show(){
    std::cout << " ------------------ "<<std::endl;
    std::cout << m_Username<< std::endl;
    std::cout << m_Password << std::endl;
    std::cout << m_ipServer << std::endl;
    std::cout << m_portConfigServer << std::endl;
    std::cout << m_portChartServer  << std::endl;
    std::cout << " ------------------ "<<std::endl;

}

void Server::converIp(){
    int result_ipv4 = inet_pton(AF_INET, m_ipServer.c_str(), &ipv4_addr);
    if (result_ipv4 == 1) {
        std::cout << "Successfully converted IPv4: " << m_ipServer << std::endl;
    } else if (result_ipv4 == 0) {
        std::cerr << "Invalid IPv4 address format: " << m_ipServer << std::endl;
    } else {
        perror("inet_pton for IPv4 failed"); 
    }
}

void Server::setSocket(){
    // ++++++++++++++++++++++++++++++++++++++++
    m_server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // ---------------------------------------------------
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr =  ipv4_addr.s_addr;
    m_address.sin_port = htons(m_portConfigServer);
    if (bind(m_server_fd, (struct sockaddr *)&m_address, sizeof(m_address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // ++++++++++++++++++++++++++++++++++++++++
}