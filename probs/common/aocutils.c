#include "utils.h"
#include "stdlib.h"
#include "stdio.h"

void process(int (*solve)(const char *, int *, int *), const char *target[])
{
    int flag;
    int part1 = -1, part2 = -1;
    flag = solve(target, &part1, &part2);
    if (flag == EXIT_SUCCESS)
        printf("Solution: \n Part 1: %d\n Part 2: %d\n", part1, part2);
    else
        printf("Received error signal. Need to investigate. Abort.\n");
}