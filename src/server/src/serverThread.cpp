#include "serverThread.h"


TestThread::TestThread(int id){
    this->m_flag = true;
    this->m_id   = id;
}

void TestThread::Run(int cmd_number){
    std::cout << "[Thread " << cmd_number << "] Started\n";
    
    this->setDataSocket("127.0.0.5" , 8081);

    int counter_Packet = 1;


    while((this->m_flag)&&(counter_Packet<=5)){
        // 
        std::string p1 = "testPacket_";
        std::string p2 = std::to_string(counter_Packet); 
        std::string massag = p1 + p2; 
        /// 
        this->setPacket(counter_Packet , massag);
        this->sendPacket();
        counter_Packet+=1;
    }

    close(m_data_socket);
    std::cout << "[Thread " << cmd_number << "] Finished\n";
}

void TestThread::showInfo(){
    std::cout<<"Id:"<<m_id<<std::endl;
}

void TestThread::setDataSocket(std::string server_ip, uint16_t data_port){
    this->m_data_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_data_socket < 0) {
        perror("socket");
    } 

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(data_port); 
    inet_pton(AF_INET, server_ip.c_str(), &m_server_addr.sin_addr);

}


void TestThread::setPacket(int header , std::string message){

    m_packet_index = 0;

    memcpy(this->m_packet + m_packet_index, &header, sizeof(header));
    m_packet_index += sizeof(header);

    memcpy(this->m_packet + m_packet_index, message.c_str(), message.size());
    m_packet_index += message.size();
}

void TestThread::sendPacket(){

    ssize_t sent_bytes = sendto(m_data_socket, this->m_packet, m_packet_index, 0,
                                (sockaddr*)&m_server_addr, sizeof(m_server_addr));

    if (sent_bytes < 0) {
        perror("sendto");
        close(m_data_socket);
    }
    std::cout << "Packet sent (" << sent_bytes << " bytes)" << std::endl;

}

// -------------------------------------
void TestThread::setBroadcastSocket(){

    // Create UDP socket
    m_broadcast_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_broadcast_socket < 0) {
        std::cerr << "Error creating socket" << std::endl;
    }

    // Enable broadcast option
    int broadcast_enable = 1;
    if (setsockopt(m_broadcast_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0) {
        std::cerr << "Error setting broadcast option" << std::endl;
        close(m_broadcast_socket);
    }
}

void TestThread::Run_broadcast(uint16_t Port){
    
    this->setBroadcastSocket();

    struct sockaddr_in broadcast_addr;
    char message[] = "code << Server >>  127.0.0.5:8081";

    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(12345);
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST; // Universal broadcast

    while (this->m_flag)
    {
        if (sendto(m_broadcast_socket, message, sizeof(message), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            std::cerr << "Error sending broadcast message" << std::endl;
            close(m_broadcast_socket);
        }
        // std::cout << "Broadcast message sent!" << std::endl;
    }
   
    close(m_broadcast_socket);
}

void TestThread::Run_BroadcastJson(uint16_t Port){
    
    this->setBroadcastSocket();

    struct sockaddr_in broadcast_addr;
    
    nlohmann::json request_data = {
        {"Code", "nopassword"},
        {"Ip", "127.0.0.5"},
        {"Port", 8081},
    };

    // Convert 
    std::string json_string = request_data.dump();
    std::cout<< " ^^^^^^^^^^^^^^^^^^^^^^^ " <<std::endl;
    std::cout<<" Json_string: "<< json_string << std::endl;
    std::cout<< " vvvvvvvvvvvvvvvvvvvvvvv " <<std::endl;
    // return;
    // char message[] = "code << Server >>  127.0.0.5:8081";
    const char *message = json_string.c_str();

    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(12345);
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST; // Universal broadcast

    while (this->m_flag)
    {
        if (sendto(m_broadcast_socket, message, strlen(message), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            std::cerr << "Error sending broadcast message" << std::endl;
            close(m_broadcast_socket);
        }
        // std::cout << "Broadcast message sent!" << std::endl;
    }
   
    close(m_broadcast_socket);
}




void TestThread::Run_BroadcastJson_codePart( std::string servercode , uint16_t Port){
    
    this->setBroadcastSocket();

    struct sockaddr_in broadcast_addr;
    
    nlohmann::json request_data = {
        {"Code", servercode},
        {"Ip", "127.0.0.5"},
        {"Port", 8081},
    };

    // Convert 
    std::string json_string = request_data.dump();
    std::cout<< " ^^^^^^^^^^^^^^^^^^^^^^^ " <<std::endl;
    std::cout<<" Json_string: "<< json_string << std::endl;
    std::cout<< " vvvvvvvvvvvvvvvvvvvvvvv " <<std::endl;
    // return;
    // char message[] = "code << Server >>  127.0.0.5:8081";
    const char *message = json_string.c_str();

    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(Port);
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST; // Universal broadcast

    while (this->m_flag)
    {
        if (sendto(m_broadcast_socket, message, strlen(message), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            std::cerr << "Error sending broadcast message" << std::endl;
            close(m_broadcast_socket);
        }
        // std::cout << "Broadcast message sent!" << std::endl;
    }
   
    close(m_broadcast_socket);
}




