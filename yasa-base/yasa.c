//
// yasa.c
//
// The main chunk of the program. Provides for interpreting lines and
//    altering the state of the VM
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "yasa.h"
#include "hash.h"
#include "io.h"

// Probably not good practice to define these globally, but eh.
// vars $a-$z, and $ (temp)
int script_vars[27] = {0};
int* script_arr;
int stack_pos = 0;

// Local copy of the script, along with where we are in it
char** script;
int current_line = 0;

// Jump value 0 means execute normally
// Jump value -1 means jump, but continue to check eif's
// Jump value -2 means go straight to end
int jump = 0;

// How deep into iff's we are. Used in dealing with end's
int nest_count = 0;

// If we're reading from file or stdin. 0 = file, 1 = console,
//      2 = -r enabled  (no autonewline, for redirection/piping)
int REPL = 0;


// the meat of it. pretty self explanitory.
void interpret(char* line) {
  //fputs(line, stdout);
  char cmd[4] = {0};
  strncpy(cmd, line, 3);
  line += 4;

  int cmd_hash = hash(cmd);


  // Jump value 0 means execute normally
  // Jump value -1 means jump, but continue to check eif's
  // Jump value -2 means go straight to end
  if (jump == -2 && cmd_hash != END) {
    return;
  }

  if (jump && cmd_hash != LBL &&
              cmd_hash != EIF &&
              cmd_hash != ELS &&
              cmd_hash != END) {
    return;
  }

  // the max three arguments passed to each command
  char args[3][16] = {0};
  int argc = sscanf(line, "%s %s %s", args[0], args[1], args[2]);

  int* vars[3] = {0};
  int literals[3] = {0};

  for (int  i = 0; i < argc; i++) {
    if (args[i][0] == '$') {
      // if just $, store to temp
      if (!args[i][1]) { vars[i] = &script_vars[26]; }
      else { vars[i] = script_vars + args[i][1] - 'a'; }
    } else {
      literals[i] = atoi(args[i]);
      vars[i] = &literals[i];
    }
  }


  switch (hash(cmd)) {
    case CPY:
      *vars[1] = *vars[0];
      break;
    case SHO:
      printf("%d", *vars[0]);
      if (REPL == 1) {
        puts("");
      }
      break;
    case DIS:
      printf("%c", (char)*vars[0]);
      if (REPL == 1) {
        puts("");
      }
      break;
    case INC:
      *vars[0] = *vars[0] + 1;
      break;
    case DEC:
      *vars[0] = *vars[0] - 1;
      break;
    case IIN:;
      char int_str[16];
      fgets(int_str, 16, stdin);
      *vars[0] = atoi(int_str);
      break;
    case CIN:;
      char char_str[4];
      fgets(char_str, 4, stdin);
      *vars[0] = char_str[0];
    break;
    case PUS:
      script_arr[stack_pos++] = *vars[0];
      break;
    case POP:
      if (stack_pos == 0) {
        // IGNORE ALLLLL THE ERRORSSSSSSSS
        fputs("POP'd empty stack", stderr);
        break;
      }
      *vars[0] = script_arr[--stack_pos];
      break;
    case PUT:
      script_arr[*vars[1]] = *vars[0];
      break;
    case GET:
      *vars[0] = script_arr[*vars[1]];
      break;
    case ADD:
      *vars[2] = *vars[0] + *vars[1];
      break;
    case SUB:
      *vars[2] = *vars[0] - *vars[1];
      break;
    case MUL:
      *vars[2] = *vars[0] * *vars[1];
      break;
    case DIV:
      if ( *vars[1] == 0 )
      {
        fputs("Attempted to divide by 0", stderr);
        break;
      }
      *vars[2] = *vars[0] / *vars[1];
      break;
    case RAN:
      if ( *vars[0] < 2 )
      {
        fputs("Attempted to modulo less than 2", stderr);
        break;
      }
      *vars[1] = rand() % *vars[0];
      break;
    case MOD:
      if ( *vars[1] < 2 )
      {
        fputs("Attempted to modulo less than 2", stderr);
        break;
      }
      *vars[2] = *vars[0] % *vars[1];
      break;
    case EQL:
      *vars[2] = (*vars[0] == *vars[1]) ? 1 : 0;
      break;
    case GRT:
      *vars[2] = *vars[0] > *vars[1] ? 1 : 0;
      break;
    case IFF:
      // Jump value 0 means execute normally
      // Jump value -1 means jump, but continue to check eif's
      // Jump value -2 means go straight to end
      nest_count++;
      if (*vars[0]) { jump = 0; break; }
      else { jump = -1; }
      break;
    case EIF:
      if (jump == 0 ) {jump = -2; break;}
      if (*vars[0]) { jump = 0; break; }
      else { jump = -1; }
      break;
    case ELS:
      if (jump == -1) { jump = 0; }
      else { jump = -2; }
      break;
    case END:
      jump = 0;
      if (nest_count == 0) {
        exit(0);
      }
      nest_count--;
      break;
    case LBL:;
      if (jump == *vars[0]) {
        jump = 0;
      }
      break;
    case MOV:;
      jump = *vars[0];
      current_line = -1;
      break;
  }
}


int main(int argc, char const *argv[]) {
  FILE *fp;
  int num_lines;

  script_arr = malloc(sizeof(int) * ARR_LENGTH);
  srand(time(NULL));

  if (argc == 1 || (argc == 2 && argv[1][1] == 'r')) {
    // REPL mode
    REPL = 1;
    if (argc == 2 && argv[1][1] == 'r') REPL = 2;
    fp = stdin;
    num_lines = REPL_LENGTH;
  } else {
    // normal mode
    fp = fopen(argv[1], "r");
    if (!fp) {
      printf("File %s could not be opened :/\n", argv[1]);
      return 1;
    }

    num_lines = count_lines(fp);
  }

  script = (char**)calloc(num_lines, sizeof(char*));

  while (1) {

    // If we're out of preallocated memory for lines, double our memory
    //    Only applies in REPL mode, as memory is allocated beforehad in
    //    file mode
    if (REPL && current_line == num_lines) {
      num_lines *= 2;
      script = (char**)realloc(script, num_lines);
      if (script == NULL) {
        fputs("Out of memory :(", stderr); return 1;
      }
      for (int i = num_lines/2; i < num_lines; i++) {
        script[i] = NULL;
      }
    }

    // check for null so that we don't write over old lines in jump commands
    if (script[current_line] == NULL) {
      script[current_line] = readLine(fp);
    }

    interpret(script[current_line]);
    current_line++;
  }

  return 0;
}