#include <stdio.h>


int main(int argc, char const *argv[]) {
  char c = '\0';
  FILE *fp;

  fp = fopen(argv[1], "r");
  if (!fp) {
    printf("File %s could not be opened :/\n", argv[1]);
    return 1;
  }
  int next_lbl_mark = 10;
  int lbl_marks[128] = {0};
  int close_mark_pos = 0;

  int in_comment = 0;

  printf("cpy 0 $p   # Initialize data pointer");

  do {
    c = fgetc(fp);

    switch (c) {
      case '>':
        printf("\ninc $p");
        break;
      case '<':
        printf("\ndec $p");
        break;
      case '+':
        printf("\nget $ $p\ninc $\nput $ $p");
        break;
      case '-':
        printf("\nget $ $p\ndec $\nput $ $p");
        break;
      case '.':
        printf("\nget $ $p\ndis $");
        break;
      case ',':
        printf("\ncin $\nput $ $p");
        break;
      case '[':
        printf("\nlbl -%d\nget $ $p\neql $ 0 $\nmov %d $", next_lbl_mark, next_lbl_mark);
        lbl_marks[close_mark_pos] = next_lbl_mark;
        next_lbl_mark++;
        close_mark_pos++;
        break;
      case ']':
        close_mark_pos--;
        printf("\nmov -%d\nlbl %d", lbl_marks[close_mark_pos], lbl_marks[close_mark_pos]);
        break;
      case '\n':
      case '\t':
      case ' ':
        break;
      default:
        printf("\n#");
        while (c != EOF  && c != '\n' && \
               c != ','  && c != '.'  && \
               c != '-'  && c != '+'  && \
               c != '<'  && c != '>'  && \
               c != '['  && c != ']') {
            printf("%c", c);
            c = fgetc(fp);
        }
        ungetc(c, fp);
    }
  } while (c != EOF);
  puts("\nend");
  return 0;
}