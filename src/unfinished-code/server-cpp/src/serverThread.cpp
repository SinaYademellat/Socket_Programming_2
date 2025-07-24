#include "serverThread.h"

void handleData(int cmd_number) {
    std::cout << "[Thread " << cmd_number << "] Started\n";
    while(1){
    // Loop
    }  
    std::cout << "[Thread " << cmd_number << "] Finished\n";
}

TestThread::TestThread(){
    this->flag = true;
}

void TestThread::Run(int cmd_number){
    std::cout << "[Thread " << cmd_number << "] Started\n";
    while(this->flag){
    // Loop
    }  
    std::cout << "[Thread " << cmd_number << "] Finished\n";
}
