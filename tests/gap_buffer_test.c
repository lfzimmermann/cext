#include "gap_buffer_test.h"
#include "../src/backend/gap_buffer.h"
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_create_gap_buffer(void){
    struct Gap_Buffer_Struct* gp = gp_create();
    CU_ASSERT_TRUE(gp != NULL);
    free(gp->buffer);
    free(gp);
}

void test_destroy_gap_buffer(void){
    struct Gap_Buffer_Struct* gp = gp_create();
    gp_destroy(gp);

}

void test_delete_char(void){
    struct Gap_Buffer_Struct* gp = gp_create();
    { // insert mock 'T'
        gp->buffer[gp->gap.start] = 'T';
        gp->content_len += 1;
        gp->gap.start++;
        gp->gap.size--;
    }
    CU_ASSERT_TRUE(gp->content_len == 1);
    CU_ASSERT_TRUE(strcmp(gp_get_buffer_content(gp), "T:")); // TODO, remove ':' character for visualization
    gp_delete(gp);
    CU_ASSERT_TRUE(gp->content_len == 0);
    CU_ASSERT_TRUE(strcmp(gp_get_buffer_content(gp), ":")); // TODO, remove ':' character for visualization
    gp_destroy(gp);

}

void test_insert_char(void){
    struct Gap_Buffer_Struct* gp = gp_create();
    CU_ASSERT_TRUE(gp->content_len == 0);
    CU_ASSERT_TRUE(strcmp(gp_get_buffer_content(gp), ":")); // TODO, remove ':' character for visualization
    gp_insert(gp, 'T');
    CU_ASSERT_TRUE(gp->content_len == 1);
    CU_ASSERT_TRUE(strcmp(gp_get_buffer_content(gp), "T:")); // TODO, remove ':' character for visualization
    gp_destroy(gp);

}

void test_move_cursor(void){
    return;
}
