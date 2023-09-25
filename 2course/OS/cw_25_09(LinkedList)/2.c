#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *ffrom1;
    FILE *temp;
    char c;
    if (argc != 3) {
        fprintf(stderr, "Usage: remove <file> <char>\n");
        return 1;
    }

    if ((ffrom1 = fopen(argv[1], "r+")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        return 1;
    }
    if (!ffrom1) {
        fprintf(stderr, "Couldn't open files\n");
        return 1;
    }

    if ((temp = fopen("_write_temp.txt", "w")) == NULL) {
        fprintf(stderr, "Cannot open temporary work file.\n\n");
    }

    while ((c = fgetc(ffrom1)) != EOF) {
        if (c != argv[2][0]) {
            fputs(&c, temp);
        }
    }

    fclose(ffrom1);
    fclose(temp);
    remove(argv[1]);
    rename("_write_temp.txt", argv[1]);
    return 0;
}