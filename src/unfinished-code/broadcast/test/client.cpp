#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>


int main(int argc, char const *argv[])
{
    int UDPSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (UDPSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
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