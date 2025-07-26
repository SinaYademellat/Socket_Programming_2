#include "serverThread.h"


TestThread::TestThread(int id){
    this->m_flag = true;
    this->m_id   = id;
}

void TestThread::Run(int cmd_number){
    std::cout << "[Thread " << cmd_number << "] Started\n";
    
    this->setDataSocket("127.0.0.5" , 8081);

    int counter_Packet = 1;
    std::string massag = "testPacket";
    while((this->m_flag)&&(counter_Packet<10)){
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