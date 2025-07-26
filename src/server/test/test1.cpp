#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>


int main(int argc, char const *argv[])
{
    struct sockaddr_in serv_addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
      std::cerr << "Socket creation error" << std::endl;
      return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
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
    std::cout<<"argc: "<<argc<<std::endl;
    if(argc >= 2){
      const char *Massage = argv[1];
      send(sock, Massage, strlen(Massage), 0);
      std::cout << "Message sent!" << std::endl;
    }
    else{    
      const char *Massage = "test Massage";
      send(sock, Massage, strlen(Massage), 0);
      std::cout << "Message sent!" << std::endl;
    }
    close(sock);
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
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8081);

    // بایند کردن سوکت به آدرس و پورت
    if (bind(UDPSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    std::cout << "Server listening on port " << 8081 << "..." << std::endl;

    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    while (true) {
        // دریافت داده از کلاینت
        int received_len = recvfrom(UDPSocket, buffer, 1024, 0, (struct sockaddr *)&client_addr, &client_len);
        if (received_len < 0) {
            std::cerr << "recvfrom failed" << std::endl;
            continue;
        }

        std::cout << "Received message: " << buffer << std::endl;
    }




    return 0;
}