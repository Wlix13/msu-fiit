#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *ffrom1, *ffrom2, *ffResult;

    if (argc != 3) {
        fprintf(stderr, "Usage: copy <file1> <file1> <fileResult>\n");
        return 1;
    }

    if ((ffrom1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        return 1;
    }

    if ((ffrom2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[2]);
        return 1;
    }

    if ((ffResult = fopen(argv[3], "w")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[3]);
        return 1;
    }

    if (!ffrom1 || !ffrom2 || !ffResult) {
        fprintf(stderr, "Couldn't open files\n");
        return 1;
    }

    int a1, a2, n1, n2;
    n1 = fread(&a1, sizeof(int), 1, ffrom1);
    n2 = fread(&a2, sizeof(int), 1, ffrom2);

    while (n1 && n2) {
        if (a1 >= a2) {
            fwrite(&a2, sizeof(int), 1, ffResult);
            n2 = fread(&a2, sizeof(int), 1, ffrom2);
        } else {
            fwrite(&a1, sizeof(int), 1, ffResult);
            n1 = fread(&a1, sizeof(int), 1, ffrom1);
        }
    }
    while (n1) {
        fwrite(&a1, sizeof(int), 1, ffResult);
        n1 = fread(&a1, sizeof(int), 1, ffrom1);
    }
    while (n2) {
        fwrite(&a2, sizeof(int), 1, ffResult);
        n2 = fread(&a2, sizeof(int), 1, ffrom2);
    }

    fclose(ffrom1);
    fclose(ffrom2);
    fclose(ffResult);

    return 0;
}