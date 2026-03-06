//
// Created by c4ner on 3/6/2026.
//
#include <iostream>
#include <ctime>

//перед початком інформую:
//Формат строк у файлі: Назва Поставщік Ціна День Місяць Рік.
//----------------------------------------
#include <fstream>
using namespace std;
//-----------------------------------------
    struct Toy{
        string name;
        string postavjik;
        double price;
        tm date;

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
    //-----------------------------------------
    void print();
    void search(Toy data);
    void filter(Toy data);
    void sort();

    private:
    class Node {
    public:
        Node *pNext;
        Toy data;
        Node(Toy data = Toy(), Node *pNext = nullptr) {
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
}

void LinkedListt::push_back(Toy data) {
}

void LinkedListt::push_seredina(int index, Toy data) {
}

void LinkedListt::pop_front() {
}

void LinkedListt::pop_back() {
}

void LinkedListt::pop_seredina(int index) {
}

void LinkedListt::print() {
}

void LinkedListt::search(Toy data) {
}

void LinkedListt::filter(Toy data) {
}

void LinkedListt::sort() {
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
    file.close();
}

//-----------------------------------------------------------------------------

int main() {

    CreateTestFile();
}
