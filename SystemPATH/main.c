#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define PATH_SEPARATOR ";"
#elif __linux__
#define PATH_SEPARATOR ":"
#endif

int main(int argc, char** argv)
{
    /*
     * Get system environment PATH
     * and split them line by line
     */
    char *env = getenv("PATH");
    size_t len = strlen(env);
    char *envcpy = calloc(len, sizeof env);
    char* tokens;
    if (strcpy(envcpy, env) != NULL)
        tokens = strtok(envcpy, PATH_SEPARATOR);
    else
    {
        printf("Unable to system get PATH variables\n");
        return -1;
    }
    if (tokens == NULL)
    {
        printf("Unable to tokenize PATH\n");
        return -2;
    }
    int i = 1;
    printf("Current system paths: \n%s\n\n", env);
    /*
    * Exhaust the tokens until we reach NULL
    */
    printf("List of your system search paths: \n");
    while (tokens != NULL)
    {
        printf("%2d: \"%s\"\n", i, tokens);
        i++;
        tokens = strtok(NULL, PATH_SEPARATOR);
    }
    free(envcpy);
    return 0;
}

