# New math library
Imitating / Rewriting a few math.h functions e.g. atoi(), atof(), strtol(), strtod() etc.

Four functions in this example:
1. toint() : string to int
2. tolong() : string to long long int
3. tofloat() : string to float
4. todouble() : string to double

Caveats:
1. The functions only handle string that doesn't have "-" or "+" signs.
2. Assumption is the integer is positive
3. The floating point output is horrible. I don't know how to fix it.
