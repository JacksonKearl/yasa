//
// io.c
//
// Functions for reading from either the file or REPL. Provides comment
//   functionality.
//

#include <stdlib.h>
#include <stdio.h>
#include "io.h"

// Currently used in file mode to avoid needing to reallocate memory every
//   so often.
int count_lines(FILE * fp) {
  int lines = 0;

  while(!feof(fp)) {
    char ch = fgetc(fp);

    if(ch == '\n') {
      lines++;
    }
  }

  rewind(fp);
  return lines;
}


// Reads and returns a the next instruction line from the file pointer passed.
// If no memory available, exits the program.
char* readLine(FILE * fp) {
  char* buffer = (char*)malloc(sizeof(char) * LINE_LENGTH);
  do {
    fgets(buffer, LINE_LENGTH, fp);
    if (buffer == NULL) {
      fputs("Out of memory :(", stderr); exit(1);
    }

  // Keep going if a comment
  } while (buffer[0] == '#');

  return buffer;
}