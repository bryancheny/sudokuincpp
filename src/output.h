#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <string>
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h> 
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
// you can loop k higher to see more color choices
for(int k = 1; k < 255; k++)
{
// pick the colorattribute k you want
SetConsoleTextAttribute(hConsole, k);
cout << k << " I want to be nice today!" << endl;
}
#else
    #ifdef __linux__
    #include <termio.h>
    #include <cstdio>
    #include <sys/ioctl.h>
    #include <unistd.h>
    #elif __APPLE__
    #include <termios.h>
    #include <sys/ioctl.h> 
    #include <unistd.h> 
    #endif 
    // Add getch function to replace 
    void initTermios(int echo);
    void resetTermios(void);
    char getch_(int echo);
    char getch(void);
    char getche(void);
#endif

inline void moveCursor(size_t pos) {
    
    #ifndef _WIN32
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); 
    std::cout << "\033[" << std::to_string (pos/w.ws_col + 1) << ";" << std::to_string(pos%w.ws_col + 1) << "f";
    #endif
}

inline void cls(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline std::string grey(std::string str) 
{
#ifndef _WIN32
    return "\033[90m" + str + "\033[0m";
#else
    SetConsoleTextAttribute(hConsole, 8);
    return str;
#endif
}

inline std::string white(std::string str) 
{
#ifndef _WIN32
    return "\033[100m" + str + "\033[0m";
#else
    SetConsoleTextAttribute(hConsole, 15);
    return str;
#endif
}

inline std::string red(std::string str) 
{
#ifndef _WIN32
    return "\033[91m" + str + "\033[0m";
#else
    SetConsoleTextAttribute(hConsole, 12);
    return str;
#endif
}


#endif
