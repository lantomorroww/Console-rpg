#include "utils/Input.h"
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

char getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return static_cast<char>(ch);
}

void clearScreen() {
    // ANSI escape — быстрее, чем system("clear")
    std::cout << "\033[2J\033[1;1H" << std::flush;
}