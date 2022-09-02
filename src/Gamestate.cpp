#include "Gamestate.h"

Gamestate::Gamestate() {
    cur_point = 0;
    numCorrect = 0;
    time = 0.0;
    generate();
    active = true;
}
void Gamestate::show() {
#pragma omp critical
    {
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
    std::cout << "\nTime: " << time << "s";
    moveCursor(cur_point);
    std::cout << std::flush;
    }
    
}
void Gamestate::play() {
    char input;
    while (cur_point < paragraph.length()) {
        input = getch();
        parseInput(input);
    }
    active = false;
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
    std::vector<std::string> list = {"\"I'm collecting food for the winter,\" said the ant, \"and I suggest you do the same.\" And off she went, helping the other ants to carry food to their store. The grasshopper carried on hopping and singing. When winter came the ground was covered with snow. The grasshopper had no food and was hungry. So he went to the ants and asked for food.", "I expect to pass through this world but once; any good thing therefore that I can do, or any kindness that I can show to any fellow-creature, let me do it now; let me not defer or neglect it, for I shall not pass this way again.", "When I was a child, I spake as a child, I understood as a child, I thought as a child: but when I became a man, I put away childish things. For now we see through a glass, darkly; but then face to face: now I know in part; but then shall I know even as also I am known."};
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,list.size());
    paragraph = list[dist(rng) - 1];
}

void Gamestate::results() {
    // show();
    int numIncorrect = isAccurate.size() - numCorrect;
    double rawWPM = (double)isAccurate.size() / 5.0 / (time / 60.0); 
    double rawCPM = (double)isAccurate.size() / (time / 60.0); 
    double WPM = rawWPM - (double)numIncorrect / (time / 60.0);
    double CPM = rawCPM - (double)numIncorrect / (time / 60.0);
    if (WPM < 0) WPM = 0; // should not be negative
    double accuracy = (double)numCorrect / ((double)numCorrect + (double)numIncorrect) * 100;
    std::cout << "\n" << std::string(40,' ') << ("Test Results") << '\n';
    std::cout.precision(3);
    std::cout << "Words Per Minute: " << WPM << "WPM" << '\n';
    std::cout << "Characters Per Minute: " << CPM << "CPM" << '\n';
    std::cout << "Accuracy: " << accuracy << "%" << '\n';
    std::cout << "Correct: " << numCorrect << '\n';
    std::cout << "Incorrect: " << numIncorrect << '\n';
    std::cout << std::string(40,' ') << "You're fast at this!" << '\n';
}

void Gamestate::timer() {
    while (isRunning())
    {
        show();
        time += 0.1;
        std::this_thread::sleep_for(std::chrono::duration<double>(0.1));     
    }
}

bool Gamestate::isRunning() {
    return active;
}