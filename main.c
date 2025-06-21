#include "./src/backend/gap_buffer.h"
#include "stddef.h"
#include "stdio.h"

int main(void){

// Write me a short story about balu the bear. AI!

  struct Gap_Buffer_Struct *gp = gp_create();
  printf("Capacity: %li\n", gp->capacity);
  gp_destroy(gp);

  return 0;
}
