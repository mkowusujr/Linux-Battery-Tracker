// file: clear.c
// description: a demo to test clearing text files
#include <stdio.h>


int main(int argc, char **argv)
{
    FILE *nonempty_file;
    nonempty_file = fopen(argv[1], "w");
    fprintf(nonempty_file, "New Text\n");
    fclose(nonempty_file);
    return 0;
}
