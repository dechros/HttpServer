#include <iostream>
#include <string>
#include "Server.h"

int main(int numArgs, char *argArray[])
{
    Core::Server server(numArgs, argArray);

    try
    {
        server.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}