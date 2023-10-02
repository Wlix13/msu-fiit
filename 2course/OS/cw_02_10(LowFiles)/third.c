/*
б) Создать новый файл, вывести в него строки исходного файла, упорядочив их по
возрастанию длины. Считывать файл в память нельзя.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp, *fpNew;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <имя файла>\n", argv[0]);
    exit(1);
  }
  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    exit(1);
  }

  int line_count = 0;
  int **line_offsets = NULL;
  int **line_lengths = NULL;

  int current_line_offset = 0;
  int current_line_length = 0;
  int current_char;
  int last_char = '\n';

  while ((current_char = fgetc(fp)) != EOF) {
    if (current_char == '\n') {
      // New line
      line_offsets = realloc(line_offsets, (line_count + 1) * sizeof(int *));
      line_lengths = realloc(line_lengths, (line_count + 1) * sizeof(int *));

      // Memory for line offset and length
      line_offsets[line_count] = malloc(sizeof(int));
      line_lengths[line_count] = malloc(sizeof(int));

      // Set values
      *line_offsets[line_count] = current_line_offset;
      *line_lengths[line_count] = current_line_length;

      // Reset values
      line_count++;
      current_line_offset += current_line_length + 1;
      current_line_length = 0;
    } else {
      current_line_length++;
    }
    last_char = current_char;
  }

  // Add last line
  if (last_char != '\n') {
    line_offsets = realloc(line_offsets, (line_count + 1) * sizeof(int *));
    line_lengths = realloc(line_lengths, (line_count + 1) * sizeof(int *));

    line_offsets[line_count] = malloc(sizeof(int));
    line_lengths[line_count] = malloc(sizeof(int));

    *line_offsets[line_count] = current_line_offset;
    *line_lengths[line_count] = current_line_length;
    line_count++;
  }

  // Sort the arrays by length of each line
  for (int i = 0; i < line_count - 1; i++) {
    for (int j = 0; j < line_count - i - 1; j++) {
      if (*line_lengths[j] > *line_lengths[j + 1]) {
        int *temp_offset = line_offsets[j];
        int *temp_length = line_lengths[j];

        line_offsets[j] = line_offsets[j + 1];
        line_lengths[j] = line_lengths[j + 1];

        line_offsets[j + 1] = temp_offset;
        line_lengths[j + 1] = temp_length;
      }
    }
  }

  if ((fpNew = fopen("new.txt", "w")) == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    exit(1);
  }

  // Write sorted lines to new file
  for (int i = 0; i < line_count; i++) {
    fseek(fp, *line_offsets[i], SEEK_SET);
    for (int j = 0; j < *line_lengths[i]; j++) {
      int current_char = fgetc(fp);
      if (current_char != EOF) {
        fputc(current_char, fpNew);
      }
    }
    fputc('\n', fpNew);
  }

  // Free memory
  for (int i = 0; i < line_count; i++) {
    free(line_offsets[i]);
    free(line_lengths[i]);
  }
  free(line_offsets);
  free(line_lengths);

  fclose(fp);
  fclose(fpNew);

  return 0;
}