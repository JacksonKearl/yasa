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
    printf("\n#");
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
        printf("\nget $ $p\neql $ 0 $\niff $\nmov %d\nend\nlbl -%d", next_lbl_mark, next_lbl_mark);
        lbl_marks[close_mark_pos] = next_lbl_mark;
        next_lbl_mark++;
        close_mark_pos++;
        break;
      case ']':
        close_mark_pos--;
        printf("\nget $ $p\niff $\nmov -%d\nend\nlbl %d", lbl_marks[close_mark_pos], lbl_marks[close_mark_pos]);
        break;
    }
  } while (c != EOF);
  puts("\nend");
  return 0;
}