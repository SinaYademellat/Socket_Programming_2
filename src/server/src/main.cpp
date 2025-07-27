#include <iostream>
#include "server.h"

int main(int argc, char const *argv[]){
    
    string configPath = "data.json";
    bool is_displayConfig = true;
    Server s(configPath , is_displayConfig);
    s.Run();
    
    // if(argc >= 2){
    //     s.Run_SSL(4443);
    // }
    // else{
    //     s.Run();
    // }

    return 0;
}
