#include <iostream>


template<typename hihi>
//----------------------------------------------------------------------------------------------
class Node { //окремі елементи цього списку (окремі ноди)
    public:
    hihi data;
    Node *next, *prev;
    Node(hihi data) { //клас Ноди що описує один елемент двузв'язного списку
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    };
};
//-------------------------------------------------------------------------------------------
template<typename hihi>
class LinkedList {

    public:
    Node<hihi> *head, *tail;
    int Size;

    LinkedList();
    ~LinkedList();


    //прописуємо методи що відповідають за операції з цим двузв'язним списком
    void push_front(hihi data);
    void push_back(hihi data);

    void pop_front();
    void pop_back();
};
//------------------------------------------------------------------------------------------

template<typename hihi>
LinkedList<hihi>::LinkedList() { //конструктор лінкід ліст
    head = nullptr;
    tail = nullptr;
    Size = 0;
}

template<typename hihi>
LinkedList<hihi>::~LinkedList() { //діструктор лол
}

template<typename hihi>
void LinkedList<hihi>::push_front(hihi data) { //впіхнуть елемент з самого початку
    Node<hihi> *ptr = new Node<hihi>(data); //создаєм новій обєкт
    ptr->next=head; //якщо хед указує на існуючий об'єкт то і некст буде вказувати на існуючий
    if (head != nullptr) {
        head->prev = ptr;
    }
    if (tail == nullptr) {//означає шо ми додаємо САМИЙ ПЕРШИЙ обьєкт
        tail = ptr;
        head = ptr;
    }
    Size++;
}

template<typename hihi>
void LinkedList<hihi>::push_back(hihi data) { //впіхнуть елемент з самого кінця
    Node<hihi>* ptr = new Node<hihi>(data);
    ptr->prev = tail;
    if (tail != nullptr) {
        tail->next = ptr;
    }
    if (head == nullptr) {
        head = ptr;
        tail = ptr;
    }
    Size++;
}

template<typename hihi>
void LinkedList<hihi>::pop_front() { //удаляє з самого початку
    if (head == nullptr) {
        return;
    }

    Node<hihi> *ptr = head->next;
    if (ptr != nullptr) {
        ptr->prev = nullptr;
    }
    else {
        tail = nullptr;
    }
    delete head;
    head = ptr;
    Size--;
}


template<typename hihi>
void LinkedList<hihi>::pop_back() {

}


//-------------------------------------------------------------------------------------
int main() {

}
