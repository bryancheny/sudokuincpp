#include <iostream> 
#include "output.h"

int main(int argc, char const *argv[])
{
    std::cout << "This text will be erased.\n";
    cls();
    #ifdef _WIN32
        std::cout << "hello Windows!!";
    #else 
        std::cout << "Hello Apple/Linux!";
    #endif
    return 0;
}
