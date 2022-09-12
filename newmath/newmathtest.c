#include <stdio.h>
#include "newmath.h"

int main()
{
    char *roundnumber = "+10.1235";
    char *floatnumber = "-110.670324230678";
    printf("%s %ld %.4Lf\n%s %ld %.12Lf\n", roundnumber, stringtolong(roundnumber), \
           stringtodouble(roundnumber), floatnumber, stringtolong(floatnumber), \
           stringtodouble(floatnumber));
    return 0;
}
