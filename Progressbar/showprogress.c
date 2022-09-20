#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define FULLBLOCK "\xdb"
#define HALFBLOCK "\xde"
#elif __linux__
#define FULLBLOCK "\u2588"
#define HALFBLOCK "\u2590"
#endif

static char* repeatchar(const char*, int);
void showprogress(int, int);

int main()
{
    printf("\nRepeat characters 100 times\n");
    for(int i = 0; i <= 100; i++)
    {
        char* progresscounter = repeatchar(FULLBLOCK, i);
        printf("\r|%s|%3d\r", progresscounter, i);
        free(progresscounter);
    }
    printf("\r\n");
    for(int i = 0; i <= 200000; i++)
        showprogress(i, 200000);
    printf("\n");
    fflush(stdout);
    return 0;
}

static char* repeatchar(const char* str, int count)
{
    char* cpy = calloc(strlen(str) + 1, sizeof(char));
    if (cpy)
        strcpy(cpy, str);
    else
        return NULL;
    if (count <= 0)
        return cpy;
    char* repeat = calloc((strlen(str) * count) + 1, sizeof(char));
    if (repeat == NULL)
        return "";
    while (count--)
        strcat(repeat, cpy);
    if (cpy != NULL)
        free(cpy);
    return repeat;
}

void showprogress(int progress, int total)
{
    float percentage = 100.00 * ((float)progress / total);
    char* current_cursor = repeatchar(FULLBLOCK, (int)percentage);
    int next_cur = (int)percentage == 100 ? 100 : (100 - (int)percentage);
    char* ch_next_cur = (int)percentage == 100 ? "" : HALFBLOCK;
    char* next_cursor = repeatchar(ch_next_cur, next_cur);
    printf("\r|%s%s|%.2f%%\r", current_cursor, next_cursor, percentage);
    if (current_cursor != NULL)
        free(current_cursor);
    if (next_cursor != NULL)
        free(next_cursor);
}
