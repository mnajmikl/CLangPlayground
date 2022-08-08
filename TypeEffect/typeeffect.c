#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h> //include windows header
#define slowdown(x) Sleep(x)
#define TIMEOUT 500
#endif

#ifdef __linux__
#include <unistd.h> //include POSIX standard C header
#define slowdown(x) usleep(x)
#define TIMEOUT 500000
#endif

#include "typeeffect.h"

void typeprint(const char* sentence)
{
    int i = 0;
    while (i < (int)strlen(sentence))
    {
        printf("%c", *(sentence+i));
        fflush(stdout);
        i++;
        slowdown(TIMEOUT);
    }
}
