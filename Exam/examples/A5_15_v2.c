#include <stdio.h>

int main(int args) {
    FILE* ptr;
    char ch;
    int count = 0;

    ptr = fopen("latin.txt", "r");

    if (ptr == NULL) {
        printf("file cannot be opened.\n");
        return 1;
    }

    printf("letter count on each line from file:\n");

    while ((ch = fgetc(ptr))) {
        if (ch != '\n') {
            if (ch != ' ') {
                count++;
            }
        } else {
            printf("%d\n", count);
            count = 0;
        }
    }

    fclose(ptr);
    return 0;
}

