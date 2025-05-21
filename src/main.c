#include "gap.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv){
  line_buffer lb = {0};
  lb.line_length = 0;
  lb.chars = malloc(256*sizeof(char));
  strcpy(lb.chars, "Hello, world!");
  lb.line_length += strlen(lb.chars);
  printf("%s\n", lb.chars);
  printf("%d\n", lb.line_length);

  return 0;
}
