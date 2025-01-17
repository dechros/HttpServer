#include <iostream>
#include <string>
#include "LogService.h"

int main(int numArgs, char *argArray[])
{
    Services::LogService LogService("LogService");
    LogService.Start();
    for (int i = 0; i < 20000000000; i++)
    {
        LogService.Log("Hello World!", "main");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    LogService.Stop();
    return 0;
}