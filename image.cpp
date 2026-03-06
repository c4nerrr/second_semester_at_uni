//
// Created by c4ner on 3/5/2026.
//
#include "image.h"
#include <fstream>
using namespace std;

void create_color (Pixel** pixels, uint32_t shirina, uint32_t visota) {
    if (pixels == nullptr) {
        return;
    }
    for (uint32_t i = 0; i < shirina; i++) {
        for (uint32_t j = 0; j < visota; j++) {
            pixels[i][j].chan.r = i+j;
            pixels[i][j].chan.g = j+i;
            pixels[i][j].chan.b = i+j;
            pixels[i][j].chan.a = 255; //шоб ця дрянь не була прозорою
        }
    }
};

void save_tga(const char* filename, uint32_t shirina, uint32_t visota, Pixel** pixels) {
    if (pixels == nullptr || filename == nullptr) {
        return;
    }
    if (shirina == 0 || visota == 0) {
        return;
    }
    uint8_t header[18] = {0}; //у будь якого формата є заголовок. ми його задаєм. тга коштує рівно 18 байт.
    header[2] = 2; //означає шо картінка рджб без зжатія
    header[16] = 32; //глубіна кольору
    header[17] = 8; //альфа-канал(8 біт)

    header[12] = shirina & 0xff; //молодший байтік шіріні
    header[13] = (shirina >> 8) & 0xff; //старший байтік шіріні
    header[14] = visota & 0xff; //вісота молод.
    header[15] = (visota >> 8) & 0xff; //вісота стар.


    ofstream fout(filename, ios_base::binary);
    if (fout.is_open() == false) {
        return;
    }
    fout.write((char*)header, 18);
    for (uint32_t i = 0; i < visota; i++) {
        for (uint32_t j = 0; j < shirina; j++) {
            fout.write((char*)&pixels[j][i].rgba, sizeof(uint32_t)); //і це шіріна, йотий це вісота
        }
    }
    fout.close();
}