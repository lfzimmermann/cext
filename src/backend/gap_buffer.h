#include <stddef.h>
struct Cursor{
  unsigned int logical_position; // with gap
  unsigned int actual_position; // without gap; only actual text
};

struct Gap{
 size_t start;
 size_t end;
 size_t size;
};


struct Gap_Buffer_Struct{
  char* buffer;
  size_t capacity;
  struct Cursor cursor;
  struct Gap gap;
};

struct Gap_Buffer_Struct* gp_create();
void gp_destroy(struct Gap_Buffer_Struct* gp);
void gp_insert(struct Gap_Buffer_Struct *gp, char c);
char* gp_get_buffer_content(struct Gap_Buffer_Struct* gp);

void gp_move_cursor(struct Gap_Buffer_Struct* gp, unsigned int logical_position);
struct Gap_Buffer_Struct* gp_resize(struct Gap_Buffer_Struct* gp, size_t new_capacity);
