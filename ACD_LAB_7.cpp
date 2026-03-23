//
// Created by c4ner on 3/20/2026.
//

#include "ACD_LAB_7.h"
#include <iostream>
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
            this->data = move(data);
            this->l = l;
            this->r = r;
        };
    };
    int Size;
    BTNode* root;
    void dodavanie(BTNode* &root, vetochka data); //зліва направо без урахування значенн
    void ydalenie(BTNode* &root, vetochka data);


    void clear_recursive(BTNode* &root);

    void prosmotr_recursive(BTNode* &root);
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
            cout << "------------------" << endl;
            cout << "Елементи дерева: " << endl;
            prosmotr_recursive(root);
            cout << "------------------" << endl;
        }
    }

    void vivod();

    void dop_fynk(vetochka data);

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
void Derevo<vetochka>::dodavanie(BTNode* &root, vetochka data) {
    if (root == nullptr) {
        root = new BTNode(data);
    }
    else {
        if (data < root->data) {
            //сиаут <<
            dodavanie(root->l, data);
        }
        else {
            //сиаут >>
            dodavanie(root->r, data);
        }
    }
}

template<typename vetochka>
void Derevo<vetochka>::clear_recursive(BTNode *&root) {
    if (root != nullptr) {
        clear_recursive(root->l);
        clear_recursive(root->r);
        delete root;
        root = nullptr;
    }
}

template<typename vetochka>
void Derevo<vetochka>::prosmotr_recursive(BTNode *&root) {
    if (root == nullptr) {
        return;
    }
    prosmotr_recursive(root->l);
    cout << root->data << " ";
    prosmotr_recursive(root->r);
}

template<typename vetochka>
void Derevo<vetochka>::ydalenie(BTNode* &root, vetochka data) {
    //пошук елемента
    if (root == nullptr) {
        proverka();
        return;
    }
    if (data < root->data) {
        ydalenie(root->l, data);
    }
    else if (data > root->data) {
        ydalenie(root->r, data);
    } //Знайшли:
    else {
        //один або нуль потомків
        //А: Нема лівого дітіни
        if (root->l == nullptr) {
            [[maybe_unused]] BTNode* temp = root->r; //запомнілі праву вітку
            delete root; //удаляєм
            root = temp; //прішиваєм ветку до родітеля
        }
        //нема правої дітітни:
        else if (root->r == nullptr) {
            [[maybe_unused]] BTNode* temp = root->l; //запомнілі лєву вєтку
            delete root;
            root = temp; //прішиваєм ветку
        }
        //як виразився мій репетитор з програмування: два потоки (самий піздєц)
        else {
            //шукаєм мінімального чєла ну там тіпа у правому поддєрєву (вліво до упору)
            BTNode* temp = root->r;
            while (temp->l != nullptr) {
                temp = temp->l;
            }
            //хаваєм данні:
            root->data = temp->data;
            //убіваєм цей дубль в правом піддереві рекурсивно
            ydalenie(root->r, temp->data);
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
void Derevo<vetochka>::vivod() {
}


template<typename vetochka>
void Derevo<vetochka>::dop_fynk(vetochka data) {
};

int main() {

}
