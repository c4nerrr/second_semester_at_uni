//
// Created by c4ner on 3/20/2026.
//

#include "ACD_LAB_7.h"

#include <conio.h>
#include <iostream>
#include <limits>
using namespace std;

template<typename vetochka>
class Derevo {

    private:
    class BTNode {
        public:
        BTNode* l;
        BTNode* r;
        vetochka data;

        explicit BTNode(vetochka data = vetochka(), BTNode* l = nullptr, BTNode* r = nullptr) {
            this->data = std::move(data);
            this->l = l;
            this->r = r;
        };
    };
    int Size;
    BTNode* root;
    void dodavanie(BTNode* &pomogite, vetochka data); //зліва направо без урахування значенн
    void ydalenie(BTNode* &help, vetochka data);
    void clear_recursive(BTNode* &sos);
    void prosmotr_recursive(BTNode* &auxilium, int level);
public:
    Derevo();
    ~Derevo();

    void additem(vetochka data) { dodavanie(root, data); Size++; }
    void ydalitem(vetochka data) { ydalenie(root, data); Size--; }

    void clear() {clear_recursive(root); Size = 0;}

    void proverka();

    void prosmotrr() {
        if (root == nullptr) {
            proverka();
        }
        else {
            int level = 0;
            cout << "------------------" << endl;
            cout << "Елементи дерева: " << endl;
            prosmotr_recursive(root, level);
            cout << "------------------" << endl;
        }
    }

    void poisk(vetochka data);

    void dop_fynk();

    void znaitu_glibiny_vyzla(vetochka data);

    //void enqueue(const vetochka& data);


};


template<typename vetochka>
Derevo<vetochka>::Derevo() : Size(0), root(nullptr) {
}

template<typename vetochka>
Derevo<vetochka>::~Derevo() {
    while (Size) {
        clear();
    }
}

template<typename vetochka>
void Derevo<vetochka>::dodavanie(BTNode* &pomogite, vetochka data) {
    if (pomogite == nullptr) {
        pomogite = new BTNode(data);
    }
    else {
        if (data < pomogite->data) {
            //сиаут <<
            dodavanie(pomogite->l, data);
        }
        else {
            //сиаут >>
            dodavanie(pomogite->r, data);
        }
    }
}

template<typename vetochka>
void Derevo<vetochka>::clear_recursive(BTNode *&sos) {
    if (sos != nullptr) {
        clear_recursive(sos->l);
        clear_recursive(sos->r);
        delete sos;
        sos = nullptr;
    }
}

template<typename vetochka>
void Derevo<vetochka>::prosmotr_recursive(BTNode *&auxilium, int level) {
    if (auxilium == nullptr) {
        return;
    }
    prosmotr_recursive(auxilium->l, level+1);

    for (int i = 0; i < level; i++) {
        cout << "    ";
    }

    cout << auxilium->data << endl;

    prosmotr_recursive(auxilium->l, level+1);
}

template<typename vetochka>
void Derevo<vetochka>::ydalenie(BTNode* &help, vetochka data) {
    //пошук елемента
    if (help == nullptr) {
        proverka();
        return;
    }
    if (data < help->data) {
        ydalenie(help->l, data);
    }
    else if (data > help->data) {
        ydalenie(help->r, data);
    } //Знайшли:
    else {
        //один або нуль потомків
        //А: Нема лівого дітіни
        if (help->l == nullptr) {
            [[maybe_unused]] BTNode* temp = help->r; //запомнілі праву вітку
            delete help; //удаляєм
            help = temp; //прішиваєм ветку до родітеля
        }
        //нема правої дітітни:
        else if (help->r == nullptr) {
            [[maybe_unused]] BTNode* temp = help->l; //запомнілі лєву вєтку
            delete help;
            help = temp; //прішиваєм ветку
        }
        //як виразився мій репетитор з програмування: два потоки (самий піздєц)
        else {
            //шукаєм мінімального чєла ну там тіпа у правому поддєрєву (вліво до упору)
            BTNode* temp = help->r;
            while (temp->l != nullptr) {
                temp = temp->l;
            }
            //хаваєм данні:
            help->data = temp->data;
            //убіваєм цей дубль в правом піддереві рекурсивно
            ydalenie(help->r, temp->data);
        }
    }
}

template<typename vetochka>
void Derevo<vetochka>::proverka() {
    if (root == nullptr) {
        cout << "------------------" << endl;
        cout << "Дерево пусте" << endl;
        cout << "------------------" << endl;
    }
    else {
        cout << "------------------" << endl;
        cout << "Дерево не пусте" << endl;
        cout << "------------------" << endl;
    }
}



