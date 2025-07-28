#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in broadcast_addr;
    char message[] = "code << Server >>  127.0.0.5:8081";

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Enable broadcast option
    int broadcast_enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0) {
        std::cerr << "Error setting broadcast option" << std::endl;
        close(sockfd);
        return 1;
    }

    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(12345);
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST; // Universal broadcast

    while (1)
    {
        if (sendto(sockfd, message, sizeof(message), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            std::cerr << "Error sending broadcast message" << std::endl;
            close(sockfd);
            return 1;
        }

        std::cout << "Broadcast message sent!" << std::endl;

    }
   
    close(sockfd);
    return 0;
}