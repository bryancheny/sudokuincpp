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
    #elif __APPLE__
    #include <termios.h>
    #endif
#endif

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
