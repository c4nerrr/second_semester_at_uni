//
// Created by c4ner on 4/11/2026.
//

#include "ACD_LABB_10.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;


Graf_Realise::Graf_Realise(const int x) : id_(x) {
    neighbours_.resize(x);
}

Graf_Realise::~Graf_Realise() {
    while (!neighbours_.empty()) {
        neighbours_.clear();
    }
}

void Graf_Realise::BFS(const int startVertex) const {
    vector<bool> visited(id_, false); //де ми вже були а де ні
    vector<int> wave(id_, -1); //ПОЧ -1???

    queue<int> queue;

    queue.push(startVertex);
    visited[startVertex] = true; wave[startVertex] = 0;
    while (!queue.empty()) {
        const int temp = queue.front(); queue.pop();
        cout << "Вершина: " << temp << "|  Хвиля: " << wave[temp] << endl;

        for (int neighbor : neighbours_[temp]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true; wave[neighbor] = wave[temp] + 1;
                queue.push(neighbor);
            }
        }
    }
}

void Graf_Realise::DFS(const int startVertex) const {
    vector<bool> visited(id_, false); //де ми вже були а де ні
    stack<int> staKK;
    staKK.push(startVertex);
    visited[startVertex] = true;
    while (!staKK.empty()) {
        const int temp = staKK.top(); staKK.pop();
        cout << "Вершина (пошук вглибину) : " << temp << endl;

        for (int neighbor : neighbours_[temp]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                staKK.push(neighbor);
            }
        }
    }
}

void Graf_Realise::ply_(const int n, const int m) {
    //неорінтований граф, тому мост працює в обидві сторони
    neighbours_[n].push_back(m);
    neighbours_[m].push_back(n);
}

void Graf_Realise::del_(const int n, const int m) {
    std::erase(neighbours_[n], m);
    std::erase(neighbours_[m], n);
}

void Graf_Realise::ply_vertices_() {
    id_++;
    neighbours_.emplace_back();
}

void Graf_Realise::del_vertices_(int n) {
    for (int i = 0; i < id_; i++) {
        std::erase(neighbours_[i], n);
    }
    neighbours_.erase(neighbours_.begin() + n);
    for (auto & neighbour : neighbours_) {
        for (int &val : neighbour) {
            if (val > n) {
                val--;
            }
        }
    }
    id_--;
}

void Graf_Realise::print_graph() const {
    for (int i = 0; i < id_; i++) {
        cout << " ----- " << endl;
        cout << "Вершина: [" << i << "] " << endl;
        cout << " ----- " << endl;
        for (const int neighbor : neighbours_[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

void Graf_Realise::indiv_() const {
    vector<bool> visited(id_, false);
    int counter = 0;

    for (int i = 0; i < id_; i++) {
        if (!visited[i]) {
            counter++;
            cout << "Компонента: " << counter << endl;

            DFS_helper(i, visited);
            cout << endl;
        }
    }
    cout << "Всього компонент зв'язності: " << counter << endl;
}

void Graf_Realise::vved_() {
    int edges = 0;
    cout << " ----- " << endl;
    cout << " Скільки ребер (мостів) хочете додати ->";
    cin >> edges;
    cin.ignore();
    short u; short v;
    for (int i = 0; i < edges; i++) {
        cout << " ----- " << endl;
        cout << "Введіть 1-шу вершину в ребрі "<< i <<" яку треба з'єднати-> ";
        cin >> u;
        cin.ignore();
        cout << "Введіть 2-гу вершину в ребрі "<< i <<" яку треба з'єднати-> ";
        cin >> v;
        cin.ignore();
        ply_(u, v);
    }
    cout << " ----- " << endl;
    cout << "Готово!" << endl;
}

void Graf_Realise::DFS_helper(const int vertex, std::vector<bool> &visited) const {
    stack<int> staKK;
    staKK.push(vertex);
    visited[vertex] = true;

    while (!staKK.empty()) {
        const int temp = staKK.top(); staKK.pop();
        cout << temp << endl;

        for (int neighbor : neighbours_[temp]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                staKK.push(neighbor);
            }
        }
    }
}


int main() {
    char oui = '9';
    do {
        cout << "Menu:" << endl;
        cout << " ----- " << endl;
        cout << "1. BFS" << endl;
        cout << "2. DFS" << endl;
        cout << "3. ply" << endl;
        cout << "4. del_" << endl;
        cout << "5. ply_vertices" << endl;
        cout << " ----- " << endl;
        cout << "0. exit" << endl;

        cin >> oui;
        cin.ignore();
        switch (oui) {
            case '1':
                break;
                case '2':
                break;
                case '3':
                break;
                case '4':
                break;
                case '5':
                break;
                case '0':
                break;
        }

    }while (oui != '0');
    return 0;
}
