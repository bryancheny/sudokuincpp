#ifndef OUTPUT_H_
#define OUTPUT_H_


#ifdef _WIN32
#include <conio.h>
#else
    #ifdef __linux__
    #include <termio.h>
    #include <cstdio>
    #elif __APPLE__
    #include <termios.h>
    #endif
    inline char getch(void)
    {
        struct termios tmtemp, tm;
        char c;
        int fd = 0;
        if (tcgetattr(fd, &tm) != 0)
        { 
            return -1;
        }
        tmtemp = tm;
        cfmakeraw(&tmtemp); 
        if (tcsetattr(fd, TCSANOW, &tmtemp) != 0)
        { 
            return -1;
        }
        c = getchar();
        if (tcsetattr(fd, TCSANOW, &tm) != 0)
        { 
            return 0;
        }
        return c;
    }
#endif

inline void cls(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif