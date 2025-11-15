#include "funcs.h"

Vector create_vector(size_t initial_capacity, VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE)) {
    Vector vector;
    vector.size = 0;
    if (initial_capacity == 0) {
        vector.capacity = 1;
    }
    else {
        vector.capacity = initial_capacity;
    }

    vector.CopyVoidPtr = CopyFunc;
    vector.DeleteVoidPtr = DeleteFunc;

    vector.data = malloc(sizeof(VECTOR_TYPE) * vector.capacity);
    if (vector.data == NULL) {
        vector.capacity = 0;
    }

    return vector;
}

void erase_vector(Vector *v) {
    if (v == NULL) {
        return;
    }

    if (v->data != NULL) {
        for (size_t i = 0; i < v->size; i++) {
            if (v->DeleteVoidPtr != NULL) {
                v->DeleteVoidPtr(v->data[i]);
            }
        }
        free(v->data);
        v->data = NULL;
    }

    v->size = 0;
    v->capacity = 0;
}

int is_equal_vector(const Vector *v1, const Vector *v2) {
    if (v1 == NULL && v2 == NULL) {
        return 1;
    }
    
    if (v1 == NULL || v2 == NULL) {
        return 0;
    }

    if (v1->size != v2->size) {
        return 0;
    }

    for (size_t i = 0; i < v1->size; i++) {
        if (v1->data[i] != v2->data[i]) {
            return 0;
        }
    }
    return 1;
}

void copy_vector(Vector *dest, const Vector *src) {
    if (dest == NULL || src == NULL) {
        return;
    }

    erase_vector(dest);

    dest->capacity = src->capacity;
    dest->size = src->size;
    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;

    dest->data = malloc(sizeof(VECTOR_TYPE) * src->capacity);
    if (dest->data == NULL) {
        dest->capacity = 0;
        dest->size = 0;
        return;
    }

    for (size_t i = 0; i < src->size; i++) {
        if (src->CopyVoidPtr != NULL) {
            dest->data[i] = src->CopyVoidPtr(src->data[i]);
        }
        else {
            dest->data[i] = src->data[i];
        }
    }
}

Vector *copy_vector_new(const Vector *src) {
    if (src == NULL) {
        return NULL;
    }

    Vector *new_vector = malloc(sizeof(Vector));
    if (new_vector == NULL) {
        return NULL;
    }

    new_vector->capacity = src->capacity;
    new_vector->size = src->size;
    new_vector->CopyVoidPtr = src->CopyVoidPtr;
    new_vector->DeleteVoidPtr = src->DeleteVoidPtr;

    new_vector->data = malloc(sizeof(VECTOR_TYPE) * src->capacity);
    if (new_vector->data == NULL) {
        free(new_vector);
        return NULL;
    }

    for (size_t i = 0; i < src->size; i++) {
        if (src->CopyVoidPtr != NULL) {
            new_vector->data[i] = src->CopyVoidPtr(src->data[i]);
        }
        else {
            new_vector->data[i] = src->data[i];
        }
    }
    return new_vector;
}

void push_back_vector(Vector *v, VECTOR_TYPE value) {
    if (v == NULL) {
        return;
    }

    if (v->size >= v->capacity) {
        size_t new_capacity;
        if (v->capacity == 0) {
            new_capacity = 1;
        }
        else {
            new_capacity = v->capacity * 2;
        }
    
        VECTOR_TYPE *new_data = realloc(v->data, sizeof(VECTOR_TYPE) * new_capacity);
        if (new_data == NULL) {
            return;
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }

    if (v->CopyVoidPtr != NULL) {
        v->data[v->size] = v->CopyVoidPtr(value);
    }
    else {
        v->data[v->size] = value;
    }
    v->size++;
}

void delete_at_vector(Vector *v, size_t index) {
    if (v == NULL) {
        return;
    }

    if (index >= v->size) {
        return;
    }

    if (v->DeleteVoidPtr != NULL) {
        v->DeleteVoidPtr(v->data[index]);
    }

    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->size--;
}

VECTOR_TYPE get_at_vector(const Vector *v, size_t index) {
    if (v == NULL) {
        return NULL;
    }

    if (index >= v->size) {
        return NULL;
    }

    if (v->CopyVoidPtr != NULL) {
        return v->CopyVoidPtr(v->data[index]);
    }
    else {
        return v->data[index];
    }
}

void delete_vector(Vector *v) {
    if (v == NULL) {
        return;
    }

    erase_vector(v);
    free(v);
}