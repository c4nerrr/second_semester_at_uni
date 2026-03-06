//
// Created by c4ner on 3/5/2026.
//
#pragma once //від двойного включення
#include <cstdint>

#ifndef UNTITLED1_IMAGE_H
#define UNTITLED1_IMAGE_H

union Pixel {
    uint32_t rgba; //доступ до всього каналу (4 байта)
    struct {
        uint8_t r, g, b, a; //а-прозорість, б - синій, дж - зелений, р - червоний
    }chan;
};

void create_color (Pixel** pixels, uint32_t shirina, uint32_t visota);
void save_tga(const char* filename, uint32_t shirina, uint32_t visota, Pixel** pixels);

#endif //UNTITLED1_IMAGE_H