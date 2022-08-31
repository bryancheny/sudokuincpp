#ifndef _TIMER_H_
#define _TIMER_H
#include "output.h"
    void timer() {
        int time = -1;
        while (true)
    {
#pragma omp critical
        {
        
        time += 1;
        std::cout << "\n" << time;  
        }
        std::this_thread::sleep_for(std::chrono::duration<double>(1));   
    }
    }
#endif