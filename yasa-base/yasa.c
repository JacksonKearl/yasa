#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "yasa.h"
#include "hash.h"

// Probably not good practice to define these globally, but eh.
int script_vars[26] = {0};
int* script_arr;
int stack_pos = 0;
char** script;
int current_line = 0;
int jump = 0;
int nest_count = 0;

// right now just allocate the $arr for us. Maybe more later on
void initalize_state() {
    script_arr = malloc(sizeof(int) * ARR_LENGTH);
}


// Currently needed beauce I'm not really feeling down to check for eof.
// Expect removal...
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

// the meat of it. pretty self explanitory.
void interpret(char* line) {
  //fputs(line, stdout);
  char cmd[4] = {0};
  strncpy(cmd, line, 3);
  line += 4;

  int cmd_hash = hash(cmd);

  if (jump && cmd_hash != LBL &&
              cmd_hash != EIF &&
              cmd_hash != ELS &&
              cmd_hash != END) {
    return;
  }

  // functions that accept non-$var input
  switch (cmd_hash) {
    case SET:;
      int val;
      char arg;
      sscanf(line, "%d %*c%c", &val, &arg);
      int* var = script_vars + (int)(arg - 'a');
      *var = val;
      break;
    case LBL:;
      int mark;
      sscanf(line, "%d", &mark);
      if (jump == mark) {
        jump = 0;
      }
      break;
    case MOV:
      current_line = 0;
      break;
  }

  // the max three arguments passed to each command
  char args[3] = {0};
  int argc = sscanf(line, "%*c%c %*c%c %*c%c", &args[0], &args[1], &args[2]);

  // the local memory locations where argument variables are stored
  int* vars[3] = {0};
  for (int i = 0; i < argc ; i ++) {
    vars[i] = script_vars + args[i] - 'a';
  }

  switch (hash(cmd)) {
    case CPY:
      *vars[1] = *vars[0];
      break;
    case SHO:
      printf("%d", *vars[0]);
      break;
    case DIS:
      printf("%c", *vars[0]);
      break;
    case INC:
      *vars[0] = *vars[0] + 1;
      break;
    case DEC:
      *vars[0] = *vars[0] - 1;
      break;
    case IIN:;
      int in;
      scanf("%d", &in);
      *vars[0] = in;
      break;
    case CIN:;
      *vars[0] = (int)getc(stdin);
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
      if ( *vars[1] < 2 )
      {
        fputs("Attempted to modulo less than 2", stderr);
        break;
      }
      *vars[1] = rand() % *vars[0];
      break;
    case EQL:
      *vars[2] = *vars[1] == *vars[2] ? 1 : 0;
      break;
    case GRT:
      *vars[2] = *vars[1] > *vars[2] ? 1 : 0;
      break;
    case IFF:
      if (*vars[0]) { break; };
      jump = -1;
      nest_count++;
      break;
    case EIF:
      if (!jump) { jump = -1; break;}
      if (*vars[0]) { break; };
      jump = -1;
      break;
    case ELS:
      if (jump == -1) { jump = 0; break; }
      break;
    case END:
      jump = 0;
      if (nest_count == 0) {
        exit(0);
      }
      nest_count--;
      break;
  }
}


int main(int argc, char const *argv[]) {
  FILE *fp;
  int num_lines;

  if (argc == 1) {
    // REPL mode
    fp = stdin;
    num_lines = REPL_LENGTH;
  } else {
    // normal mode
    fp = fopen(argv[1], "r");
    if (!fp) {
      printf("File %d could not be opened :/\n", argc);
      return 1;
    }

    num_lines = count_lines(fp);
  }

  script = (char**)calloc(num_lines, sizeof(char*));

  while (1) {
    if (argc == 1 && current_line == num_lines) {
      num_lines *= 2;
      script = (char**)realloc(script, num_lines);
      if (script == NULL) {
        fputs("Out of memory :(", stderr); return 1;
      }
      for (int i = num_lines/2; i < num_lines; i++) {
        script[i] = NULL;
      }
    }

    if (script[current_line] == NULL) {
      script[current_line] = (char*)malloc(sizeof(char) * LINE_LENGTH);
      fgets(script[current_line], LINE_LENGTH, fp);
    }
    interpret(script[current_line]);
    current_line++;
  }

  return 0;
}