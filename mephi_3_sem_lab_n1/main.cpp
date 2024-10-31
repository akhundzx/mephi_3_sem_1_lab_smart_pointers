#include "time_test.h"
#include "test.h"
#include "dinamicarray.h"
int main()
{
    test_unq_ptr_int();
    test_unq_ptr_string();
    test_unq_ptr_int_arr();
    test_shared_ptr_int();
    test_linked_list();
    test_shared_ptr_arr_int();
    test_dinamic_array();
    compare();
}
