//
// Created by c4ner on 4/15/2026.
//

#include "ACD_LABB_11.h"
#include <iostream>
#include <fstream>
#include <ranges>
using namespace std;

constexpr int INF = 1e9;



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
    int edges = 0;
    cout << " ----- " << endl;
    cout << " Скільки ребер (мостів) хочете додати ->";
    cin >> edges;
    cin.ignore();
    short u; short v; short w;
    for (int i = 0; i < edges; i++) {
        cout << " ----- " << endl;
            cout << "Введіть 1-шу вершину в ребрі "<< i <<" яку треба з'єднати-> ";
            cin >> u;
            cin.ignore();
            cout << "Введіть 2-гу вершину в ребрі "<< i <<" яку треба з'єднати-> ";
            cin >> v;
            cin.ignore();
            cout << "Введіть вагу вершин" << u << " " << v << " ->" << endl;
            cin >> w;
        cin.ignore();
        ply_g(u, v, w);
    }
    cout << " ----- " << endl;
    cout << "Готово!" << endl;
}

void GDAF::vvid_from_file() {
    ifstream file;
    file.open("graph.txt", ios::in);
        if (file.is_open()) { //ребра, вершини, вага. у в веігт
            int u, v, weight;
            while (file.good() && file >> u >> v >> weight) { //прийдется писать в один рядок НЕ стовбцями по 3 шт
                    cout << u << " " << v << " " << weight << endl;
                    ply_g(u, v, weight);
                }
         }
        else {
            cerr << "Не вдалося відкрити файл! " << endl;
            return;
        }
    file.close();
}

vector<int> GDAF::deqistri_alg(const int start_vertex) const {
    vector<int> dist(id_, INF);
    vector<bool> visited(id_);
    dist[start_vertex] = 0;

        for (int i = 0; i < id_; i++) {
            int nearest = -1;
                 for (int v = 0; v < id_; v++) {
                    if (!visited[v] && (nearest == -1 || dist[v] < dist[nearest])) {
                        nearest = v;
                    }
                 }
            if (dist[nearest] == INF) break;
            visited[nearest] = true;

            for (auto &[to, weight] : neib_[nearest]) {
                if (dist[to] > dist[nearest] + weight) {
                    dist[to] = dist[nearest] + weight;
                }
            }
        }
    cout << "--- Результати алгоритму Дейкстри від вершини " << start_vertex << " ---" << endl;
    for (int i1 = 0; i1 < id_; ++i1) {
        if (dist[i1] == INF) cout << i1 << " \t Недосяжна" << endl;
        else cout << i1 << " \t " << dist[i1] << endl;
    }
    return dist;
}

void GDAF::bell_ford_alg(int start_vertex) const {
    vector<int> lambdas(id_, INF);
    lambdas[start_vertex] = 0;

    for (int i = 0; i <= id_ - 1; i++) {
        for (int u = 0; u < id_; u++) { //перебираємо ребра графа
            if (lambdas[u] == INF) continue;
                for (auto &[v, weight] : neib_[u]) {
                    if (lambdas[u] + weight < lambdas[v]) {
                        lambdas[v] = lambdas[u] + weight;
                    }
                }

        }

        for (int u = 0; u < id_; u++) {
            if (lambdas[u] == INF) continue;
            for (auto &[v, weight] : neib_[u]) {
                if (lambdas[u] + weight < lambdas[v]) {
                    cout << "Знайдено негативний цикл у графі!" << endl;
                    return;
                }
            }
        }

    }
}

void GDAF::floid_yorshell_alg() const {
}


void GDAF::dop_13_v(int dist, int vershina) {
}


int main() {

    return 0;
}