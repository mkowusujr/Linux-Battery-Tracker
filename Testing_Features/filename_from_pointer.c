#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXSIZE 0xff
int main()
{
    char proclnk[MAXSIZE];
    char filename[MAXSIZE];
    FILE *fptr;
    int fno;
    ssize_t r;

    fptr = fopen("test.txt", "r");
    if (fptr != NULL)
    {
        fno = fileno(fptr);
        sprintf(proclnk, "proc/self/fd/%d", fno);
        r = readlink(proclnk, filename, MAXSIZE);
        if (r < 0)
        {
            printf("failed to readlink\n");
            exit(1);
        }
        filename[r] = '\0';
        printf("fp -> fno-> filename: %p -> %d -> %s\n", fptr, fno, filename);

    }
    return 0;
}
