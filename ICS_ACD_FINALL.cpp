//
// Created by c4ner on 3/6/2026.
//
#include <iostream>
#include <limits>

//перед початком інформую:
//Формат строк у файлі: Назва Поставщік Ціна День Місяць Рік.
//----------------------------------------
#include <fstream>
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
    void push_front(const Toy &data);
    void push_back(const Toy &data);
    void push_seredina(int index, const Toy& data);
    //------------------------------------------
    void pop_front();
    void pop_back();
    void pop_seredina(int index);
    Toy& operator[](int index) const;

    void clear();
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
    clear();
}

void LinkedListt::push_front(const Toy &data) {
        head = new Node(data, head);
    Size++;
}

void LinkedListt::push_back(const Toy &data) {
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

void LinkedListt::push_seredina(int index, const Toy& data) {
    if (head == nullptr || index == 0){
        push_front(data);
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

void LinkedListt::pop_seredina(const int index) {
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

Toy& LinkedListt::operator[](const int index) const {
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

void LinkedListt::clear() {
    while (Size) {
        pop_front();
    }
}

void LinkedListt::print() const {
    Node *current = head;
    while (current != nullptr) {
        cout << "Назва: " << current->data.name << "| Постачальник: "<< current->data.postavjik
            << " | Ціна: " << current->data.price << " | Дата: " << current->data.date.tm_mday<< "." <<
                current->data.date.tm_mon << "." << current->data.date.tm_year << endl;

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
    if (current == nullptr || current->pNext == nullptr) {
        cerr << "Не вдалося нічого знайти! " << endl;
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
    LinkedListt list;
    LoadFromFile(list);

    Toy igryshki;

    cout << "Ваш список наведено нижче: " << endl;
    list.print();

    char coi = '1';
    do {
        cout << "-----MENU-----" << endl;
        cout << "1. Видалити елемент" << endl;
        cout << "2. Додати елемент" << endl;
        cout << "3. Надрукувати вміст списку" << endl;
        cout << "4. Пошук за постачальником та датою надходження" << endl;
        cout << "5. Сортування за датою надходження, потім за ціною" << endl;
        cout << "6. Вивести іграшки, що надійшли ПІСЛЯ конкретної дати." << endl;
        cout << "7. Видалити весь список" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "0. Вийти" << endl;

        cin >> coi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (coi) {
            case '0':
                return 0;
                //---------------------------------------------------------
                case '1': {
                    char case_1 = '9';
                    cout << endl;
                    cout << "----------------------------------------------------" << endl;
                    cout << "Оберіть як видалити елемент: " << endl;
                    cout << "1. Видалити елемент починаючи спочатку" << endl;
                    cout << "2. Видалити елемент починаючи з кінця" << endl;
                    cout << "3. Видалити певний обраний елемент" << endl;
                    cout << "----------------------------------------------------" << endl;
                    cout << "0. Повернутися в меню" << endl;

                    cin >> case_1;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    switch (case_1) {
                        case '0': //NOLINT
                            break;
                            case '1':
                            list.pop_front();
                            cout << "----------------------------------------------------" << endl;
                            cout << "Успішно очищений перший елемент!" << endl;
                            cout << "----------------------------------------------------" << endl;
                            break;
                            case '2':
                            list.pop_back();
                            cout << "----------------------------------------------------" << endl;
                            cout << "Успішно очищений перший елемент!" << endl;
                            cout << "----------------------------------------------------" << endl;
                            break;
                            case '3': {
                                unsigned short index = 0;
                                cout << "----------------------------------------------------" << endl;
                                cout << "Елемент під яким номером хочете видалити? " << endl;
                                cin >> index;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                index--;
                                list.pop_seredina(index);
                                cout << "Успішно очищений перший елемент!" << endl;
                                cout << "----------------------------------------------------" << endl;
                            }
                            break;
                            default:
                            exit(-1);
                            break;
                    }
                }
                break;
                //-------------------------------------------------------------------
                case '2': {
                    char case_2 = '9';
                    cout << endl;
                    cout << "----------------------------------------------------" << endl;
                    cout << "Оберіть як додати елемент: " << endl;
                    cout << "1. Додати елемент спочатку" << endl;
                    cout << "2. Додати елемент з кінця" << endl;
                    cout << "3. Додати певний елемент" << endl;
                    cout << "----------------------------------------------------" << endl;
                    cout << "0. Повернутися в меню" << endl;

                    cin >> case_2;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Введіть назву іграшки (БЕЗ ПРОБІЛІВ!): " << endl;
                    cin >> igryshki.name;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Введіть постачальника(БЕЗ ПРОБІЛІВ): " << endl;
                    cin >> igryshki.postavjik;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Введіть ціну(напр: 799.99/409.50): " << endl;
                    cin >> igryshki.price;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Введіть рік коли була випущена іграшка(ТІЛЬКИ ЦИФРА): " << endl;
                    cin >> igryshki.date.tm_year;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (igryshki.date.tm_year > 2026) {
                        cerr << "Ти адекватний? 2026 на дворі. Який " << igryshki.date.tm_year << " ???"<<endl;
                        break;
                    }

                    cout << "Введіть місяць(ТІЛЬКИ ЦИФРА(напр: 09)): " << endl;
                    cin >> igryshki.date.tm_mon;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (igryshki.date.tm_mon > 12) {
                        cerr << "Ти бляха муха реал тупий чи просто недоразвітий? Ти вважаєш що в 1 році " << igryshki.date.tm_mon << " місяців?????" << endl;
                        break;
                    }

                    cout << "Введіть день(ТІЛЬКИ ЦИФРА(напр: 09))" << endl;
                    cin >> igryshki.date.tm_mday;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (igryshki.date.tm_mday > 31) {
                        cerr << "Будь ласка перестань знущатись надімною. Я викидую тебе в меню, це останнє попередження." << endl;
                        break;
                    }
                    switch (case_2) {
                        case '0': //NOLINT
                            break;
                            case '1':
                            list.push_front(igryshki);
                            cout << "Успішно додано!" << endl;
                            cout << "----------------------------------------------------" << endl;
                            break;
                            case '2':
                            list.push_back(igryshki);
                            cout << "Успішно додано!" << endl;
                            cout << "----------------------------------------------------" << endl;
                            break;
                            case '3': {
                                unsigned short index = 0;
                                cout << "Під яким номером хочете додати дані? " << endl;
                                cin >> index;
                                index--;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                list.push_seredina(index, igryshki);
                                cout << "Успішно додано!" << endl;
                                cout << "----------------------------------------------------" << endl;
                            }
                            break;

                            default:
                            exit(-1);
                            break;
                    }
                }
                break;
                //------------------------------------------------------------------

                case '3':
                cout << "----------------------------------------------------" << endl;
                list.print();
                cout << "----------------------------------------------------" << endl;
                break;
                //------------------------------------------------------------------

                case '4':
                cout << "Введіть поставщика: " << endl;
                cin >> igryshki.postavjik;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Введіть рік коли була випущена іграшка(ТІЛЬКИ ЦИФРА): " << endl;
                cin >> igryshki.date.tm_year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (igryshki.date.tm_year > 2026) {
                    cerr << "Ти адекватний? 2026 на дворі. Який " << igryshki.date.tm_year << " ???"<<endl;
                    break;
                }

                cout << "Введіть місяць(ТІЛЬКИ ЦИФРА(напр: 09)): " << endl;
                cin >> igryshki.date.tm_mon;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (igryshki.date.tm_mon > 12) {
                    cerr << "Ти бляха муха реал тупий чи просто недоразвітий? Ти вважаєш що в 1 році " << igryshki.date.tm_mon << " місяців?????" << endl;
                    break;
                }

                cout << "Введіть день(ТІЛЬКИ ЦИФРА(напр: 09))" << endl;
                cin >> igryshki.date.tm_mday;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (igryshki.date.tm_mday > 31) {
                    cerr << "Будь ласка перестань знущатись надімною. Я викидую тебе в меню, це останнє попередження." << endl;
                    break;
                }
                list.search(igryshki.postavjik, igryshki.date.tm_mday, igryshki.date.tm_mon, igryshki.date.tm_year);
                cout << "----------------------------------------------------" << endl;
                break;

                //--------------------------------------------------------------------------

                case '5':
                cout << "----------------------------------------------------" << endl;
                list.sort();
                cout << "Успішно відсортовано!" << endl;
                cout << "----------------------------------------------------" << endl;
                break;


                case '6':
                cout << "----------------------------------------------------" << endl;
                cout << "Введіть рік по якому треба знайти(ТІЛЬКИ ЦИФРА): " << endl;
                cin >> igryshki.date.tm_year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (igryshki.date.tm_year > 2026) {
                    cerr << "Ти адекватний? 2026 на дворі. Який " << igryshki.date.tm_year << " ???"<<endl;
                    break;
                }

                cout << "Введіть місяць(ТІЛЬКИ ЦИФРА(напр: 09)): " << endl;
                cin >> igryshki.date.tm_mon;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (igryshki.date.tm_mon > 12) {
                    cerr << "Ти бляха муха реал тупий чи просто недоразвітий? Ти вважаєш що в 1 році " << igryshki.date.tm_mon << " місяців?????" << endl;
                    break;
                }

                cout << "Введіть день(ТІЛЬКИ ЦИФРА(напр: 09))" << endl;
                cin >> igryshki.date.tm_mday;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (igryshki.date.tm_mday > 31) {
                    cerr << "Будь ласка перестань знущатись надімною. Я викидую тебе в меню, це останнє попередження." << endl;
                    break;
                }

                list.filter(igryshki.date.tm_mday, igryshki.date.tm_mon, igryshki.date.tm_year);
                cout << "----------------------------------------------------" << endl;
                break;

                case '7':
                cout << "----------------------------------------------------" << endl;
                list.clear();
                cout << "Успішно очищено!" << endl;
                cout << "----------------------------------------------------" << endl;
                break;


                default:
                exit(-1);
                break;
        }

    } while(coi != '0');
    return 0;
}