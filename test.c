#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "funcs.h"

int main() {
    printf("=== Running Vector Tests ===\n");
    
    printf("Test 1: create_vector\n");
    Vector v = create_vector(2, copy_int, delete_int);
    assert(v.size == 0);
    assert(v.capacity >= 2);
    assert(v.data != NULL);
    printf("✓ create_vector passed\n");
    
    printf("Test 2: push_back_vector\n");
    push_back_vector(&v, 10);  // Передаем значения, а не указатели
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    assert(v.size == 3);
    assert(v.capacity >= 3);
    
    // get_at_vector теперь возвращает int, а не указатель
    int elem0 = get_at_vector(&v, 0);
    int elem1 = get_at_vector(&v, 1);
    int elem2 = get_at_vector(&v, 2);
    assert(elem0 == 10);
    assert(elem1 == 20);
    assert(elem2 == 30);
    // Больше не нужно free, так как получаем значения
    printf("✓ push_back_vector passed\n");
    
    printf("Test 3: delete_at_vector\n");
    delete_at_vector(&v, 1);  // Удаляем элемент с индексом 1 (20)
    assert(v.size == 2);
    
    int elem0_after = get_at_vector(&v, 0);
    int elem1_after = get_at_vector(&v, 1);
    assert(elem0_after == 10);
    assert(elem1_after == 30);  // Теперь 30 на позиции 1
    printf("✓ delete_at_vector passed\n");
    
    printf("Test 4: copy_vector\n");
    Vector v2 = create_vector(1, copy_int, delete_int);
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
    
    Vector v4 = create_vector(2, copy_int, delete_int);
    push_back_vector(&v4, 99);  // Добавляем другое значение
    assert(is_equal_vector(&v, &v4) == 0);
    printf("✓ is_equal_vector passed\n");
    
    printf("Test 7: edge cases\n");
    // Тест пустого вектора
    Vector empty = create_vector(0, copy_int, delete_int);
    assert(empty.size == 0);
    assert(empty.capacity >= 1);
    
    // Тест получения за пределами размера
    int out_of_bounds = get_at_vector(&v, 100);
    assert(out_of_bounds == 0);  // Должен вернуть 0 для невалидного индекса
    
    // Тест удаления за пределами размера
    size_t old_size = v.size;
    delete_at_vector(&v, 100);  // Не должно ничего сделать
    assert(v.size == old_size);
    printf("✓ edge cases passed\n");
    
    printf("Test 8: erase_vector\n");
    erase_vector(&v);
    assert(v.size == 0);
    assert(v.capacity == 0);
    assert(v.data == NULL);
    printf("✓ erase_vector passed\n");
    
    printf("Test 9: delete_vector\n");
    delete_vector(v3);
    printf("✓ delete_vector passed\n");
    
    // Очистка оставшихся векторов
    erase_vector(&v2);
    erase_vector(&v4);
    erase_vector(&empty);
    
    printf("\n🎉 All tests passed! (9/9)\n");
    return 0;
}