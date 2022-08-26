#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <string> 
#include <iostream> 

class Gamestate {
    public:
        Gamestate::Gamestate();
        void show();
        void play();
        void parseInput();
        void generate();
        void restart();
    private:
        std::string paragraph;
        int cur_point;
        int cur_correct_point;
};
#endif