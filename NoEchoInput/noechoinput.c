#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#elif __linux__
#include <termios.h>
#include <unistd.h>
#endif

int main()
{
    char sentence[30];
    printf("The input will not echo\n");
    printf("Please enter some text 30 characters max : ");

#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
#elif __linux__
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif

    fscanf(stdin, " %[^\n]s", sentence);
    printf("\nYour input was: \"%s\"\n", sentence);

#ifdef _WIN32
    SetConsoleMode(hStdin, mode & (ENABLE_ECHO_INPUT));
#elif
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt);
#endif

    return 0;
}
