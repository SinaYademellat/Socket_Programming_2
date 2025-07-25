#include "serverThread.h"


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
