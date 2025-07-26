#ifndef serverThread_H
#define serverThread_H
#include <iostream>

class TestThread{
    public:
        TestThread();
        void Run(int cmd_number);
        bool flag = true;
};

void handleData(int cmd_number) ;

#endif