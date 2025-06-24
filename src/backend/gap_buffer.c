#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./gap_buffer.h"

void gp_destroy(struct Gap_Buffer_Struct* gp){
  if (gp == NULL) {
    return; // prevent double-free.
  }
  free(gp->buffer);
  free(gp);
  gp = NULL;
}

void gp_move_cursor(struct Gap_Buffer_Struct* gp, size_t position) {

  if (gp == NULL || position == gp->gap.start) {
    // No move needed.
    return;
  }

  if (position < gp->gap.start) {
    // --- MOVE CURSOR LEFT ---
    size_t chunk_len = gp->gap.start - position;
    char* source = gp->buffer + position;
    char* destination = gp->buffer + gp->gap.end - chunk_len;

    memmove(destination, source, chunk_len);

    gp->gap.start = position;
    gp->gap.end = gp->gap.start + gp->gap.size;

  } else { // position > gp->gap.start
    // --- MOVE CURSOR RIGHT ---

    size_t chunk_len = position - gp->gap.start;
    char* source = gp->buffer + gp->gap.end;
    char* destination = gp->buffer + gp->gap.start;

    memmove(destination, source, chunk_len);

    gp->gap.start = position;
    gp->gap.end = gp->gap.end + chunk_len;
  }
  gp->cursor.position = gp->gap.start - 1;
}

char* gp_get_buffer_content(struct Gap_Buffer_Struct* gp){
  size_t buffer_1_len = gp->gap.start;
  size_t buffer_2_len = gp->content_len - buffer_1_len;

  char* text = malloc(gp->content_len + 2);
  memcpy(text, gp->buffer, buffer_1_len);
  memcpy(text + buffer_1_len, ":", 1);
  memcpy(text + buffer_1_len + 1, gp->buffer + gp->gap.end, buffer_2_len);
  text[gp->content_len] = '\0';
  return text;
}

void gp_insert(struct Gap_Buffer_Struct *gp, char c){
  if (gp != NULL){
    gp->buffer[gp->gap.start] = c;
    gp->content_len += 1;
    if (gp->gap.start + 1 != gp->gap.end){
      gp->gap.start += 1;
      gp->gap.size -= 1;
    } else {
// start and end are the same -> buffer is full;
      gp_resize(gp, gp->capacity + 4096);
      gp->gap.size = 4096;
    }
    gp->cursor.position++;
  }
}

void gp_delete(struct Gap_Buffer_Struct* gp){
  if (gp == NULL) return;
  if (gp->gap.start == 0) return;
  gp->buffer[gp->gap.start] = 0;
  gp->content_len--;
  gp->gap.start--;
  gp->gap.size++;
  gp->cursor.position--;

}

struct Gap_Buffer_Struct* gp_resize(struct Gap_Buffer_Struct* gp, size_t new_capacity){
  return realloc(gp, new_capacity);
}

struct Gap_Buffer_Struct* gp_create() {
  struct Gap_Buffer_Struct* gp = malloc(sizeof(struct Gap_Buffer_Struct)); 

  gp->capacity = 4096;
  gp->buffer = (char*) malloc(gp->capacity);
  gp->content_len = 0;

  struct Cursor c = { .position = 0 };
  gp->cursor = c;
  
// gap is always located at cursor position;
// in new buffer, takes up all space;
  struct Gap g = { .start = gp->cursor.position, .end = gp->cursor.position + (int) gp->capacity, .size = (gp->cursor.position + (int) gp->capacity) - gp->cursor.position };
  gp->gap = g;

  return gp;
}
