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

void GDAF::floid_yorshell_alg() const {
    vector<vector<int>> matrix(id_, vector<int>(id_, INF));
    for (int i = 0; i < id_; i++) {
        matrix[i][i] = 0;
            for (auto &[v, weight] : neib_[i]) {
                matrix[i][v] = weight;
        }
    }
    for (int k = 0; k < id_; k++) {
        for (int i = 0; i < id_; i++) {
            for (int j = 0; j < id_; j++) {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
}


void GDAF::dop_13_v(const int dist, const int vershina) const {
    vector<int> SS1_dist(id_, INF);
    SS1_dist = deqistri_alg(vershina);
    for (int i = 0; i < id_; i++) {
        if (dist >= SS1_dist[i] && SS1_dist[i] != INF) {
            cout << i << " "  << endl;
        }
    }
}

int main() {
    int initial_size;
    cout << "Скільки вершин буде у графі зі старту? -> ";
    cin >> initial_size;

    GDAF GRaF(initial_size);
    char oui = '9';

    do {
        cout << "\n=== Menu ===" << endl;
        cout << "1. Вивести граф на екран (pri_graph)" << endl;
        cout << "2. Заповнити граф ребрами з клавіатури (vve_)" << endl;
        cout << "3. Завантажити граф з файлу (vvid_from_file)" << endl;
        cout << "4. Додати ребро вручну (ply_g)" << endl;
        cout << "5. Алгоритм Дейкстри" << endl;
        cout << "6. Алгоритм Беллмана-Форда" << endl;
        cout << "7. Алгоритм Флойда-Уоршелла" << endl;
        cout << "8. Індив. завдання (Варіант 13: вершини на відстані <= K)" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір -> ";

        cin >> oui;
        cin.ignore();

        switch (oui) {
            case '1':
                GRaF.pri_graph();
                break;

            case '2':
                GRaF.vve_();
                break;

            case '3':
                GRaF.vvid_from_file();
                cout << "Граф успішно завантажено з файлу!" << endl;
                break;

            case '4': {
                int u, v, weight;
                // Не забудь, що граф зважений! Тому додаємо вагу.
                cout << "Введіть дві вершини та вагу для з'єднання (через пробіл) -> ";
                cin >> u >> v >> weight;
                GRaF.ply_g(u, v, weight);
                cout << "Ребро додано!" << endl;
                break;
            }

            case '5': {
                int start;
                cout << "Стартова вершина для Дейкстри -> ";
                cin >> start;
                GRaF.deqistri_alg(start); //NOLINT
                break;
            }

            case '6': {
                int start;
                cout << "Стартова вершина для Беллмана-Форда -> ";
                cin >> start;
                GRaF.bell_ford_alg(start);
                break;
            }

            case '7':
                GRaF.floid_yorshell_alg();
                break;

            case '8': {
                int dist, start;
                cout << "Введіть ліміт відстані (K) -> ";
                cin >> dist;
                cout << "Введіть стартову вершину (S) -> ";
                cin >> start;
                GRaF.dop_13_v(dist, start);
                break;
            }

            case '0':
                break;

            default:
                cout << "Невідома команда, машина. Спробуй ще раз." << endl;
                break;
        }

    } while (oui != '0');

    return 0;
}