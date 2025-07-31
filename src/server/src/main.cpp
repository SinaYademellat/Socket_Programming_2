#include <iostream>
#include "server.h"


int main(int argc, char const *argv[]){
        
    uint16_t PORT_SSL = 4443;
    uint16_t PORT_BroadCast =12345;

    string configPath = "data.json";
    bool is_displayConfig = false;

    Server serverObject(configPath , is_displayConfig);

    // +++++++++++++++++++++++++++
    bool is_Multiserver = false;
    // +++++++++++++++++++++++++++

    if(is_Multiserver){

        if(argc >= 3){
            int port_ = atoi(argv[2]);
            auto tmp = std::make_shared<TestThread>(-1);
            std::thread Thread_broadcast(std::bind(&TestThread::Run_BroadcastJson_codePart ,tmp,  argv[1]  , port_ )); // port 12345
            Thread_broadcast.detach();

        } else{
            auto tmp = std::make_shared<TestThread>(-1);
            std::thread Thread_broadcast(std::bind(&TestThread::Run_BroadcastJson_codePart ,tmp,  argv[1]  , 12345 ));
            Thread_broadcast.detach();
        }
        while (1)
        {
            /* code */
        }

    }
    else
    {
        // auto tmp = std::make_shared<TestThread>(-1);
        // std::thread Thread_broadcast(std::bind(&TestThread::Run_broadcast, tmp, PORT_BroadCast));
        // Thread_broadcast.detach();

        auto tmp = std::make_shared<TestThread>(-1);
        std::thread Thread_broadcast(std::bind(&TestThread::Run_BroadcastJson, tmp, PORT_BroadCast));
        Thread_broadcast.detach();
        
        if(argc >= 2){
            std::cout << " << SSL >>" <<std::endl;
            serverObject.Run_SSL(PORT_SSL);
        }
        else{
            std::cout << " << Normal >>" << std::endl;
            serverObject.Run();
        }
        
    }
    return 0;

}
