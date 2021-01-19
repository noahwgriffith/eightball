#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

char *roll(char *fortunes[], int size)
{
    srand(time(NULL));
    int offset = (rand() % size);
    return *(fortunes+offset);
}

int main()
{
    #define FORTUNE_BUFFER_SIZE 200 /* This defines the max byte size for each string read from the file. */
    int capacity = 10; /* set inital capacity to 10 */
    char **fortunes = malloc(capacity * sizeof(char*));

    FILE *filePointer;
    filePointer = fopen("../fortunes.txt", "r");
    char singleLine[FORTUNE_BUFFER_SIZE];
    int size = 0;
    for (int i = 0; feof(filePointer) == false; i++)
    {
        /* grow */
        if (size == capacity)
            fortunes = realloc(fortunes, (capacity += capacity) * sizeof(char*));

        fgets(singleLine, FORTUNE_BUFFER_SIZE, filePointer);

        /* find and remove '\n' */
        char *newLine = strchr(singleLine, '\n');
        if (newLine)
            *newLine = '\0';

        *(fortunes+i) = strdup(singleLine);
        size++;
    }
    fclose(filePointer);

    /* trim excess */
    fortunes = realloc(fortunes, size * sizeof(char*));

    printf("%s\n", roll(fortunes, size));

    /* deallocate */
    for (int i = 0; i < size; i++)
        free(*(fortunes+i));
    free(fortunes);
    
    return 0;
}