#include "funcs.h"

int main() {
    Vector v = create_vector(2, copy_int, delete_int);
    
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    
    printf("Vector v after adding elements:\n");
    for (size_t i = 0; i < v.size; i++) {
        int element = get_at_vector(&v, i);
        printf("Index %zu: %d\n", i, element);
    }
    
    delete_at_vector(&v, 0);
    
    printf("\nVector v after deleting first element:\n");
    for (size_t i = 0; i < v.size; i++) {
        int element = get_at_vector(&v, i);
        printf("Index %zu: %d\n", i, element);
    }
    
    Vector v2 = create_vector(1, copy_int, delete_int);
    copy_vector(&v2, &v);
    
    printf("\nVector v2 (copy of v):\n");
    for (size_t i = 0; i < v2.size; i++) {
        int element = get_at_vector(&v2, i);
        printf("Index %zu: %d\n", i, element);
    }
    
    Vector *v3 = copy_vector_new(&v);
    printf("\nVector v3 (new copy):\n");
    for (size_t i = 0; i < v3->size; i++) {
        int element = get_at_vector(v3, i);
        printf("Index %zu: %d\n", i, element);
    }
    
    printf("\nComparison results:\n");
    printf("v == v2: %d\n", is_equal_vector(&v, &v2));
    printf("v == v3: %d\n", is_equal_vector(&v, v3));
    
    erase_vector(&v);
    erase_vector(&v2);
    delete_vector(v3);
    
    return 0;
}