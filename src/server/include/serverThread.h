#ifndef serverThread_H
#define serverThread_H
#include <iostream>
#include <string>

class TestThread{
    public:
        TestThread(int id);
        void Run(int cmd_number);
        bool flag = true;

        void showInfo();
    private:
        int Id;
};

#endif