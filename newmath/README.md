# New math library

Imitating / Rewriting a few math.h functions e.g. atoi(), atof(), strtol(), strtod() etc.

Two useable functions in this example:
long stringtolong(const char*)
long double stringtodouble(const char*)

Static functions in "newmath.c"
int getnumber(char)
int isvalidnumber(char)
int isvalidnumbersign(char)
char *getfloatstring(const char*)
char *getintstring(const char*)
long getlong(const char*)
long double getdouble(const char*)

Caveats:
Casting to to smaller data type will not preserve floating precision.

Issues resolved:
Precision increased by using long double and long data types.
Number signs are now considered as valid (number can be marked as negative or positive with "-" or "+" sign).
stringtolong() will accepts string with floating point into integer.
