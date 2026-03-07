//
// Created by c4ner on 3/6/2026.
//
#include <iostream>
#include <ctime>

//перед початком інформую:
//Формат строк у файлі: Назва Поставщік Ціна День Місяць Рік.
//----------------------------------------
#include <fstream>
#include <utility>
using namespace std;
//-----------------------------------------
    struct Toy{
        string name;
        string postavjik;
        double price{};
        tm date{};

    };

//-----------------------------------------
class LinkedListt {
    public:
    //--------------------------------------------
   LinkedListt();
    ~LinkedListt();
    //--------------------------------------------
    void push_front(Toy data);
    void push_back(Toy data);
    void push_seredina(int index, Toy data);
    //------------------------------------------
    void pop_front();
    void pop_back();
    void pop_seredina(int index);
    Toy& operator[](const int index);
    //-----------------------------------------

    [[nodiscard]] int GetSize() const {
        return Size;
    }

    void print() const;
    void search(const string &TargetPostavjik,int targetDay, int TargetMonth, int TargetYear) const;
    void filter(int targetDay, int targetMonth, int targetYear) const;
    void sort();

    private:
    class Node {
    public:
        Node *pNext;
        Toy data;

        explicit Node(const Toy &data = Toy(), Node *pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };
    int Size = 0;
    Node *head;
};

LinkedListt::LinkedListt() {
    head = nullptr;
    Size = 0;
}

LinkedListt::~LinkedListt() {
}

void LinkedListt::push_front(Toy data) {
        head = new Node(data, head);
    Size++;
}

void LinkedListt::push_back(Toy data) {
    if (head == nullptr) {
        head = new Node(data);
    }
    else {
        Node *current = this->head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        current->pNext = new Node(data);
    }
    Size++;
}

void LinkedListt::push_seredina(int index, Toy data) {
    if (head == nullptr || index == 0){
        push_front(std::move(data));
        return;
    }
        Node *current = head;
            for (int i = 0; i < index-1; i++) {
                current = current->pNext;
            }
        current->pNext = new Node(data, current->pNext);
    Size++;
}

void LinkedListt::pop_front() {
    Node *current = head;
    head = head->pNext;
    delete current;
    Size--;
}

void LinkedListt::pop_back() {
    if (head == nullptr) {
        return;
    }
    if (head->pNext == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node *current = this->head;
        while (current->pNext->pNext != nullptr) {
            current = current->pNext;
        }
        delete current->pNext;
        current->pNext = nullptr;
    }
    Size--;
}

void LinkedListt::pop_seredina(int index) {
    if (head == nullptr) {
        return;
    }
    if (index == 0) {
        pop_front();
        return;
    }
    Node *current = head;
    for (int i = 0; i < index-1; i++) {
        if (current->pNext == nullptr) {
            throw out_of_range("Там немає стільки елементів!!!");
        }
        current = current->pNext;
    }
    if (current == nullptr || current->pNext == nullptr) {
        throw out_of_range("Це шо ти тут таке наклацав странне. Спробуй ще раз і не виходь за межі!");
    }
    Node *toDelete = current->pNext;
    current->pNext = toDelete->pNext;
    delete toDelete;
    Size--;
}

Toy& LinkedListt::operator[](const int index) {
    int count = 0;
    Node *current = this->head;
    while (current != nullptr) {
        if (count == index) {
            return current->data;
        }
        current = current->pNext;
        count++;
    }
     throw out_of_range("Індекс більше за розмір списку!!!");
}
void LinkedListt::print() const {
    Node *current = head;
    while (current != nullptr) {
        cout << "Назва: " << current->data.name << "| Постачальник: "<< current->data.postavjik
            << " | Ціна: " << current->data.price << " | Дата: " << current->data.date.tm_mday<< "." <<
                current->data.date.tm_mon + 1 << "." << current->data.date.tm_year + 1900 << endl;

        current = current->pNext;
    }
}
void LinkedListt::search(const string &TargetPostavjik, int targetDay, int TargetMonth, int TargetYear) const {
    Node *current = head;
    while (current != nullptr) {
        if (current->data.postavjik == TargetPostavjik &&
            current->data.date.tm_mday == targetDay &&
            current->data.date.tm_mon+1 == TargetMonth &&
            current->data.date.tm_year+1900 == TargetYear) {
            cout << current->data.name << endl;
        }
        current = current->pNext;
    }
}


void LinkedListt::filter(int targetDay, int targetMonth, int targetYear) const {
    Node *current = head;
    while (current != nullptr) {
        if (current->data.date.tm_year+1900 > targetYear) {
            cout << current->data.name << endl;
        }
        if (current->data.date.tm_year+1900 == targetYear) {
            if (current->data.date.tm_mon+1 > targetMonth) {
                cout << current->data.name << endl;
            }
            if (current->data.date.tm_mon+1 == targetMonth) {
                if (current->data.date.tm_mday > targetDay) {
                    cout << current->data.name << endl;
                }
            }
        }
        current = current->pNext;
    }
}

void LinkedListt::sort() { //бульбашка
    if (head == nullptr || head->pNext == nullptr) {
        return;
    }
    bool swapped; //щоб знать коли остановитись
    do {
        swapped = false;
        Node *previous = nullptr;
        Node *current = head;
        Node *nextNode = head->pNext;

        while (nextNode != nullptr) {
            bool needSwap = false; //за замовчуванням нічо не надо свапити
            //порівнюємо дати і ціни
            if (current->data.date.tm_year+1900 > nextNode->data.date.tm_year+1900) {
               needSwap = true;
            }
            else if (current->data.date.tm_year+1900 == nextNode->data.date.tm_year+1900) {
                if (current->data.date.tm_mon+1 > nextNode->data.date.tm_mon+1) {
                    needSwap = true;
                }
                else if (current->data.date.tm_mon+1 == nextNode->data.date.tm_mon+1) {
                    if (current->data.date.tm_mday > nextNode->data.date.tm_mday) {
                        needSwap = true;
                    }
                    else if (current->data.date.tm_mday == nextNode->data.date.tm_mday) {
                        if (current->data.price > nextNode->data.price) {
                            needSwap = true;
                        }
                    }
                }
            }

            if (needSwap) {
                current->pNext = nextNode->pNext;
                nextNode->pNext = current;
                if (previous == nullptr) {
                    head = nextNode; //якщо змінювали голову
                }
                else {
                    previous->pNext = nextNode; //якщо змінювали середину
                }
                //після усіх змін, некстНод почав стояти перед карент
                //обновляєм прев і некстНОд
                previous = nextNode;
                nextNode = current->pNext;
                swapped = true;
            }else {
                //якщо не змунювали, дружно двигаємо вперед
                previous = current;
                current = nextNode;
                nextNode = nextNode->pNext;
            }
        }
    }while (swapped);
}



//----------------------------------------------------------------------------
void LoadFromFile(LinkedListt &list) {
    ifstream file("Test.txt");
    string n, p;
    double price;
    int data, month, year;
    while (file >> n >> p >> price >> data >> month >> year) {
        Toy temp;

        temp.name = n;
        temp.postavjik = p;
        temp.price = price;

        temp.date.tm_mday = data;
        temp.date.tm_mon = month-1;
        temp.date.tm_year = year-1900;
        temp.date.tm_hour = 0;
        temp.date.tm_min = 0;
        temp.date.tm_sec = 0;

        list.push_back(temp);
    }
    file.close();
}
void CreateTestFile() {
    ofstream file("Test.txt");
    file << "Barbie Mattel 599.99 15 05 2023" << endl;
    file << "LegoNinjago LEGO 1799.99 04 01 2025" << endl;
    file << "LOL MGA_Enterteiment 345.00 28 02 2005" << endl;
    file << "Pop_Top Letsvan 1195.00 06 03 2026" << endl;
    file << "LegoNinjago LEGO 899.99 01 12 2017" << endl;
    file << "HotWheels Mattel 150.50 10 09 2020" << endl;
    file << "Monopoly Hasbro 850.00 01 12 2023" << endl;
    file << "RubiksCube Rubiks 299.99 15 05 2023" << endl;
    file << "Jenga Hasbro 450.00 20 08 2021" << endl;
    file << "TeddyBear PlayTive 600.00 14 02 2019" << endl;
    file.close();
}
//-----------------------------------------------------------------------------


int main() {

    CreateTestFile();
    LinkedListt list;
    LoadFromFile(list);
    list.print();
}
