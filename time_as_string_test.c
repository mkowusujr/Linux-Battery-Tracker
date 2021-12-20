#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    // store current time as a string
    time_t curr_time = time(0);
	char *time_string = ctime(&curr_time);
    time_string[strlen(time_string) - 1] = 0;
    // create a file with that name
    FILE *target = fopen(time_string, "w");
    // write to that file and close
	fprintf(target, "%s", time_string);
	fclose(target);
	return 0;
}
