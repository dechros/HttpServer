#include <iostream>
#include <string>
#include "ErrorService.h"

int main(int numArgs, char *argArray[])
{
    Services::ErrorService errorService("ErrorService");
    errorService.Start();
    errorService.LogError("Hello World!");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    errorService.Stop();
    return 0;
}