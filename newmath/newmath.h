#ifndef NEWMATH_H_INCLUDED
#define NEWMATH_H_INCLUDED
#include <stdlib.h>
#include <string.h>

/* Static functions in "newmath.c"
 * int getnumber(char);
 * int isvalidnumber(char);
 * int isvalidnumbersign(char);
 * char *getfloatstring(const char*);
 * char *getintstring(const char*);
 * long getlong(const char*);
 * long double getdouble(const char*);
*/

long stringtolong(const char*);
long double stringtodouble(const char*);

#endif // NEWMATH_H_INCLUDED
