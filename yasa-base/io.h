//
// io.h
//
// Functions for reading from either the file or REPL. Provides comment
//   functionality.
//


// How much space we allocate per line of code.
#ifndef LINE_LENGTH
#define LINE_LENGTH 128
#endif


// Find the number of lines left in a passed file.
int count_lines(FILE * fp);


// Get a line from the stdin.
char* readLine(FILE * fp);
