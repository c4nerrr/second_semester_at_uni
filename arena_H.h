//
// Created by c4ner on 3/5/2026.
//
#pragma once
#include <cstdint>

#ifndef UNTITLED1_ARENA_H_H
#define UNTITLED1_ARENA_H_H


struct arenka {
    uint8_t* memory;
    uint64_t size;
    uint64_t offset;
};

arenka* arena_new(uint64_t size);
void* arena_alloc(arenka* a, uint64_t size);
void arena_free(arenka* a);

#endif //UNTITLED1_ARENA_H_H