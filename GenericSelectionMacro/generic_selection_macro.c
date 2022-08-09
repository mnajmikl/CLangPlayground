#include <stdio.h>

// You may use type generic macro (C 2011) using the keyword _Generic
#define do_something(S) _Generic ((S),  a_ptr: do_this, b_ptr: do_that ) (S)

typedef struct { int x; } type_a;
typedef struct { int y; } type_b;

typedef type_a *a_ptr;
typedef type_b *b_ptr;

void do_this(type_a *a);
void do_that(type_b *b);

int main()
{
    type_a a1;
    type_b b1;
    do_something(&a1);
    do_something(&b1);
    printf("%d %d\n", a1.x, b1.y);
    return 0;
}

void do_this(type_a *a) { a->x = 10; }

void do_that(type_b *b) { b->y = 20; }
