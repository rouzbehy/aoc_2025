#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int solve_part_1(const char * fname)
{
    if (fname == NULL)
    {
        puts("Could not open file.");
        return EXIT_FAILURE;
    }

    // variables for reading the file
    FILE* flptr;
    flptr = fopen(fname, "r");
    size_t sline = 0;
    size_t sread = 0;
    char* buffer = NULL;
    char* number_buffer = NULL;
    int current_position = 50;
    int num_zeroes=0, notches=0, temp;
    char direction;
    while( (sread = getline(&buffer, &sline, flptr)) != -1)
    {
        if ((char) buffer[0]  == '\n') 
            continue;
        
        direction = (char) buffer[0];
        
        number_buffer = (char * )malloc(sread - 1);
        for (size_t i=0; i < sread-1; i++)
        {
            number_buffer[i] = (char) buffer[i+1];
        }
        number_buffer[sread - 2] = '\0';

        notches = atoi(number_buffer);
        printf("turn %c for %d: \n", direction, notches);
        //now do the math
        if (direction == 'L')
        {
            temp = current_position - notches;
        }
        else if (direction == 'R')
        {
            temp = current_position + notches;
        }
        else
        {
            return EXIT_FAILURE;
        }

        if (temp <= 99 && temp >= 0)
            current_position = temp;
        if (temp >= 100)
        {
            current_position = temp%100;
        }
        else if (temp < 0)
        {
            current_position = - 1 * (abs(temp) % 100);
        }
        printf("temp: %d, ", temp);
        printf("current_position: %d\n",current_position);
        if (current_position == 0)
            num_zeroes += 1;
        // have to also count, for part 2, the number of times 
        // we passed zero:
    };
    return num_zeroes;
}



int main(int argc, char *argv[])
{
    int solution= solve_part_1(argv[1]);
    printf("had %d zeros.\n", solution);
}
