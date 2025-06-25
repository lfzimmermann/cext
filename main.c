#include "stddef.h"
#include "stdio.h"

#include "./src/backend/gap_buffer.h"
#include "./src/frontend/gui.h"

int main(void){

  struct Gap_Buffer_Struct *gp = gp_create();

  run_ed_gui(gp);

  gp_destroy(gp);

  return 0;
}
