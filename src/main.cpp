#include "output.h"
#include "Gamestate.h"
#include <thread>
#include "timer.h"

int main(int argc, char const *argv[])
{
    #ifdef _WIN32
        cout << "hello Windows!!";
    #else 
        Gamestate game;
        #pragma omp parallel
        #pragma omp sections
            {
        #pragma omp section
              game.play();
        #pragma omp section
              
              game.timer();
            }
    #endif
    return 0;
}
