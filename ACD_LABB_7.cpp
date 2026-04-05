//
// Created by c4ner on 3/20/2026.
//
#include <iostream>
using namespace std;

template<typename vetochka>
class Derevo {
    public:
    Derevo();
    ~Derevo();

    Node* dodavanie(const vetochka &data); //зліва направо без урахування значення
    void ydalenie(vetochka data);

    void proverka();
    void prosmotr();
    void vivod();

    void clear();

    void dop_fynk(vetochka data);



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

};

template<typename vetochka>
Derevo<vetochka>::Derevo() : Size(0), root(nullptr) {
}

template<typename vetochka>
Derevo<vetochka>::~Derevo() {

}

template<typename vetochka>
Node* Derevo<vetochka>::dodavanie(const vetochka &data) {
    if (root == nullptr) {
        root = new BTNode(data);
    }
    else {
        if (root->l == nullptr || root->r == nullptr) {
            BTNode* current = this->root;
            while (current != nullptr) {
                current = current->root;
            }
            current->root->r->l = new BTNode(data);
        }
    }
    Size++;
}

template<typename vetochka>
void Derevo<vetochka>::ydalenie(vetochka data) {
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
void Derevo<vetochka>::prosmotr() {
}

template<typename vetochka>
void Derevo<vetochka>::vivod() {
}

template<typename vetochka>
void Derevo<vetochka>::clear() {
}

template<typename vetochka>
void Derevo<vetochka>::dop_fynk(vetochka data) {
};

int main() {

}
