// file: 
// description:
//
// author: mathew owusu jr
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// 
#define ENERGY_NOW "/sys/class/power_supply/BAT0/energy_now"
//
#define ENERGY_FULL "/sys/class/power_supply/BAT0/energy_full"
//
#define BAT_DATA "/var/lib/bat_data"


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

    //
    FILE *cur_bat, *max_bat, *output;
    
    //
    while(1)
    {
        //
        cur_bat = fopen(ENERGY_NOW, "r");
        int cur_val;
        fscanf(cur_bat, "%d", &cur_val);
        printf("current battery %d\n", cur_val);
        
        //
        max_bat = fopen(ENERGY_FULL, "r");
        int max_val;
        fscanf(max_bat, "%d", &max_val);
        printf("max battery %d\n", max_val);

        //
        double bat_percentage = (double) cur_val / (double) max_val;
        bat_percentage *= 100.0;
        printf("current battery percentage %0.2f%%\n", bat_percentage);
        
        //
        time_t cur_time = time(0);
        
        //
        output = fopen(BAT_DATA, "a");
        fprintf(output, "%lu,%0.2f\n", cur_time, bat_percentage);
        
        //
        fclose(cur_bat);
        fclose(max_bat);
        fclose(output);

        //sleep
        sleep(10);
    }
}
