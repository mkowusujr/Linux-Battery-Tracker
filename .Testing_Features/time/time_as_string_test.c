#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    // store current time as a string
    time_t curr_time = time(0);
	char *time_string = ctime(&curr_time);
    time_string[strlen(time_string) - 1] = 0; // removes '\n' 
    for (int i = 0; i < strlen(time_string); i++)
    {
        if (time_string[i] == ' ')
            time_string[i] = '_';
    }
    // create a file with that name
    FILE *target = fopen(time_string, "w");
    // write to that file and close
	fprintf(target, "%lu\n", curr_time);
	fclose(target);
	return 0;
}
