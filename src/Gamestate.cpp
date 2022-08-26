#include "Gamestate.h"

Gamestate::Gamestate() {
    paragraph = "Sample";
    cur_point = 0;
    numCorrect = 0;
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
    std::cout << grey(paragraph.substr(cur_point));
}
void Gamestate::play() {
    generate();
    char input;
    while (cur_point < paragraph.length()) {
        show();
        input = getch();
        if (input == '\033') { // Handles arrow keys because arrow keys return three values
            getch();
            getch(); 
        }
        parseInput(input);
    }
    results();
}
void Gamestate::parseInput(char c) {
    if (c == paragraph[cur_point]) {
        cur_point++;
        isAccurate.push_back(true);
        numCorrect++;
    }
    else {
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
