#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "funcs.h"

int main() {
    printf("=== Running Vector Tests ===\n");
    
    printf("Test 1: create_vector\n");
    Vector v = create_vector(2, 
        (VECTOR_TYPE(*)(VECTOR_TYPE))copy_int, 
        (void(*)(VECTOR_TYPE))delete_int
    );
    assert(v.size == 0);
    assert(v.capacity >= 2);
    assert(v.data != NULL);
    printf("✓ create_vector passed\n");
    
    printf("Test 2: push_back_vector\n");
    int a = 10, b = 20, c = 30;
    push_back_vector(&v, &a);
    push_back_vector(&v, &b);
    push_back_vector(&v, &c);
    assert(v.size == 3);
    assert(v.capacity >= 3);
    
    int* elem0 = (int*)get_at_vector(&v, 0);
    int* elem1 = (int*)get_at_vector(&v, 1);
    int* elem2 = (int*)get_at_vector(&v, 2);
    assert(*elem0 == 10);
    assert(*elem1 == 20);
    assert(*elem2 == 30);
    free(elem0); free(elem1); free(elem2);
    printf("✓ push_back_vector passed\n");
    
    printf("Test 3: delete_at_vector\n");
    delete_at_vector(&v, 1);
    assert(v.size == 2);
    
    int* elem0_after = (int*)get_at_vector(&v, 0);
    int* elem1_after = (int*)get_at_vector(&v, 1);
    assert(*elem0_after == 10);
    assert(*elem1_after == 30);
    free(elem0_after); free(elem1_after);
    printf("✓ delete_at_vector passed\n");
    
    printf("Test 4: copy_vector\n");
    Vector v2 = create_vector(1, 
        (VECTOR_TYPE(*)(VECTOR_TYPE))copy_int, 
        (void(*)(VECTOR_TYPE))delete_int
    );
    copy_vector(&v2, &v);
    assert(v2.size == 2);
    assert(is_equal_vector(&v, &v2) == 1);
    printf("✓ copy_vector passed\n");
    
    printf("Test 5: copy_vector_new\n");
    Vector* v3 = copy_vector_new(&v);
    assert(v3 != NULL);
    assert(v3->size == 2);
    assert(is_equal_vector(&v, v3) == 1);
    printf("✓ copy_vector_new passed\n");
    
    printf("Test 6: is_equal_vector\n");
    assert(is_equal_vector(&v, &v2) == 1);
    assert(is_equal_vector(&v, v3) == 1);
    
    Vector v4 = create_vector(2, 
        (VECTOR_TYPE(*)(VECTOR_TYPE))copy_int, 
        (void(*)(VECTOR_TYPE))delete_int
    );
    int d = 99;
    push_back_vector(&v4, &d);
    assert(is_equal_vector(&v, &v4) == 0);
    printf("✓ is_equal_vector passed\n");
    
    printf("Test 7: erase_vector\n");
    erase_vector(&v);
    assert(v.size == 0);
    assert(v.capacity == 0);
    assert(v.data == NULL);
    printf("✓ erase_vector passed\n");
    
    printf("Test 8: delete_vector\n");
    delete_vector(v3);
    printf("✓ delete_vector passed\n");
    
    erase_vector(&v2);
    erase_vector(&v4);
    
    printf("\nAll tests passed!\n");
    return 0;
}