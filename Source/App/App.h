#ifndef APP_H
#define APP_H

#include <vector>
#include <string>
#include "LogService.h"

class App
{
private:
    const std::vector<std::string> args;
    Services::LogService logService;

public:
    App(int numArgs, char *argArray[]);
    ~App();
    void Run();
};

#endif