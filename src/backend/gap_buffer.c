#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./gap_buffer.h"
int main(int argc, char** argv){
  
  char msg[] = "Hello, world!";
  struct Gap_Buffer_Struct *gp = gp_create();
  printf("Capacity: %d\n", gp->capacity);

  for (int i = 0; i < 16; i++){
    gp_insert(gp, msg[i]);
    printf("Content: %s\nGap Size: %d\n\n", gp_get_buffer_content(gp), gp->gap.end - gp->gap.start);
    
  }

  gp_move_cursor(gp, 2);
  printf("Cursor positions: \nactual %d;\nlogical %d\n", gp->cursor.actual_position, gp->cursor.logical_position);

  gp_move_cursor(gp, 2 + gp->gap.size);
  printf("Cursor positions: \nactual %d;\nlogical %d\n", gp->cursor.actual_position, gp->cursor.logical_position);

  gp_destroy(gp);

  return 0;
}

void gp_destroy(struct Gap_Buffer_Struct* gp){
  if (gp == NULL) {
    return; // prevent double-free.
  }

  free(gp->buffer);
  free(gp);

}

void gp_move_cursor(struct Gap_Buffer_Struct* gp, unsigned int logical_position) {
    if (gp == NULL || logical_position == gp->gap.start) {
        // No move needed.
        return;
    }

    if (logical_position < gp->gap.start) {
        // --- MOVE CURSOR LEFT --- 
        gp->cursor.logical_position = logical_position;
        gp->cursor.actual_position = logical_position;

        size_t chunk_len = gp->gap.start - logical_position;
        char* source = gp->buffer + logical_position;
        char* destination = gp->buffer + gp->gap.end - chunk_len;

        memmove(destination, source, chunk_len);

        gp->gap.start = logical_position;
        gp->gap.end = gp->gap.start + gp->gap.size;

    } else { // logical_position > gp->gap.start
        // --- MOVE CURSOR RIGHT --- 
        gp->cursor.logical_position = logical_position;
        
        // The physical position must jump over the gap.
        // We calculate this BEFORE we move the gap.
        gp->cursor.actual_position = gp->gap.end + (logical_position - gp->gap.start);

        size_t chunk_len = logical_position - gp->gap.start;
        char* source = gp->buffer + gp->gap.end;
        char* destination = gp->buffer + gp->gap.start;

        memmove(destination, source, chunk_len);

        gp->gap.start = logical_position;
        gp->gap.end = gp->gap.end + chunk_len;
    }
}

char* gp_get_buffer_content(struct Gap_Buffer_Struct* gp){
  size_t buffer_1_len = gp->gap.start;
  size_t buffer_2_len = gp->capacity - buffer_1_len - gp->gap.size;

  char* text = malloc(buffer_1_len + buffer_2_len);
  memcpy(text, gp->buffer, buffer_1_len);
  memcpy(text + buffer_1_len, gp->buffer + gp->gap.end, buffer_2_len);
  return text;
}

void gp_insert(struct Gap_Buffer_Struct *gp, char c){
  if (gp != NULL){
    gp->buffer[gp->gap.start] = c; 
    if (gp->gap.start + 1 != gp->gap.end){
      gp->gap.start += 1;
      gp->gap.size -= 1;
    } else {
// start and end are the same -> buffer is full;
      gp_resize(gp, gp->capacity + 4096);
      gp->gap.size = 4096;
    }
  }
}

struct Gap_Buffer_Struct* gp_resize(struct Gap_Buffer_Struct* gp, size_t new_capacity){
  return realloc(gp, new_capacity);
}

struct Gap_Buffer_Struct* gp_create() {
  struct Gap_Buffer_Struct* gp = malloc(sizeof(struct Gap_Buffer_Struct)); 

  gp->capacity = 4096;
  gp->buffer = (char*) malloc(gp->capacity);

  struct Cursor c = { .logical_position = 0, .actual_position = 0 };
  gp->cursor = c;
  
// gap is always located at cursor position;
// in new buffer, takes up all space;
  struct Gap g = { .start = gp->cursor.logical_position, .end = gp->cursor.logical_position + (int) gp->capacity, .size = (gp->cursor.logical_position + (int) gp->capacity) - gp->cursor.logical_position };
  gp->gap = g;

  return gp;
}
