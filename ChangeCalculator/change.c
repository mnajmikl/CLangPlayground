#include <stdio.h>
#include <math.h>
#include "change.h"

unsigned int gethundreds(unsigned int change) {
    return change / 100;
}

unsigned int getfifties(unsigned int change) {
    return change / 50;
}

unsigned int gettwenties(unsigned int change) {
    return change / 20;
}

unsigned int gettens(unsigned int change) {
    return change / 10;
}

unsigned int getfives(unsigned int change) {
    return change / 5;
}

unsigned int getones(unsigned int change) {
    return change;
}

unsigned int gethalfs(unsigned int change) {
    return change / 50;
}

unsigned int getquarters(unsigned int change) {
    return change / 25;
}

unsigned int getdimes(unsigned int change) {
    return change / 10;
}

unsigned int getnickels(unsigned int change) {
    return change / 5;
}

unsigned int getpennies(unsigned int change) {
    return change;
}

void getchange() {
    float change;
    unsigned int halfs, quarters, dimes, nickels, pennies;
    unsigned int hundreds, fifties, twenties, tens, fives, ones;

    printf("Please enter the change in dollars and cents: ");
    scanf("%f", &change);

    unsigned int dollars = (unsigned int) change;
    float cents = (float)(change - (unsigned int)change);
    printf("\nDollar portion: %d | Cents portion: %.2f\n", dollars, cents);
    printf("\nYour change:\n");

    do {
        hundreds = gethundreds(dollars);
        dollars %= 100;
        fifties = getfifties(dollars);
        dollars %= 50;
        twenties = gettwenties(dollars);
        dollars %= 20;
        tens = gettens(dollars);
        dollars %= 10;
        fives = getfives(dollars);
        dollars %= 5;
        ones = getones(dollars);
        dollars = 0;
    } while(dollars > 0);

    printf("\nHundreds: %d\nFifties: %d\nTwenties: %d\n", hundreds, fifties, twenties);
    printf("Tens: %d\nFives: %d\nOnes: %d\n", tens, fives, ones);

    unsigned int icents = round(cents * 100);
    do {
        halfs = gethalfs(icents);
        icents %= 50;
        quarters = getquarters(icents);
        icents %= 25;
        dimes = getdimes(icents);
        icents %= 10;
        nickels = getnickels(icents);
        icents %= 5;
        pennies = getpennies(icents);
        icents = 0;
    } while (icents > 0);

    printf("\nFifty cents: %d\nQuarters: %d\nDimes: %d\nNickels: %d\nPennies: %d\n", halfs, quarters, dimes, nickels, pennies);

    printf("\nTotal notes: %d\n", hundreds + fifties + twenties + tens + fives + ones);
    printf("Total coins: %d\n", halfs + quarters + dimes + nickels + pennies);
}
