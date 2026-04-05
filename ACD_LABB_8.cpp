//
// Created by c4ner on 3/28/2026.
//
#include  <iostream>
#include <limits>
using namespace std;

template <typename VEt>
class DEREvo {
    private:
    class BTNode {
    public:
        BTNode* l;
        BTNode* r;
        VEt data;

        explicit BTNode(VEt data = VEt(), BTNode* l = nullptr, BTNode* r = nullptr) {
            this->data = std::move(data);
            this->l = l;
            this->r = r;
        };
    };
    int Size;
    BTNode* root;

    void dodavanie(BTNode* &pomogite, VEt data); //зліва направо без урахування значенн
    void ydalenie(BTNode* &help, VEt data);
    void clear_recursive(BTNode* &sos);
    int yzli_dva_nagatka(BTNode* &koreni);
    void print_tree(BTNode* node, int space);

    bool dop_dop_fynk(BTNode* node, int syme);
    public:
    DEREvo();
    ~DEREvo();
    void poisk(VEt data);
    void print() {
        print_tree(root, 0);
    }
    void additem(VEt data) { dodavanie(root, data); Size++; }
    void ydalitem(VEt data) {
        ydalenie(root, data);
        if (root != nullptr) {
            Size--;
        }
    }

    void clear() {clear_recursive(root); Size = 0;}
    void dod_fync () {cout << "Вузлів з двома нащадками: " << yzli_dva_nagatka(root) << endl;}

    void proverka();
    void dop_fynk(int syme) {
        if (dop_dop_fynk(root, syme)) {
            cout << "------------------" << endl;
            cout << "Так, шлях з такою сумою існує!" << endl;
            cout << "------------------" << endl;
        } else {
            cout << "------------------" << endl;
            cout << "Ні, шляху з такою сумою немає." << endl;
            cout << "------------------" << endl;
        }
    }

};

template<typename VEt>
DEREvo<VEt>::DEREvo() {
    root = nullptr;
    Size = 0;
}

template<typename VEt>
DEREvo<VEt>::~DEREvo() {
    while (Size) {
        clear();
    }
}

template<typename VEt>
void DEREvo<VEt>::poisk(VEt data) {
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

template<typename VEt>
void DEREvo<VEt>::dodavanie(BTNode *&pomogite, VEt data) {
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

template<typename VEt>
void DEREvo<VEt>::ydalenie(BTNode *&help, VEt data) {
    //пошук елемента
    if (help == nullptr) {
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
            BTNode* temp = help->r; //запомнілі праву вітку
            delete help; //удаляєм
            help = temp; //прішиваєм ветку до родітеля
        }
        //нема правої дітітни:
        else if (help->r == nullptr) {
            [[maybe_unused]] BTNode* temp = help->l; //запомнілі лєву вєтку
            delete help;
            help = temp; //прішиваєм ветку
        }
        //два потоки (самий піздєц)
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

template<typename VEt>
void DEREvo<VEt>::clear_recursive(BTNode *&sos) {
    if (sos != nullptr) {
        clear_recursive(sos->l);
        clear_recursive(sos->r);
        delete sos;
        sos = nullptr;
    }
}

template<typename VEt>
int DEREvo<VEt>::yzli_dva_nagatka(BTNode *&koreni) {
    if (koreni == nullptr) {
        return 0;
    }
    unsigned short count = 0;

    if (koreni->l != nullptr && koreni->r != nullptr) {
        count = 1;
    }
    count = count + yzli_dva_nagatka(koreni->l);
    count = count + yzli_dva_nagatka(koreni->r);
    //temp->l != nullptr && temp->r != nullptr ? ++koreni->l && ++koreni->r && temp->l : temp->l;
    return count;
}

template<typename VEt>
void DEREvo<VEt>::print_tree(BTNode *node, int space) {
    if (node == nullptr) {
        return;
    }
    space += 5;
    print_tree(node->r, space);
    for (int i = 5; i < space; i++) {
        cout << " ";
    }
    cout << node->data << "\n";
    print_tree(node->l, space);
}

template<typename VEt>
bool DEREvo<VEt>:: dop_dop_fynk(BTNode* node, int syme) {
        if (node == nullptr) {
            return false;
        }
        //випадок якщо елемент не має нащадків
        if (node->l == nullptr && node->r == nullptr) {
            return syme == node->data;
        }
         //зн поточного вузла - і шук. залишки в гілках
        int ostacha = syme - node->data;
        return dop_dop_fynk(node->l, ostacha) || dop_dop_fynk(node->r, ostacha);
}

template<typename VEt>
void DEREvo<VEt>::proverka() {
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


int main() {
    DEREvo<double> tree;
    cout << "Програма створена для реалізації алгоритму Дерева Пошуку. Числові значення." << endl;
    cout << "------------------" << endl;
    char simvol = '9';
    do {
        cout << "--MENU--" << endl;
        cout << "1. Додати елемент в дерево " << endl;
        cout << "2. Видалити елемент з дерева" << endl;
        cout << "3. Переглянути всі елементи дерева" << endl;
        cout << "4. Знайти елемент за значенням" << endl;
        cout << "5. Дод.функція: Знайти максимальній додатній елемент" << endl;
        cout << "7. ДОД функц. Тру фалс." << endl;
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
                tree.additem(cifra);
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
                    tree.ydalitem(cifra);
                    cout << "Успішно видалено!" << endl;
                    cout << "------------------" << endl;
                }
                break;
                case '3':
                tree.print();
                break;
                case '4': {
                    int cifra;
                    cout << "------------------" << endl;
                    cout << "Який елемент хочете знайти? ->";
                    cin >> cifra;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    tree.poisk(cifra);
                }
                break;
                case '5':
                tree.dod_fync();
                break;

                case '6':
                tree.clear();
                cout << "------------------" << endl;
                cout << "Все дерево було успішно очищено!" << endl;
                cout << "------------------" << endl;
            break;
            case '7': {
                int cifra;
                cout << "Введіть суму:" << endl;
                cin >> cifra;
                tree.dop_fynk(cifra);
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
