/*
 * main.c
 *
 *  Created on: May 9, 2020
 *      Author: Robert
 */
#include <stdio.h>
#include "math.h"

int main()
{
    int a=1000000, b=999999;

    printf("Sum: %d\n", addition(a, b));
    printf("subtract: %d\n", subtraction(a, b));
    printf("multiple: %lld\n", multiplication(a, b));
    printf("division: %f\n", division(a, b));

    getchar();
    return 0;
}
