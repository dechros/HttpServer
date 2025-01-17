#include "App.h"

App::App(int numArgs, char *argArray[]) : args(argArray, argArray + numArgs), logService("LogService")
{
}

App::~App()
{
}

void App::Run()
{
    logService.Start();
    for (int i = 0; i < 100; ++i)
    {
        logService.Log("Hello World!", "App");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    logService.Stop();
}