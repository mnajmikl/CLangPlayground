#include <stdio.h>

typedef struct {
    int x;
    int y;
    int z;
    char n[8];
} PointA;

typedef struct {
    int a;
    int b;
    char c[14];
} PointB;


int main() {
    PointA point1 = {10, 10, 0, "ABCDEF"};
    PointB *point2 = (PointB *) &point1;
    printf("point1: {%d, %d, %d, %s}\n", point1.x, point1.y, point1.z, point1.n);
    point1.x = 20;
    point1.y = 15;
    printf("point2: {%d, %d, %s}\n", point2->a, point2->b, point2->c);
    printf("\nAfter changing a,b of point2\n");
    printf("point1: {%d, %d}\n", point1.x, point1.y);
    printf("point2: {%d, %d}\n", point2->a, point2->b);
    return 0;
}
