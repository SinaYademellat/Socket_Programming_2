#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    // ++++++++++++++++++++++++++
    //  UDP
    // ++++++++++++++++++++++++++

    int UDPSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (UDPSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    // ===================================================
    string m_ipServer = "0.0.0.0";
    struct in_addr ipv4_addr;


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

    // server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_addr.s_addr = ipv4_addr.s_addr;

    // ===================================================
    server_addr.sin_port = htons(12345);

    if (bind(UDPSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    std::cout << "Server listening on port " << 12345 << "..." << std::endl;

    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    int index_J ;
    for (index_J = 1 ; index_J< 5 ; index_J++) {
        
        std::cout<<"$ "<<index_J<<" $  ";
        int received_len = recvfrom(UDPSocket, buffer, 1024, 0, (struct sockaddr *)&client_addr, &client_len);
        if (received_len < 0) {
            std::cerr << " recvfrom failed" << std::endl;
            continue;
        }

        std::cout << "Received message: " << buffer << std::endl;
    }
    return 0;
}