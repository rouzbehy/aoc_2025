#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int solve(const char *fname, int *part1, int *part2)
{
    if (fname == NULL)
    {
        puts("Could not open file.");
        return EXIT_FAILURE;
    }

    // variables for reading the file
    FILE *flptr;
    flptr = fopen(fname, "r");
    size_t sline = 0;
    size_t sread = 0;
    char *buffer = NULL;
    char *number_buffer = NULL;
    int current_position = 50;
    int num_zeroes_part_1 = 0, notches = 0;
    int temp, num_zeroes_part_2 = 0;
    int inner_loop_value;
    int sign_of_movement = 0;
    char direction;
    while ((sread = getline(&buffer, &sline, flptr)) != -1)
    {
        if ((char)buffer[0] == '\n')
            continue;

        direction = (char)buffer[0];

        number_buffer = (char *)malloc(sread - 1);
        for (size_t i = 0; i < sread - 1; i++)
        {
            number_buffer[i] = (char)buffer[i + 1];
        }
        number_buffer[sread - 2] = '\0';

        notches = atoi(number_buffer);
        // printf("turn %c for %d: \n", direction, notches);
        // now do the math
        if (direction == 'L')
            sign_of_movement = -1;
        else if (direction == 'R')
            sign_of_movement = 1;
        else
            return EXIT_FAILURE;
        temp = current_position + sign_of_movement * notches;
        // Inspiration from a reddit post: don't bother
        // with rotating anything: just find out if where you are
        // is divisible by 100
        if (temp % 100 == 0)
            num_zeroes_part_1 += 1;
        // before updating the current position, determine
        // how many times we passed zero:
        inner_loop_value = current_position;
        while (inner_loop_value != temp)
        {
            inner_loop_value = inner_loop_value + sign_of_movement;
            if (inner_loop_value % 100 == 0)
                num_zeroes_part_2 += 1;
        }
        current_position = temp;
    };
    *part1 = num_zeroes_part_1;
    *part2 = num_zeroes_part_2;
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    int flag;
    int part1 = -1, part2 = -1;
    if (argc < 2)
    {
        printf("Require at least 2 arguments, recevied %d. Abort.\n", argc);
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "test") == 0)
        flag = solve("../../inputs/day_1/test_data.txt", &part1, &part2);
    else if (strcmp(argv[1], "main") == 0)
        flag = solve("../../inputs/day_1/main_data.txt", &part1, &part2);
    else
    {
        printf("The argument should either be `test` or `main`. Abort.\n ");
        return EXIT_FAILURE;
    }
    if (flag == EXIT_SUCCESS)
        printf("Solution: \n Part 1: %d\n Part 2: %d\n", part1, part2);
    else
        printf("Received error signal. Need to investigate.\n");
}
