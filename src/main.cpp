#include "output.h"
#include "Gamestate.h"
#include <thread>
#include <pthread.h>
#include <iomanip>

int main(int argc, char const *argv[])
{
    std::cout << std::setprecision(2) << std::fixed;
    #ifdef _WIN32
        cout << "hello Windows!!";
    #else 
        Gamestate game;
        game.show();
        #pragma omp parallel
        #pragma omp sections
        {
        #pragma omp section
              game.timer();
        #pragma omp section
              game.play();  
        }
    #endif
    return 0;
}
