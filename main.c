#include "./src/backend/gap_buffer.h"
#include "stddef.h"
#include "stdio.h"

int main(void){

  // The Gap_Buffer_Struct is defined in src/backend/gap_buffer.h
  // Its definition is:
  // struct Gap_Buffer_Struct{
  //     char* buffer;
  //     size_t capacity;
  //     size_t content_len;
  //     struct Cursor cursor;
  //     struct Gap gap;
  // };

  struct Gap_Buffer_Struct *gp = gp_create();
  printf("Capacity: %li\n", gp->capacity);
  gp_destroy(gp);

  return 0;
}
