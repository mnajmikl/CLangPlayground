#include <string.h>
#include <stdlib.h>
#include "nmath.h"

int toint(const char* src)
{
    /*
     * Output given C string into integer e.g. "1000" will be 1000
     * Assumption is the C string passed is a positive valid integer without integer sign
     * This function does not process integer sign -/+ yet
     *
     * The logic:
     *  1. Get the length of the given C string "src" using strlen();
     *     or manually counting until we get '\0' (null terminator)
     *  2. Get the highest 10 to the power nth position of the first character src[0]
     *     e.g. "1000" - the first character is 1 (thousand)
     *  3. Calculate the power of the highest number value e.g. 1000 = 10 to the power of n = 3
     *      Which is strlen(src) - 1 = 4 - 1 = 3
     *  4. Calculate the rest of the numbers in their position of nth.Can be done from 10^0 to 10^n, or 10^ to 10^1 (1)
     *  5. Sum up all the values and return
     */
    int hasnoninteger = 0;
    int n = strlen(src);
    for (int j = 0; j < n; j++)
    {
        if(((int)src[j] < 48) || ((int)src[j] > 57))
        {
            hasnoninteger = 1;
            break;
        }
    }
    if (hasnoninteger) return 0;
    int sum = 0;
    if (n == 1)
    {
        return getnumber(src[0]);
    }
    for (int s = 0; s < n; s++)
    {
        int d = getnumber(src[s]);
        for (int p = n - 1; p > s; p--)
        {
            d *= 10;
        }
        sum += d;
    }
    return sum;
}

long long int tolong(const char* src)
{
    /*
     * Output given C string into integer e.g. "1000" will be 1000
     * Assumption is the C string passed is a positive valid integer
     *
     * The logic is the same as toint() but the return type is long long int
     */
    int hasnoninteger = 0;
    int len = strlen(src);
    for (int j = 0; j < len; j++)
    {
        if(((int)src[j] < 48) || ((int)src[j] > 57))
        {
            hasnoninteger = 1;
            break;
        }
    }
    if (hasnoninteger) return 0;
    long long int sum = 0;
    if (len == 1)
    {
        return getnumber(src[0]);
    }
    for (int s = 0; s < len; s++)
    {
        long long int d = (long long int) getnumber(src[s]);
        for (int p = len - 1; p > s; p--)
        {
            d *= 10;
        }
        sum += d;
    }
    return sum;
}

float tofloat(const char* src)
{
    /*
     * The integer part is the same as tofloat() and tolong()
     * The string is tokenize by the separator character "." (decimal sign)
     * The floating point part is repeatedly divided by 10 according to each decimal place
     */
    int validfloat = 1;
    int tokencount = 0;
    int len = strlen(src);
    char floatstring[2][30];
    char *srccpy = calloc(len, sizeof(char));
    strncpy(srccpy, src, len);
    if (((int)srccpy[0] < 48) || ((int)srccpy[0] > 57)) validfloat = 0;
    char* token = strtok(srccpy, ".");
    if (token != NULL)
    {
        strncpy(floatstring[tokencount], token, 30);
        tokencount++;
        token = strtok(NULL, ".");
    }
    if (token != NULL)
    {
        strncpy(floatstring[tokencount], token, 30);
        tokencount++;
        token = strtok(NULL, ".");
    }
    if (token != NULL) validfloat = 0;
    free(srccpy);
    if ((!toint(floatstring[0])) || (!toint(floatstring[1]))) validfloat = 0;
    float sum = 0.00f;
    if (validfloat)
    {
        int tlen = strlen(floatstring[1]);
        for (int s = 0; s < tlen; s++)
        {
            float d = (float) getnumber(floatstring[1][s]);
            for (int p = 0; p <= s; p++)
            {
                d /= 10.00f;
            }
            sum += d;
        }
        return (float)toint(floatstring[0]) + sum;
    }
    return 0.00f;
}

double todouble(const char* src)
{
    /*
     * This the the double version of tofloat()
     */
    int validfloat = 1;
    int tokencount = 0;
    int len = strlen(src);
    char floatstring[2][30];
    char *srccpy = calloc(len, sizeof(char));
    strncpy(srccpy, src, len);
    if (((int)srccpy[0] < 48) || ((int)srccpy[0] > 57)) validfloat = 0;
    char* token = strtok(srccpy, ".");
    if (token != NULL)
    {
        strncpy(floatstring[tokencount], token, 30);
        tokencount++;
        token = strtok(NULL, ".");
    }
    if (token != NULL)
    {
        strncpy(floatstring[tokencount], token, 30);
        tokencount++;
        token = strtok(NULL, ".");
    }
    if (token != NULL) validfloat = 0;
    free(srccpy);
    if ((!toint(floatstring[0])) || (!toint(floatstring[1]))) validfloat = 0;
    float sum = 0.00f;
    if (validfloat)
    {
        int tlen = strlen(floatstring[1]);
        for (int s = 0; s < tlen; s++)
        {
            double d = (double) getnumber(floatstring[1][s]);
            for (int p = 0; p <= s; p++)
            {
                d /= 10.00f;
            }
            sum += d;
        }
        return (double)toint(floatstring[0]) + sum;
    }
    return 0.00f;
}

int getnumber(char n)
{
    /*
     * This helper function output the corresponding number for char n
     */
    switch(n)
    {
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    /* '0' and other characters */
    default:
        return 0;
    }
}

