#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <thread>


#define PORT 8080

void handleCMD(int cmd_number) {
    std::cout << "[Thread " << cmd_number << "] Started\n";
    while(1){
    // Loop
    }  
    std::cout << "[Thread " << cmd_number << "] Finished\n";
}


int main() {
    std::string ipv4_str = "127.0.0.5";

    struct in_addr ipv4_addr;
    int result_ipv4 = inet_pton(AF_INET, ipv4_str.c_str(), &ipv4_addr);
    if (result_ipv4 == 1) {
        std::cout << "Successfully converted IPv4: " << ipv4_str << std::endl;
    } else if (result_ipv4 == 0) {
        std::cerr << "Invalid IPv4 address format: " << ipv4_str << std::endl;
    } else {
        perror("inet_pton for IPv4 failed"); 
    }

    // ++++++++++++++++++++++++++++++++++++++++
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // ---------------------------------------------------
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr =  ipv4_addr.s_addr;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // ++++++++++++++++++++++++++++++++++++++++
    
    int counter = 0;
    std::cout << "Server listening on " << ipv4_str << ":" << PORT << "\n";

    while(true){
        if (listen(server_fd, 1) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        // *************************************
        std::cout<<"["<<counter <<"] >> \n";
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        // *************************************
        std::thread t(handleCMD, counter );
        t.detach();
        // *************************************
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        // *************************************
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        std::cout <<"["<< counter  <<"] Message from client: " << buffer << std::endl;
        std::cout<<" ------------- \n ";
        close(new_socket);
        // *************************************
        counter +=1 ;
    }

    return 0;
}

