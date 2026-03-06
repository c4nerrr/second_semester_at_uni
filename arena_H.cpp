//
// Created by c4ner on 3/5/2026.
//

#include "arena_H.h"
#include <new> //для std::nothrow

arenka* arena_new(uint64_t size) {
    if (size == 0) {
        return nullptr;
    }
    arenka* a = new(std::nothrow) arenka;//носров від краша сейвіт
    if (a == nullptr) {
        return nullptr;
    }
    a->memory = new(std::nothrow) uint8_t[size];
    if (a->memory == nullptr) { //не вистачило памяті
        delete a;
        return nullptr;
    }
    a->size = size;
    a->offset = 0;
    return a;
}


void *arena_alloc(arenka *a, uint64_t size) {
    if (a == nullptr || size == 0) {
        return nullptr;
    }
    if (a->offset + size > a->size) {
        return nullptr;
    }
    void* result = a->memory + a->offset;
    a->offset += size;
    return result;
}

void arena_free(arenka * a) {
    //неможна видалити то, чого нема
    if (a == nullptr) {
        return;
    }
    delete[] a->memory;
    delete a;
}
