/// file: battery_tracker.c
/// description: Thisprogram handles the file operations and contains the main
/// loop that runs as a the daemon process
/// author: mathew owusu jr
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "/usr/lib/battery-tracker/Utilities/queue.h"

/// Location of current battery voltage file
#define ENERGY_NOW "/sys/class/power_supply/BAT0/energy_now"
/// Location of max battery voltage file
#define ENERGY_FULL "/sys/class/power_supply/BAT0/energy_full"
/// Location where output is stored
#define BAT_DATA "/var/log/battery-tracker/bat_data"
/// The location where the data from the past days are stored
#define BAT_LOG "/var/log/battery-tracker/past-days/"
/// One day in seconds according to the Unix standard
#define UNIX_DAY 86400
/// the reminder of any day at midnight(00:00:00) mod one day in seconds
#define MIDNIGHT 18000
/// the reminder of any day at twelve o one(00:01:00) mod one day in seconds
#define TWELVE_O_ONE 18060


/// Creates the name of the file and also contains its filepath
/// @param time_t curr_time is the timestamp that the file is being created for
/// @return the file path of the filename created
static char *new_filename(time_t curr_time)
{
    char *location = (char*)malloc(200);
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


/// Copies the contents of the battery data file to its new location in the
/// past days folder
/// @param FILE *source the pointer to the battery data file
// @param FILE *target the pointer to the new file location
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


/// The main loop that acts a daemon process
/// 1. Creates the file pointers, the queue, and checks if the battery data
/// file exists. If it doesn't it creates it along with its directory
/// 2. Opens and reads and stores the data collected from the energy files
/// in the root directory
/// 3. Calculates the battery percentage by dividing the value in the energy_now
/// file with the value in the engery_full file
/// 4. Gets the time at which the calculation is preformed and stores it
/// 5. If it is midnight it copies the contents of the battery data file to a
/// new file inside the created past days folder, and wipes the battery data
/// file otherwise it appends the data to the end of the battery data file
/// 6. It writes to the battery data file in this format:
/// unixTime,batteryPercentage
/// 7. Puts the program to sleep for 10 seconds then runs the loop again
/// 8. If the program is terminated, frees the memory allocated
int main(void)
{
    //check access
    /*if (access(BAT_DATA, W_OK) != 0)
    {
        perror("You don't have permission to write to file");
        return 1;
    }*/

    // Creating file pointers
    FILE *cur_bat, *max_bat, *output;

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
            target_name = new_filename(cur_time);
            FILE *target = fopen(target_name,"w");
            if (!target)
            {
                mkdir(BAT_LOG, S_IRWXO);
                target = fopen(target_name,"w");
            }
            printf("name: %s\n", target_name);
            copy_file_contents(source, target);
            enqueue(past_days, (void*)&(*target_name));

            // Wipe current file
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

        // Closing files and freeing memory
        fclose(cur_bat);
        fclose(max_bat);
        fclose(output);
        // Pause the program and re-run the main loop in 10 seconds
        sleep(10);
    }
    free(target_name);
}
