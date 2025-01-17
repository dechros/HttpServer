#include <iostream>
#include <string>
#include "App.h"

int main(int numArgs, char *argArray[])
{
    App app(numArgs, argArray);
    app.Run();
    return 0;
}