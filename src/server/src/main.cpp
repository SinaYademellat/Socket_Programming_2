#include <iostream>
#include "server.h"

int main(int argc, char const *argv[]){
    
    string configPath = "data.json";
    bool is_displayConfig = true;
    Server A(configPath , is_displayConfig);
    A.Run();

    return 0;
}
