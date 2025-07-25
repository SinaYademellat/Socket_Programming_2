#ifndef serverThread_H
#define serverThread_H
#include <iostream>

class TestThread{
    public:
        TestThread();
        void Run(int cmd_number);
        bool flag = true;
};

#endif