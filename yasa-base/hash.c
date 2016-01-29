//
// hash.h
//
// interface for the hash function, which is
//    used for mapping commands to functions
//

#include "hash.h"

// Basically just convert charachters to their ordinals and append
// i.e. hash(aaa) = 10101, hash(zzz) = 262626
int hash(char *str) {
  int hash = 0;
  char c;
  while ((c = *str++)) {
    hash = hash*100 + c-'a'+1;
  }
  return hash;
}


// //Uncomment to generate hashes for new operations
//
// #include <stdio.h>
// int main(int argc, char const *argv[]) {
//   printf("%d", hash("mod"));
//   return 0;
// }