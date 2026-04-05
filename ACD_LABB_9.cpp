//
// Created by c4ner on 4/5/2026.
//

#include "ACD_LABB_9.h"

#include <cassert>
#include <iostream>
#include <chrono>
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
  const auto index = hash_code(code);
    table[index].push_back({code, name, price});
}

bool hash_tabl::hash_map_has_key(const std::string &code) const {
    const auto index = hash_code(code);
    for (const auto &item: table[index]) { //звіряєм код орігінала з тим який передали
        if (item.code == code) {
            return true;
        }
    }
    return false;
}

void hash_tabl::has_map_at(const std::string &codik) const {
    const auto index = hash_code(codik);
    for (const auto &[code, name, price]: table[index]) {
        if (codik == code) {
            cout << "Товар: " << name << "  Ціна: " << price << endl;
        }
    }
}

void hash_tabl::hash_clear() {
    for (auto & i : table) {
        i.clear();
    }
}

int hash_tabl::hash_code(const std::string &key) const {
 long long base = 0;
    for (const char c : key) {
        base += c; //строка в число
    }
    long long sqrt = base * base; //возводимо до квадрата
    sqrt /= 10; //прибираємо 1 цифру справа
    const int mid = static_cast<int>(sqrt)  % 1000; //забиражмо 3 цифри, це буде середина
    return mid % table_size;
}


int main() {
    int cifra = 0;
    cout << "Введіть стартовий розмір хеш-таблиці" << endl;
    cin >> cifra;
    hash_tabl my_table(cifra);
    bool flag = false;
    char gui = '8';
    do {
        cout << "---MENU---" << endl;
        cout << "1) Gener data file (20,1000,5000);" << endl;
        cout << "2) Load data in table " << endl;
        cout << "3) Find code && name && data" << endl;
        cout << "------" << endl;
        cout << "0) Exit" << endl;

        cin >> gui;
        cin.ignore();

        switch (gui) {
            case '1': {
                unsigned short schotchik = 0;
                cout << "How many want to gener? (20,1000,5000)" << endl;
                cin >> schotchik;
                cin.ignore();
                 if (schotchik == 20 || schotchik == 1000 || schotchik == 5000) {
                     cin.clear();
                     ofstream fout("data.txt");
                     if (!fout.is_open()) {
                         cerr << "Error. Can't open file " << endl;
                         return 1;
                     }

                     for (int i = 0; i < schotchik; i++) {
                         const string opt[] = {"FgT", "AAA", "hYlKK"};
                         constexpr int n = size(opt);
                         const int randCODE = rand() % n;
                         string fake_code = opt[randCODE] + to_string(i);
                         string fake_name = "Item_" + to_string(i);
                         double fake_price = (rand() % 1000) + 10.9;

                         fout << fake_code << " " << fake_name << " " << fake_price << endl;
                     }
                     fout.close();
                     cout << "Congratulations! Your file is done." << endl;
                     flag = true;
                 }
                else { //NOLINT
                    cerr << "Invalid input! ONLY 20,1000 OR 5000! TRY AGAIN!" << endl;
                 }
            }
                break;
                //-------------------------------------------------------------
                case '2':
                if (flag == true) {
                   ifstream fin("data.txt");
                    if (fin.is_open()) {
                        string Code, Name;
                        float Price;
                        while (fin >> Code >> Name >> Price) {
                            my_table.hash_map_insert(Code, Name, Price); //запіхуєм в хешку
                        }
                        fin.close();
                        cout << "Congratulations! Step is done." << endl;
                    }
                    else {
                        cerr << "Error. Can't open file " << endl;
                        return 1;
                    }
                }
                else {
                    cerr << "Invalid input! Your first step is Gener data file." << endl;
                    break;
                }
                break;
             //----------------------------------------------------------------
                case '3': {
                    if (flag == true) {
                        string tovar_code;
                        cout << "Enter code tovara: " << endl;
                        cin >> tovar_code;
                        auto start = chrono::steady_clock::now();
                        my_table.has_map_at(tovar_code);
                        auto end = chrono::steady_clock::now();
                        auto dif = chrono::duration_cast<chrono::microseconds>(end - start);
                        cout << "Total time: " << dif.count() << endl;
                    }
                    else {
                        cerr << "Invalid input! Your first step is Gener data file." << endl;
                        break;
                    }
                }
                break;
                //------------------------------------------------------------
                case '0':
                break;
                //------------------------------------------------------------

                default:
                cerr << "Invalid input!" << endl;
                break;
                //-----------------------------------------------------------
        }
    }while (gui != '0');
}