#include "Gamestate.h"

Gamestate::Gamestate() {
    cur_point = 0;
    numCorrect = 0;
    time = 0.0;
    generate();
}
void Gamestate::show() {
    cls();
    for (size_t i = 0; i < isAccurate.size(); i++) {
        if (isAccurate[i]) {
            std::cout << white(paragraph.substr(i,1));
        }
        else {
            std::cout << red(paragraph.substr(i,1));
        }
    }
    std::cout << paragraph.substr(cur_point,1);
    if (cur_point < paragraph.size()) std::cout << grey(paragraph.substr(cur_point+1));
    std::cout << "\n";
    std::cout << "Time: " << time << "\n" << "\n";
    moveCursor(cur_point);
    
}
void Gamestate::play() {
    char input;
    while (cur_point < paragraph.length()) {
        show();
        input = getch();
        parseInput(input);
    }
    results();
}
void Gamestate::parseInput(char c) {
    if (c == '\t') return;
    else if ((c == 127 || c == 8) ) { // backspace
        if (cur_point == 0) return;
        cur_point --;
        if(isAccurate.back()) numCorrect--;
        isAccurate.pop_back();
    }
    else if (c == '\033') { // Test for Esc, Del, arrow keys, home, end, pg up, pg dn characters
        char next = getch();
        if (next != '[') parseInput(next); 
        else {
            char nextnext = getch(); // home, end, arrow keys
            if (nextnext == '3' || nextnext == '5' || nextnext == '6') getch(); // Del, pg up, pg dn
        }
    }
    else if (c == paragraph[cur_point]) {
        cur_point++;
        isAccurate.push_back(true);
        numCorrect++;
    }
    else if (isprint(c)){ // Wrong character keyed in
        cur_point++;
        isAccurate.push_back(false);
    }
}
void Gamestate::generate() {
    paragraph = "This text will be replaced by something better and randomly generated I promise!";
}

void Gamestate::results() {
    show();
    std::cout << "\n" << std::string(40,' ') << ("Test Results") << '\n';
    std::cout << "Correct: " << numCorrect << '\n';
    std::cout << "Incorrect: " << isAccurate.size() - numCorrect << '\n';
}

void Gamestate::timer() {
    
    while (true)
    {
#pragma omp critical
        time += 0.1;
        std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
        show();
    }
}
