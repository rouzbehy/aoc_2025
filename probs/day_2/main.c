#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "stdbool.h"
#include "aocutils.h"

long long int convert_substring_to_integer(char *data, int start_indx, int stop_indx)
{
    long long int result = 0;
    size_t length = stop_indx - start_indx;
    char *number_buffer = (char *)malloc((length + 1) * sizeof(char));
    printf("looking at %s:\n", data);
    strncpy(number_buffer, &data[start_indx], length);
    number_buffer[length + 1] = '\0';
    int status = sscanf(number_buffer, "%lld", &result);
    printf("%s --> %lld ? %d\n", number_buffer, result, status);
    free(number_buffer);
    return result;
}

int count_digits(long long int number)
{
    if (number == 0)
        return 1;
    if (number < 0)
        number = -number;

    return floor(log10((double)number)) + 1;
}

bool has_repeated_digits_part1(long long int number)
{
    int num_digits = count_digits(number);
    char num_as_string[num_digits];
    sprintf(num_as_string, "%lld", number);
    int midpoint = num_digits / 2;
    for (size_t i = 0; i < midpoint; i++)
    {
        // printf("\t%c =? %c\n", num_as_string[i], num_as_string[i + midpoint]);
        if (num_as_string[i] != num_as_string[i + midpoint])
            return false;
    }
    return true;
}

long int solve(const char *fname, long int *part1, long int *part2)
{
    if (fname == NULL)
    {
        puts("Coulld not open file.");
        return EXIT_FAILURE;
    }

    // variables for reading the file
    FILE *flptr;
    flptr = fopen(fname, "r");
    size_t sline = 0;
    size_t sread = 0;
    int index;
    char *buffer = NULL;
    const char *delim_outer = ",";
    char find = '-';
    char *token, *ptr;
    long long int num1 = 0, num2 = 0;
    int digit_count;
    *part1 = 0;
    sread = getline(&buffer, &sline, flptr);
    if (sread == -1)
    {
        printf("Error reading the file. Abort");
        return EXIT_FAILURE;
    }
    token = strtok(buffer, delim_outer);

    while (token != NULL)
    {
        ptr = strchr(token, find);
        index = (int)(ptr - token);
        // printf("index of `-`: %d\n", index);
        num1 = convert_substring_to_integer(token, 0, index);
        num2 = convert_substring_to_integer(token, index + 1, strlen(token));
        // printf("num1=%lld num2=%lld\n", num1, num2);
        for (long long int i = num1; i <= num2; i++)
        {
            digit_count = count_digits(i);
            // printf("%lld has %d digits\n", i, digit_count);
            // re-convert to string and check for repetition
            if ((digit_count % 2 == 0) && has_repeated_digits_part1(i))
            {
                *part1 = *part1 + i;
                *part2 = *part2 + i;
            }
        };
        printf("\tup to %s we have %ld for part 1.\n ", token, *part1);
        token = strtok(NULL, delim_outer);
    };
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    long_process(solve, argv[1]);
    return 0;
}