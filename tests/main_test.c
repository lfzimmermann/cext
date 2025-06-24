#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "main_test.h"
#include "gap_buffer_test.h"

int main(){
    CU_pSuite suite;
    CU_initialize_registry();
    suite = CU_add_suite("basic tests.", NULL, NULL);
    CU_add_test(suite, "Insert char.", test_insert_char);
    CU_add_test(suite, "Delete char.", test_delete_char);
    CU_add_test(suite, "Create gap_buffer.", test_create_gap_buffer);
    CU_add_test(suite, "Destroy gap_buffer.", test_destroy_gap_buffer);
    CU_add_test(suite, "Test for correct cursor movement.", test_move_cursor);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
