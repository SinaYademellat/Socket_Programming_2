#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <nlohmann/json.hpp>


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
    // ************************************** JSON
    nlohmann::json request_data = {
        {"key1", "value1"},
        {"key2", 123},
    };

    // Convert 
    std::string json_string = request_data.dump();
    
    std::cout<< " ^^^^^^^^^^^^^^^^^^^^^^^ " <<std::endl;
    std::cout<<" Json_string: "<< json_string << std::endl;
    std::cout<< " vvvvvvvvvvvvvvvvvvvvvvv " <<std::endl;

    const char *Massage = json_string.c_str();
    send(sock, Massage, strlen(Massage), 0);
    std::cout << "Message sent!" << std::endl;

    // ************************************** JSON



    close(sock);
    // ++++++++++++++++++++++++++
    //  UDP
    // ++++++++++++++++++++++++++
    return 0;
}