#include <stdio.h>
#include "../include/file.h"


void print_file(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("打开文件失败");
  }
  char buffer[MAX_BUFFER];
  while(fgets(buffer, MAX_BUFFER, file) != NULL) {
    printf("%s", buffer);
  }
  fclose(file);
}