#include "serverThread.h"

void handleData(int cmd_number) {
    std::cout << "[Thread " << cmd_number << "] Started\n";
    while(1){
    // Loop
    }  
    std::cout << "[Thread " << cmd_number << "] Finished\n";
}