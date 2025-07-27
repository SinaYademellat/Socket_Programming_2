#include <iostream>
#include "server.h"

int main(int argc, char const *argv[]){
    
    string configPath = "data.json";
    bool is_displayConfig = false;

    Server serverObject(configPath , is_displayConfig);
    if(argc >= 2){
        std::cout << " << SSL >>" <<std::endl;
        serverObject.Run_SSL(4443);
    }
    else{
        std::cout << " << Normal >>" << std::endl;
        serverObject.Run();
    }
    return 0;
}
