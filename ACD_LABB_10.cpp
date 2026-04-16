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
    if (n >= id_ || m >= id_ || n < 0 || m < 0) {
        cout << "Помилка: Вершини " << n << " або " << m << " не існує в графі!" << endl;
        return;
    }

    neighbours_[n].push_back(m);
    neighbours_[m].push_back(n);
}

void Graf_Realise::del_(const int n, const int m) {
    if (n >= id_ || m >= id_ || n < 0 || m < 0) {
        cout << "Помилка: Вершини " << n << " або " << m << " не існує в графі!" << endl;
        return;
    }
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

void Graf_Realise::BFS_ignore(const int startVertex, const int ignoreVertex) const {
    if (startVertex == ignoreVertex) {
        cout << "Помилка: не можна стартувати з вершини, яку ми ігноруємо!" << endl;
        return;
    }

    vector<bool> visited(id_, false);
    vector<int> wave(id_, -1);

    if (ignoreVertex >= 0 && ignoreVertex < id_) {
        visited[ignoreVertex] = true;
    }

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

void Graf_Realise::DFS_ignore(const int startVertex, const int ignoreVertex) const {
    if (startVertex == ignoreVertex) {
        cout << "Помилка: не можна стартувати з вершини, яку ми ігноруємо!" << endl;
        return;
    }

    vector<bool> visited(id_, false);

    if (ignoreVertex >= 0 && ignoreVertex < id_) {
        visited[ignoreVertex] = true;
    }

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
    int initial_size;
    cout << "Скільки вершин буде у графі зі старту? -> ";
    cin >> initial_size;

    // Створюємо об'єкт правильно, передаючи початковий розмір!
    Graf_Realise GRaF(initial_size);
    char oui = '9';

    do {
        cout << "\n=== Menu ===" << endl;
        cout << "1. Вивести граф на екран (print_graph)" << endl;
        cout << "2. Заповнити граф ребрами (vved_)" << endl;
        cout << "3. Додати ребро (ply_)" << endl;
        cout << "4. Видалити ребро (del_)" << endl;
        cout << "5. Додати пусту вершину (ply_vertices)" << endl;
        cout << "6. Видалити вершину (del_vertices)" << endl;
        cout << "7. Обхід в ширину (BFS)" << endl;
        cout << "8. Обхід в глибину (DFS)" << endl;
        cout << "9. Знайти компоненти зв'язності (indiv_)" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір -> ";

        cin >> oui;
        cin.ignore();

        switch (oui) {
            case '1':
                GRaF.print_graph();
                break;

            case '2':
                GRaF.vved_();
                break;

            case '3': {
                int u, v;
                cout << "Введіть дві вершини для з'єднання (через пробіл) -> ";
                cin >> u >> v;
                GRaF.ply_(u, v);
                cout << "Ребро додано!" << endl;
                break;
            }

            case '4': {
                int u, v;
                cout << "Введіть дві вершини для роз'єднання (через пробіл) -> ";
                cin >> u >> v;
                GRaF.del_(u, v);
                cout << "Ребро видалено!" << endl;
                break;
            }

            case '5':
                GRaF.ply_vertices_();
                cout << "Нову порожню вершину додано в кінець!" << endl;
                break;


            case '6': {
                int v;
                cout << "Введіть вершину для ВИДАЛЕННЯ -> ";
                cin >> v;
                GRaF.del_vertices_(v);
                cout << "Вершину видалено, індекси зсунуто!" << endl;
                break;
            }

            case '7': {
                /*int start;
                cout << "Стартова вершина для BFS -> ";
                cin >> start;
                GRaF.BFS(start);
                break;*/
                int start;
                char choice;
                cout << "Стартова вершина для BFS -> ";
                cin >> start;
                cout << "Бажаєте проігнорувати якусь вершину? (y/n) -> ";
                cin >> choice;

                if (choice == 'y' || choice == 'Y') {
                    int ignore_v;
                    cout << "Введіть вершину для ІГНОРУ -> ";
                    cin >> ignore_v;
                    GRaF.BFS_ignore(start, ignore_v);
                } else {
                    GRaF.BFS(start);
                }
                break;
            }

            case '8': {
                /*int start;
                cout << "Стартова вершина для DFS -> ";
                cin >> start;
                GRaF.DFS(start);
                break;*/
                int start;
                char choice;
                cout << "Стартова вершина для DFS -> ";
                cin >> start;
                cout << "Бажаєте проігнорувати якусь вершину? (y/n) -> ";
                cin >> choice;

                if (choice == 'y' || choice == 'Y') {
                    int ignore_v;
                    cout << "Введіть вершину для ІГНОРУ -> ";
                    cin >> ignore_v;
                    GRaF.DFS_ignore(start, ignore_v);
                } else {
                    GRaF.DFS(start);
                }
                break;
            }

            case '9':
                GRaF.indiv_();
                break;

            case '0':

                break;



            default:
                cout << "Невідома команда. Спробуй ще раз." << endl;
                break;
        }

    } while (oui != '0');

    return 0;
}