template<typename vetochka>
void Derevo<vetochka>::poisk(vetochka data) {
    BTNode* temp = root;
    while (temp != nullptr) {
        if (data == temp->data) {
            cout << "------------------" << endl;
            cout << "Адреса вказанного елементу: " << temp << " " << endl;
            cout << "------------------" << endl;
            return;
        }
        else {
            temp = (data < temp->data) ? temp->l : temp->r;
        }
    }
    if (temp == nullptr) {
        cout << "------------------" << endl;
        cout << "Такого елемента в дереві немає! " << endl;
        cout << "------------------" << endl;
    }
}


template<typename vetochka>
void Derevo<vetochka>::dop_fynk() {
    if (root == nullptr) {
        proverka();
        return;
    }
    BTNode* temp = root;
    while (temp->r != nullptr) { //дивимось чи наступний елемент равін налптр. якшо да то зупинка на цьому
        temp = temp->r; //тому шо саме велике число справа
    }
    if (temp->data > 0) {
        cout << "------------------" << endl;
        cout << "Елемент: " << temp->data << endl;
        cout << "------------------" << endl;
        cout << "Адреса: " << temp << endl;
        cout << "------------------" << endl;
    }
    else {
        cout << "------------------" << endl;
        cout << "Додатніх елементів немає " << endl;
        cout << "------------------" << endl;
    }
}

template<typename vetochka>
void Derevo<vetochka>::znaitu_glibiny_vyzla(vetochka data) {
    BTNode *temp = root;
    int count = 0;

    while (temp != nullptr) {
        if (data == temp->data) {
            cout << "------------------" << endl;
            cout << "Глибина вузла зі значенням:" << data << " дорівнює" << count << endl;
            return;
        }
        else {
            temp = (data < temp->data) ? temp->l : temp->r;
            count++;
        }
    }
    cout << "------------------" << endl;
    cout << "Такого значення немає " << endl;
    cout << "------------------" << endl;
};

int main() {
    cout << "Програма створена для реалізації алгоритму Дерева Пошуку. Числові значення." << endl;
    cout << "------------------" << endl;
    char simvol = '9';
    Derevo<int> derevuchko;
    do {
        cout << "--MENU--" << endl;
        cout << "1. Додати елемент в дерево " << endl;
        cout << "2. Видалити елемент з дерева" << endl;
        cout << "3. Переглянути всі елементи дерева" << endl;
        cout << "4. Знайти елемент за значенням" << endl;
        cout << "5. Дод.функція: Знайти максимальній додатній елемент" << endl;
        cout << "7. Доп функція: Знайти глибину вузла" << endl;
        cout << "------------------" << endl;
        cout << "6. Видалити все дерево " << endl;
        cout << "0. Вийти" << endl;

        cin >> simvol;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (simvol) {
            case '1': {
                int cifra;
                cout << "------------------" << endl;
                cout << "Введіть число яке хочете додати->";
                cin >> cifra;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                derevuchko.additem(cifra);
                cout << "Успішно додано!" << endl;
                cout << "------------------" << endl;
            }
                break;
                case '2': {
                    int cifra;
                    cout << "------------------" << endl;
                    cout << "Введіть число яке хочете видалити-> ";
                    cin >> cifra;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    derevuchko.ydalitem(cifra);
                    cout << "Успішно видалено!" << endl;
                    cout << "------------------" << endl;
                }
                break;
                case '3':
                derevuchko.prosmotrr();
                break;
                case '4': {
                    int cifra;
                    cout << "------------------" << endl;
                    cout << "Який елемент хочете знайти? ->";
                    cin >> cifra;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    derevuchko.poisk(cifra);
                }
                break;
                case '5':
                derevuchko.dop_fynk();
                break;

                case '6':
                derevuchko.clear();
                cout << "------------------" << endl;
                cout << "Все дерево було успішно очищено!" << endl;
                cout << "------------------" << endl;
            break;
            case '7': {
                int cifra;
                cout << "------------------" << endl;
                cout << "Введіть елемент який хочете знайти" << endl;
                cin >> cifra;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                derevuchko.znaitu_glibiny_vyzla(cifra);
                cout << "------------------" << endl;
            }
                break;
                case '0':
                break;
                default:
                cerr << "Unknown Value" << endl;
                exit(1);
        }
    }while (simvol != '0');
return 0;
}