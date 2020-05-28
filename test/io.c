//
// Created by rainzhong on 2020/5/27.
//

#include <stdio.h>

void printInt(long x){
    printf("[output] Int value = %ld\n", x);
}

void printChar(char x){
    printf("[output] Char value = %c\n", x);
}

void printDouble(double x){
    printf("[output] Double value = %f\n", x);
}

long inputInt(){
    printf("[input] ");
    long value;
    scanf("%ld", &value);
    return value;
}

double inputDouble(){
    printf("[input] ");
    double value;
    scanf("%lf", &value);
    return value;
}

char inputChar(){
    printf("[input] ");
    char value;
    scanf("%c", &value);
    return value;
}