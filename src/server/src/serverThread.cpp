#include "serverThread.h"


TestThread::TestThread(int id){
    this->flag = true;
    this->Id   = id;
}

void TestThread::Run(int cmd_number){
    std::cout << "[Thread " << cmd_number << "] Started\n";
    while(this->flag){
    // Loop
    }  
    std::cout << "[Thread " << cmd_number << "] Finished\n";
}

void TestThread::showInfo(){
    std::cout<<"Id:"<<Id<<std::endl;
}