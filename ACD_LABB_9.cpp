//
// Created by c4ner on 4/5/2026.
//

#include "ACD_LABB_9.h"

#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;


hash_tabl::hash_tabl(const int size) {
  table_size = size; //бєру ціфру которую ввів користувач і сейвю в память класу на майб
    table.resize(size);
}

hash_tabl::~hash_tabl() {
    hash_clear();
    table.clear();
}

void hash_tabl::hash_map_insert(const std::string &code, const std::string &name, float price) {

}

bool hash_tabl::hash_map_has_key(const std::string &code) {
}

void hash_tabl::has_map_at(const std::string &code) {
}

void hash_tabl::hash_clear() {
    for (int i = 0; i < table.size(); i++) {
        table[i].clear();
    }
}

int hash_tabl::hash_code(const std::string &key) const {
 long long base = 0;
    for (const char c : key) {
        base += c; //строка в число
    }
    long long sqrt = base * base; //возводимо до квадрата
    sqrt /= 10; //прибираємо 1 цифру справа
    const int mid = sqrt % 1000; //забиражмо 3 цифри, це буде середина
    return mid % table_size;
}


int main() {

}
