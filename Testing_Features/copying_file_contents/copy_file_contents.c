#include <stdio.h>

int main()
{
    FILE *source, *target;
    source = fopen("bat_data", "r");
    target = fopen("copied_file.txt", "w");

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
