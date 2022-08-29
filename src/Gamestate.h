#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <string> 
#include <iostream> 
#include <vector>
#include "output.h"
#include <thread>

class Gamestate {
    public:
        Gamestate();
        void show();
        void play();
        void parseInput(char c);
        void generate();
        void restart();
        void results();
        void timer();
    private:
        std::string paragraph;
        size_t cur_point;
        std::vector<bool> isAccurate;
        int numCorrect;
        double time;
};
#endif