// file: 
// description:
//
// author: mathew owusu jr
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "/usr/lib/battery-tracker/Utilities/queue.h"

// Location of current battery voltage file 
#define ENERGY_NOW "/sys/class/power_supply/BAT0/energy_now"
// Location of max battery voltage file
#define ENERGY_FULL "/sys/class/power_supply/BAT0/energy_full"
// Location where output is stored
#define BAT_DATA "/var/log/battery-tracker/bat_data"
#define BAT_LOG "/var/log/battery-tracker/past-days/"
#define CHARGE_STATUS "/sys/class/power_supply/BAT0/status"
// One day in Unix
#define UNIX_DAY 86400
// 00:00:00
#define MIDNIGHT 18000
// 00:01:00
#define TWELVE_O_ONE 18060


// Function to create name of past day file
//
// @param:
// @reutrn:
static char *new_filename(time_t curr_time)
{
    char *location = (char*)malloc(200);
    //strcpy(location, "data/");
    strcpy(location, BAT_LOG);
    char *time_string = ctime(&curr_time);
    time_string[strlen(time_string) - 1] = 0; // removes '\n' 
    for (int i = 0; i < strlen(time_string); i++)
    {
        if (time_string[i] == ' ')
            time_string[i] = '_';
    }
    strcat(location, time_string);
    return location;
}


//
//
// @param:
// @param:
static void copy_file_contents(FILE *source, FILE *target)
{
    char c;
    c = fgetc(source);
    while (c != EOF)
    {
        fputc(c, target);
        c = fgetc(source);
    }

    fclose(source);
    fclose(target);
}


// This function has the main loop
//
int main(void)
{
    //check access
    /*if (access(BAT_DATA, W_OK) != 0)
    {
        perror("You don't have permission to write to file");
        return 1;
    }*/

    // Creating file pointers
    FILE *cur_bat, *max_bat, *output, *charging;
    
    // queue for handling past bat day data
    Queue past_days = make_queue(7);
    char *target_name;

    // Have I cleared the current file?
    int clear_file = 0;

    output = fopen(BAT_DATA, "a");
    if (!output)
            {
                mkdir("/var/log/battery-tracker", S_IRWXO);
                output = fopen("BAT_DATA", "w");
            }
    fclose(output);

    // main loop of daemon process
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
        
        // get charge status
        charging = fopen(CHARGE_STATUS, "r");
        int status;
        if (fgetc(charging) == 'D')
            status = 0;
        else
            status = 1;

        // Get the current unix time
        time_t cur_time = time(0);
        
        // Writing to files
        // if time is between 00:00 and 00:01 clear the file
        if ((clear_file == 0) &&
                ((cur_time % UNIX_DAY >= MIDNIGHT) && 
                 (cur_time % UNIX_DAY <= TWELVE_O_ONE)))
        {
            // Copy current data to new file and add it to the past days queue
            FILE *source = fopen(BAT_DATA,"r");
            
            //
            //if (!source)
            //{
            //   mkdir("/var/log/Battery Tracker", S_IRWXO);
            //    source = fopen("BAT_DATA", "w");
            //}

            target_name = new_filename(cur_time);
            FILE *target = fopen(target_name,"w");
            
            if (!target)
            {
                mkdir(BAT_LOG, S_IRWXO);
                target = fopen(target_name,"w");
            }


            if (! target)
                perror("Can't create file");
            printf("name: %s\n", target_name);
            copy_file_contents(source, target);
            enqueue(past_days, (void*)&(*target_name));

            // Wipe current file
            output = fopen(BAT_DATA, "w");
            fprintf(output, "%lu,%0.2f,%d\n", cur_time, bat_percentage, status);
            clear_file = 1;
        }
        else
        {
            output = fopen(BAT_DATA, "a");
            fprintf(output, "%lu,%0.2f,%d\n", cur_time, bat_percentage, status);
        }

        if (cur_time % UNIX_DAY > TWELVE_O_ONE)
            clear_file = 0;

        // Closing files, freeing memory
        fclose(cur_bat);
        fclose(max_bat);
        fclose(charging);
        fclose(output);
        //sleep
        sleep(10);
    }
    free(target_name);
}
