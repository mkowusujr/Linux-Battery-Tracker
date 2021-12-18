// file: 
// description:
//
// author: mathew owusu jr
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Location of current battery voltage file 
#define ENERGY_NOW "/sys/class/power_supply/BAT0/energy_now"
// Location of max battery voltage file
#define ENERGY_FULL "/sys/class/power_supply/BAT0/energy_full"
// Location where output is stored
#define BAT_DATA "/var/lib/bat_data"
// One day in Unix
#define UNIX_DAY 86400
// 00:00:00
#define MIDNIGHT 18000
// 00:01:00
#define TWELVE_O_ONE 18060


// This function
//
int main(void)
{
    //check access
    if (access(BAT_DATA, W_OK) != 0)
    {
        perror("You don't have permission to write to file");
        return 1;
    }

    // Creating file pointers
    FILE *cur_bat, *max_bat, *output;
    
    // Main loop
    int clear_file = 0;
    while(1)
    {
        // Read current battery
        cur_bat = fopen(ENERGY_NOW, "r");
        int cur_val;
        fscanf(cur_bat, "%d", &cur_val);
        printf("current battery %d\n", cur_val);
        
        // Read maximum battery
        max_bat = fopen(ENERGY_FULL, "r");
        int max_val;
        fscanf(max_bat, "%d", &max_val);
        printf("max battery %d\n", max_val);

        // Calculate the current battery percentage
        double bat_percentage = (double) cur_val / (double) max_val;
        bat_percentage *= 100.0;
        printf("current battery percentage %0.2f%%\n", bat_percentage);
        
        // Get the current unix time
        time_t cur_time = time(0);
        
        // Writing to files
        // if time is between 00:00 and 00:01 clear the file
        if ((clear_file == 0) &&
                ((cur_time % UNIX_DAY >= MIDNIGHT) && 
                 (cur_time % UNIX_DAY <= TWELVE_O_ONE)))
        {
            output = fopen(BAT_DATA, "w");
            fprintf(output, "%lu,%0.2f\n", cur_time, bat_percentage);
            clear_file = 1;
        }
        else
        {
            output = fopen(BAT_DATA, "a");
            fprintf(output, "%lu,%0.2f\n", cur_time, bat_percentage);
        }
        
        if (cur_time % UNIX_DAY > TWELVE_O_ONE)
            clear_file = 0;
        // Closing files, freeing memory
        fclose(cur_bat);
        fclose(max_bat);
        fclose(output);

        //sleep
        sleep(10);
    }
}
