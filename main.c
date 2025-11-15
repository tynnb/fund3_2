#include <stdio.h>
#include "funcs.h"

int* copy_int(int* value) {
    if (value == NULL) return NULL;
    int* copy = (int*)malloc(sizeof(int));
    *copy = *value;
    return copy;
}

void delete_int(int* value) {
    free(value);
}

int main() {
    Vector v = create_vector(2, 
        (VECTOR_TYPE(*)(VECTOR_TYPE))copy_int, 
        (void(*)(VECTOR_TYPE))delete_int
    );
    
    int a = 10, b = 20, c = 30;
    
    push_back_vector(&v, &a);
    push_back_vector(&v, &b);
    push_back_vector(&v, &c);
    
    for (size_t i = 0; i < v.size; i++) {
        int* element = (int*)get_at_vector(&v, i);
        printf("Index %zu: %d\n", i, *element);
        free(element);
    }
    
    delete_at_vector(&v, 0);
    
    for (size_t i = 0; i < v.size; i++) {
        int* element = (int*)get_at_vector(&v, i);
        printf("Index %zu: %d\n", i, *element);
        free(element);
    }
    
    Vector v2 = create_vector(1, 
        (VECTOR_TYPE(*)(VECTOR_TYPE))copy_int, (void(*)(VECTOR_TYPE))delete_int
    );
    copy_vector(&v2, &v);
    
    for (size_t i = 0; i < v2.size; i++) {
        int* element = (int*)get_at_vector(&v2, i);
        printf("Index %zu: %d\n", i, *element);
        free(element);
    }
    
    erase_vector(&v);
    erase_vector(&v2);
    return 0;
}