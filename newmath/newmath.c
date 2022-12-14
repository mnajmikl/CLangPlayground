#include "newmath.h"

/* Static functions in "newmath.c"
 * int getnumber(char)
 * int isvalidnumber(char)
 * int isvalidnumbersign(char)
 * int isnegative(const char* src)
 * char *getfloatstring(const char*)
 * char *getintstring(const char*)
 * long getlong(const char*);
 * long double getdouble(const char*)
*/

static int getnumber(char n)
{
    return ((n - 48 >= 0) && (n - 48 <= 57)) ? (n - 48) : 0;
}

static int isvalidnumber(char c)
{
    return ((c >= 48) && (c <= 57));
}

static int isvalidnumbersign(char c)
{
    return ((c == 43) || (c == 45));
}

static int isnegative(const char* src)
{
    return (src[0] == 45);
}

static char *getfloatstring(const char* src)
{
    size_t len = strlen(src);
    char *decimals = (char*) calloc(len, sizeof(char));
    /* Find the decimal point */
    size_t pos = strcspn(src, ".");
    if (pos >= len)
        return "0";
    int c = 0;
    while (c < (int) (len - pos))
    {
        int loc = (int) pos + c + 1;
        if (loc < (int) len)
        {
            if (!isvalidnumber(src[loc])) return "0";
        }
        decimals[c] = src[loc];
        c++;
    }
    decimals[c] = '\0';
    /* Verify the integer part. Make sure we also have valid integer. If not, the result is "0" */
    int i = 0;
    while (i < (int) pos)
    {
        if (i == 0)
        {
            if (!((isvalidnumbersign(src[i])) || (isvalidnumber(src[i])))) return "0";
        }
        else
        {
            if (!isvalidnumber(src[i])) return "0";
        }
        i++;
    }
    return decimals;
}

static char *getintstring(const char* src)
{
    size_t len = strlen(src);
    char *integers = (char*) calloc(len, sizeof(char));
    /* Find the decimal point */
    size_t pos = strcspn(src, ".");
    int c = 0;
    while (c < (int) len)
    {
        if (c == 0)
        {
            if (!((isvalidnumbersign(src[c])) || (isvalidnumber(src[c])))) return "0";
        }
        if (src[c] == 46)
            integers[c] = '\0';
        else
            integers[c] = src[c];
        /* Verify the decimal part. Make sure we also have valid decimal. If not, the result is "0" */
        if (c > (int) pos)
        {
            if (!isvalidnumber(src[c])) return "0";
        }
        c++;
    }
    return integers;
}

static long getlong(const char* src)
{
    size_t len = strlen(src);
    long sum = 0;
    if ((int) len == 0) return sum;
    if ((int) len == 1) return (long) getnumber(src[0]);
    for (int s = 0; s < (int) len; s++)
    {
        long d = getnumber(src[s]);
        for (int p = (int) len - 1; p > s; p--)
            d *= 10;
        sum += d;
    }
    return sum;
}

static long double getdouble(const char* src)
{
    size_t len = strlen(src);
    long double sum = 0.00f;
    if ((int) len == 0) return sum;
    if ((int) len == 1) return (long double) getnumber(src[0]);
    for (int s = 0; s < (int) len; s++)
    {
        long double d = (long double) getnumber(src[s]);
        for (int p = 0; p <= s; p++)
            d /= 10.00f;
        sum += d;
    }
    return sum;
}

long stringtolong(const char* src)
{
    char* istring = getintstring(src);
    long long1 = getlong(istring);
    free(istring);
    return ((isnegative(src) ? -1 : 1) * long1);
}

long double stringtodouble(const char* src)
{
    char* istring = getintstring(src);
    char* dstring = getfloatstring(src);
    long double d1 = (long double) getlong(istring);
    long double d2 = getdouble(dstring);
    free(istring);
    free(dstring);
    return ((isnegative(src) ? -1 : 1) * d1) + ((isnegative(src) ? -1 : 1) * d2);
}
