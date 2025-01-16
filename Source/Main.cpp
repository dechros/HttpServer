#include <iostream>
#include <string>
#include "ErrorService.h"

int main(int numArgs, char *argArray[])
{
    Services::ErrorService errorService("ErrorService");
    errorService.Start();
    for (int i = 0; i < 15; i++)
    {
        errorService.LogError("Hello World!", "main");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    errorService.Stop();
    return 0;
}