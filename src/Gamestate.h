#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <string> 
#include <iostream> 
#include <vector>
#include "output.h"
#include <thread>
#include <random>

class Gamestate {
    public:
        Gamestate();
        void show();
        void play();
        void parseInput(char c);
        void generate();
        void results();
        void timer();
        bool isRunning();
    private:
        std::string paragraph;
        size_t cur_point;
        std::vector<bool> isAccurate;
        int numCorrect;
        double time;
        bool active;
};
#endif