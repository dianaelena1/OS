#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CLASSES   100
#define MAX_NAME_LEN  64
#define MAX_OCCURS    500
#define MAX_LINE_LEN  1024

typedef struct {
    char name[MAX_NAME_LEN];
    int  count;
    int  lines[MAX_OCCURS];
} ClassInfo;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source.cpp>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("fopen");
        return 1;
    }

    ClassInfo classes[MAX_CLASSES];
    int nclass = 0;
    char line[MAX_LINE_LEN];

    while (fgets(line, sizeof(line), f)) {
        char *p = strstr(line, "class ");
        if (!p) continue;
        p += 6;
        while (*p && isspace((unsigned char)*p)) p++;
        if (isalpha((unsigned char)*p) || *p == '_') {
            char name[MAX_NAME_LEN] = {0};
            int i = 0;
            while (*p && (isalnum((unsigned char)*p) || *p == '_') && i < MAX_NAME_LEN-1)
                name[i++] = *p++;
            int found = 0;
            for (int j = 0; j < nclass; j++) {
                if (strcmp(classes[j].name, name) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found && nclass < MAX_CLASSES) {
                strcpy(classes[nclass].name, name);
                classes[nclass].count = 0;
                nclass++;
            }
        }
    }

    if (nclass == 0) {
        printf("No classes found in %s\n", argv[1]);
        fclose(f);
        return 0;
    }

    rewind(f);
    int lineno = 0;

    while (fgets(line, sizeof(line), f)) {
        lineno++;
        for (int i = 0; i < nclass; i++) {
            char pattern[MAX_NAME_LEN + 5];
            snprintf(pattern, sizeof(pattern), "new %s", classes[i].name);
            char *q = line;
            while ((q = strstr(q, pattern)) != NULL) {
                if (classes[i].count < MAX_OCCURS)
                    classes[i].lines[classes[i].count++] = lineno;
                q += strlen(pattern);
            }
        }
    }
    fclose(f);

    for (int i = 0; i < nclass; i++) {
        printf("Class %s: %d new-instance(s)", classes[i].name, classes[i].count);
        if (classes[i].count) {
            printf(" at lines");
            for (int k = 0; k < classes[i].count; k++)
                printf(" %d", classes[i].lines[k]);
        }
        printf("\n");
    }

    return 0;
}

