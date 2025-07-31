#include <iostream>
#include "server.h"


int main(int argc, char const *argv[]){
        
    uint16_t PORT_SSL = 4443;
    uint16_t PORT_BroadCast = 12345;

    string configPath = "server-1.json";

    bool is_displayConfig = false;
    bool is_SSL = false ;

    Server serverObject(configPath , is_displayConfig);

    // arg[1] --> code
    auto tmp = std::make_shared<TestThread>(-1);
    std::thread Thread_broadcast(std::bind(&TestThread::Run_BroadcastJson_codePart ,tmp,  argv[1]  , 12345 ));
    Thread_broadcast.detach();
    if(is_SSL){
        std::cout << " << SSL >>" <<std::endl;
        serverObject.Run_SSL(PORT_SSL);
    }
    else{
        std::cout << " << Normal >>" << std::endl;
        serverObject.Run();
    }
        
    return 0;

}
