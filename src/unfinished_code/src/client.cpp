#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#define PORT 8080

int main() {
    struct sockaddr_in serv_addr;

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
      std::cerr << "Socket creation error" << std::endl;
      return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    const char IP[] = "127.0.0.5";

    
    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
      std::cerr << "Invalid address/ Address not supported" << std::endl;
      return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      std::cerr << "Connection Failed" << std::endl;
      return -1;
    }

    // Send data
    const char *Massage = "test Massage";
    send(sock, Massage, strlen(Massage), 0);
    std::cout << "Message sent!" << std::endl;

    close(sock);

    return 0;
}