#include "Gamestate.h"

Gamestate::Gamestate() {
    cur_point = 0;
    numCorrect = 0;
    time = 0.0;
    active = true;
    generate();
}
void Gamestate::show() {
    cls();
    for (size_t i = 0; i < isAccurate.size();) {
        size_t curr = i;
        i++;
        for ( ; i < isAccurate.size() && isAccurate[i] == isAccurate[i-1]; i++) {
        }
        if (isAccurate[curr]) {
            std::cout << white(paragraph.substr(curr,i - curr));
        }
        else {
            std::cout << red(paragraph.substr(curr,i - curr));
        }
    }
    std::cout << paragraph.substr(cur_point,1);
    if (cur_point < paragraph.size()) std::cout << grey(paragraph.substr(cur_point+1));
    std::cout << "\nTime: " << time << "s";
    moveCursor(cur_point);
    std::cout << std::flush;
}
void Gamestate::play() {
    char input;
    while (cur_point < paragraph.length()) {
        input = getch();
        bool needReprint = parseInput(input);
        if (needReprint) {
            #pragma omp critical
            show();
        }
        else {
            #pragma omp critical
            if (isAccurate.back()) std::cout << white(paragraph.substr(cur_point - 1,1));
            else std::cout << red(paragraph.substr(cur_point - 1,1));
            std::cout << paragraph[cur_point];
            moveCursor(cur_point);
        }
        
    }
    active = false;
    results();
}
bool Gamestate::parseInput(char c) {
    if (c == '\t') return true;
    else if ((c == 127 || c == 8) ) { // backspace
        if (cur_point == 0) return true;
        cur_point --;
        if(isAccurate.back()) numCorrect--;
        isAccurate.pop_back();
        return true;
    }
    else if (c == '\033') { // Test for Esc, Del, arrow keys, home, end, pg up, pg dn characters
        char next = getch();
        if (next != '[') parseInput(next); 
        else {
            char nextnext = getch(); // home, end, arrow keys
            if (nextnext == '3' || nextnext == '5' || nextnext == '6') getch(); // Del, pg up, pg dn
            return true;
        }
    }
    else if (c == paragraph[cur_point]) {
        cur_point++;
        isAccurate.push_back(true);
        numCorrect++;
        return false;
    }
    else if (isprint(c)){ // Wrong character keyed in
        cur_point++;
        isAccurate.push_back(false);
        return false;
    }
    return true;
}
void Gamestate::generate() {
    std::vector<std::string> list = {
        "Call me Ishmael. Some years ago-never mind how long precisely-having little or no money in my purse, and nothing particular to interest me on shore, I thought I would sail about a little and see the watery part of the world.", 
        "I expect to pass through this world but once; any good thing therefore that I can do, or any kindness that I can show to any fellow-creature, let me do it now; let me not defer or neglect it, for I shall not pass this way again.", 
        "When I was a child, I spoke as a child, I understood as a child, I thought as a child: but when I became a man, I put away childish things. For now we see through a glass, darkly; but then face to face: now I know in part; but then shall I know even as also I am known.",
        "The 1910 Cuba hurricane was said to be one of the worst tropical cyclones that has ever hit Cuba. The storm formed in the southern Caribbean Sea on October 9, 1910.",
        "When on board H.M.S. 'Beagle,' as naturalist, I was much struck with certain facts in the distribution of the inhabitants of South America, and in the geological relations of the present to the past inhabitants of that continent.",
        "Christchurch Central Library was the largest library in the South Island and the third-biggest in New Zealand. It opened in 1982 on the corner of Oxford Terrace and Gloucester Street but was closed on the day of the 22 February 2011 Christchurch earthquake."
        };
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,list.size());
    paragraph = list[dist(rng) - 1];
}

void Gamestate::results() {
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
    std::cout << std::string(40,' ') << "You're fast!" << '\n';
}

void Gamestate::timer() {
    while (isRunning())
    {
        #pragma omp critical
        {
        moveCursor(paragraph.length() - 1);
        std::cout << "\r\033[1B" << "\033[K";
        std::cout << "Time: " << time << "s";
        moveCursor(cur_point);
        std::cout << std::flush;
        }   
        time += 0.01;
        std::this_thread::sleep_for(std::chrono::duration<double>(0.01));    
    }
}

bool Gamestate::isRunning() {
    return active;
}