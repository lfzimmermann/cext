#include "./src/backend/gap_buffer.h"
#include "stddef.h"
#include "stdio.h"

int main(int argc, char** argv){
  
  char msg[] = "Hello, world!";
  struct Gap_Buffer_Struct *gp = gp_create();
  printf("Capacity: %li\n", gp->capacity);

  for (int i = 0; i < 16; i++){
    gp_insert(gp, msg[i]);
    printf("Content: %s\nGap Size: %li\n\n", gp_get_buffer_content(gp), gp->gap.end - gp->gap.start);
    
  }

  gp_move_cursor(gp, 2);
  printf("Cursor positions: \nactual %d;\nlogical %d\n", gp->cursor.actual_position, gp->cursor.logical_position);

  gp_move_cursor(gp, 2 + gp->gap.size);
  printf("Cursor positions: \nactual %d;\nlogical %d\n", gp->cursor.actual_position, gp->cursor.logical_position);

  gp_destroy(gp);

  return 0;
}
