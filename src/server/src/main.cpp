#include <iostream>
#include "server.h"

int main(int argc, char const *argv[]){
    
    string configPath = "data.json";
    bool is_displayConfig = true;
    Server s(configPath , is_displayConfig);
    s.Run();

    return 0;
}
