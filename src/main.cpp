#include "output.h"
#include "Gamestate.h"

int main(int argc, char const *argv[])
{
    std::cout << "This text will be erased.\n";
    cls();
    #ifdef _WIN32
        cout << "hello Windows!!";
    #else 
        std::cout << grey("This text is grey.");
        std::cout << white("This text is white.");
        std::cout << red("This text is red.\n");
        Gamestate game;
        game.play();
    #endif
    return 0;
}
