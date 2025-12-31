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
    strncpy(number_buffer, &data[start_indx], length);
    number_buffer[length + 1] = '\0';
    int status = sscanf(number_buffer, "%lld", &result);
    // printf("%s --> %lld ? %d\n", number_buffer, result, status);
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

bool has_repeated_digits(long long int number)
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

bool is_all_the_same_character(char *input)
{
    if (input == NULL)
    {
        printf("input is null. abort.");
        return EXIT_FAILURE;
    }
    char first = input[0];
    for (size_t i = 1; input[i] != '\0'; i++)
        if (input[i] != first)
            return false;
    return true;
}

bool has_repeated_pattern(long long int number)
{
    int num_digits = count_digits(number);
    char num_as_string[num_digits];
    sprintf(num_as_string, "%lld", number);
    if (num_digits < 2)
        return false;
    if (is_all_the_same_character(num_as_string))
        return true;
    // start by splitting the string into
    // substrings
    int split_factor = 2;
    size_t chunk_size;
    char **chunks = NULL;
    int comparison_flag = 0;
    // printf("---------------------------------\n");
    while (split_factor <= (num_digits / 2))
    {
        // printf("* Applying split_factor = %d to %s\n", split_factor, num_as_string);
        // chunk_size += (even_num_digits ? 0 : 1);
        if ((num_digits % split_factor) != 0)
        {
            split_factor += 1;
            continue;
        }
        chunk_size = num_digits / split_factor;
        chunks = (char **)malloc((split_factor + 1) * sizeof(char *));
        for (size_t i = 0; i <= split_factor; i++)
        {
            chunks[i] = malloc((chunk_size + 1) * sizeof(char));
            strncpy(chunks[i], num_as_string + i * chunk_size, chunk_size);
            chunks[i][chunk_size + 1] = '\0';
            // printf("\t%s\n", chunks[i]);
            if (i == 0)
            {
                // printf("first element for split factor %d : %s\n", split_factor, chunks[i]);
                continue;
            }
            else
            {
                // printf("comparing chunks[i]='%s' and chunks[0]='%s': %d\n", chunks[i], chunks[0], strcmp(chunks[i], chunks[0]));

                if (strcmp(chunks[i], chunks[0]) == 0)
                    comparison_flag += 1;
            }
            if (comparison_flag == (split_factor - 1))
            {
                for (size_t i = 0; i <= split_factor; i++)
                    free(chunks[i]);
                free(chunks);
                // deallocate and return true
                return true;
            }
        }
        // printf("\n");
        for (size_t i = 0; i <= split_factor; i++)
            free(chunks[i]);
        free(chunks);
        split_factor += 1;
    }
    return false;
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
    bool acceptable = false;
    int index;
    char *buffer = NULL;
    const char *delim_outer = ",";
    char find = '-';
    char *token, *ptr;
    long long int num1 = 0, num2 = 0;
    int digit_count;
    *part1 = 0;
    *part2 = 0;
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
        // printf("Range %s:\n", token);
        num1 = convert_substring_to_integer(token, 0, index);
        num2 = convert_substring_to_integer(token, index + 1, strlen(token));
        // printf("num1=%lld num2=%lld\n", num1, num2);
        for (long long int i = num1; i <= num2; i++)
        {
            digit_count = count_digits(i);
            // printf("%lld has %d digits\n", i, digit_count);
            // re-convert to string and check for repetition
            if ((digit_count % 2 == 0) && has_repeated_digits(i))
            {
                *part1 = *part1 + i;
            }
            // printf("applying part 2 solution to %lld\n", i);
            acceptable = has_repeated_pattern(i);
            if (acceptable)
            {
                // printf("%lld in has a repeating pattern.\n", i);
                // printf("\t * Work on %lld:", i);
                // printf(", Acceptable: %d\n", acceptable);
                *part2 = *part2 + i;
                // printf("\t * part2 = %lld at %d\n", *part2, i);
            }
        };
        // printf("\tup to %s we have %ld for part 1.\n ", token, *part1);
        token = strtok(NULL, delim_outer);
    };
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    long_process(solve, argv[1]);
    return 0;
}