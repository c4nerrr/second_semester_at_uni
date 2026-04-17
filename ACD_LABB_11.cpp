//
// Created by c4ner on 4/15/2026.
//

#include "ACD_LABB_11.h"

#include <iostream>
using namespace std;



GDAF::GDAF(const int size) : id_(size) {
    neib_.resize(size);
}

GDAF::~GDAF() {
    neib_.clear();
}

void GDAF::ply_g(int u, int v, int weight) {
    if (u >= id_ || v >= id_ || u < 0 || v < 0) {
        cerr << "Помилка: Вершини " << u << " або " << v << " не існує в графі!" << endl;
        return;
    }
    neib_[u].emplace_back(v, weight);
    neib_[v].emplace_back(u, weight);
}

void GDAF::del(int u, int v) {
    erase_if(neib_[u], [v](const std::pair<int, int>& p) {
        return p.first == v; //{номер сусіда, вага}
        //return true;
    } );
    erase_if(neib_[v], [u](const std::pair<int, int>& p) {
        return p.first == u;
    });
}

void GDAF::pri_graph() const {
    for (int i = 0; i < id_; i++) {
        cout << " ----- " << endl;
        cout << "Вершина: [" << i << "] " << endl;
        cout << " ----- " << endl;
        for (auto [fst, snd] : neib_[i]) {
            cout << "Номер: {" << fst << " }, Вага: { " << snd << "}" << endl;
        }
        cout << endl;
    }
}

void GDAF::vve_() {
}

void GDAF::vvid_from_file() {
}

void GDAF::deqistri_alg(int start_vertex) const {
}

void GDAF::bell_ford_alg(int start_vertex) const {
}

void GDAF::floid_yorshell_alg() const {
}


void GDAF::dop_13_v(int dist, int vershina) {
}


int main() {

    return 0;
}