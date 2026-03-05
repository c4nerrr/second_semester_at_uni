
#include <cstdint>
#include <fstream>
#include <iostream>
#include <new> //для std::nothrow щоб не було bad_alloc щоб не крашити прогу

using namespace std;
//------------------------------------------------------------------------------------------------------

struct arenka {
    uint8_t* memory; //показник на пам'ять
    uint64_t size;
    uint64_t offset; //показує скільки байт від початку роздано
};


//------------------------------------------------------------------------------------------------
arenka * arena_new(uint64_t size) {
    if (size == 0) {
        return nullptr; //арена нуль без сенсу
    }
    auto a = new(std::nothrow) arenka; //ниє про аренка тому авто
    if (a == nullptr) {
        return nullptr;
    }
    a->memory = new uint8_t[size];
    a->size = size;
    a->offset = 0;
    return a;
}

void* arena_alloc(arenka* a, uint64_t size) {
    if (a->offset + size > a->size) { //сайз -кусок який просять виділити. а-сайз - розмір всієї арени
        return nullptr;
    }
    void* result = a->memory + a->offset; //якшо місце є, запам'ятовуємо адрес з якого починається непотрібна пам'ять
    a->offset += size;
    return result; //віддаєм пам'ять
}

void arena_free(arenka* a) {
    delete[] a->memory;
    delete a;
}


//----------------------------------------------------------------------------------------------------
union Pixel {
    uint32_t rgba; //доступ до всього каналу (4 байта)
    struct {
        uint8_t r, g, b, a; //а-прозорість, б - синій, дж - зелений, р - червоний
    }chan;
};

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


    ofstream fout(filename,ios_base::binary);
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
//------------------------------------------------------------------------------------------
int main(int argc, char const *argv[]) {
    arenka* my_arenna = arena_new(3000000);
    uint32_t shirina = 700;
    uint32_t visota = 900;
    auto pix = (Pixel**)arena_alloc(my_arenna, shirina*sizeof(Pixel*)); //авто шоб авоід дублікейт нейм
    for (uint32_t i = 0; i < shirina; ++i) {
        pix[i] = (Pixel*)arena_alloc(my_arenna, visota*sizeof(Pixel));
        if (pix[i] == nullptr) {
            arena_free(my_arenna);
            cerr << "Memory allocation failed" << endl;
            exit(-1);
        }
    }

    create_color(pix, shirina, visota);
    save_tga("kartinka.tga", shirina, visota, pix);


   arena_free(my_arenna);
    return 0;
}
//------------------------------------------------------------------------------------------