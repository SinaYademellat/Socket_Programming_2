#include "server.h"
#include <iostream>


int main(int argc, char const* argv[])
{
    string config_path       = "server-test.json";
    bool   is_display_config = true;

    Server server_object(config_path, is_display_config);

    return 0;
}
