#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define FULLBLOCK "\xdb"
#define HALFBLOCK "\xde"
#endif // _WIN32

#ifdef _linux_
#define FULLBLOCK "\u2588"
#define HALFBLOCK "\u2590"
#endif // linux

char *repeatchar(char *, size_t);
char *showprogress(size_t, size_t);

int main() {
    char *progresscounter, *progressbar;
    printf("\nRepeat characters 100 times\n");
    for(size_t i = 0; i <= 25; i++) {
        progresscounter = repeatchar(FULLBLOCK, i);
        printf("\r|%s|\r", progresscounter);
    }
    free(progresscounter);
    printf("\nShow Progress 0 - 200000\n");
    for(size_t i = 0; i <= 200000; i++) {
        progressbar = showprogress(i, 200000);
        printf("\r%s\r", progressbar);
    }
    printf("\r\n");
    fflush(stdout);
    free(progressbar);
    return 0;
}

char *repeatchar(char *str, size_t count) {
    if (count == 0) return str;
    char *repeat = calloc(strlen(str) * count + count, sizeof(size_t));
    if (repeat == NULL) return "";
    while (count--)
        strcat(repeat, str);
    return repeat;
}

char *showprogress(size_t progress, size_t total)
{
    char *current_cursor, *next_cursor, *result;
    float percent = 100 * ((float)progress / (float)total);
    current_cursor = repeatchar(FULLBLOCK, ((size_t)percent / 4));
    next_cursor = repeatchar(HALFBLOCK, 25 - ((size_t)percent / 4));
    result = calloc(strlen(current_cursor) + strlen(next_cursor) + (size_t)percent + 1, sizeof(size_t));
    if ((int)percent == 100) next_cursor = "";
    sprintf(result, "|%s%s|%.2f%%", current_cursor, next_cursor, percent);
    return result;
}
