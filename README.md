# Linux Battery Tracker
This is a multi file program, that tracks and displays the battery charge of a laptop
In unix everything is a file, even the current battery voltage of you laptop! This program 
is a daemon process wriiten in c that reads the laptop current voltage, and calculates in current
percentage, and writes to a file the percentage and time it was calculated.

Then the python program displays the data written to the file with matplotlib

## C Battery Daemon
### bata_stat.c
TODO
### queue.h and queue.c
TODO
## Python Graphing Program
TODO
## Features
Shows the battery life of linux laptop over a day, clears at the end of the day
### Upcoming Features
Save last few days for later reference
## How to Set Up This Program on Your Linux Laptop
TODO