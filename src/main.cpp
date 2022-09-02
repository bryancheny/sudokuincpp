#include "output.h"
#include "Gamestate.h"
#include <thread>
#include <pthread.h>

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
              game.timer();
        #pragma omp section
              game.play();  
        }
    #endif
    return 0;
}
