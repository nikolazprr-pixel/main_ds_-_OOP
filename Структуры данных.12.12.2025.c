#include <iostream>
#include <windows.h>

using namespace std;


struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};


class LinkedList {
private:


public:
    LinkedList() : head(nullptr) {}

 
    void pushFront(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

 
    void popFront() {
        if (!head) return;

        Node* temp = head;
        head = head->next;
        delete temp;
    }


    void print() {
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

  
    ~LinkedList() {
        while (head) {
            popFront();
        }
    }
};

int main() {
    SetConsoleOutputCP(1251);

    LinkedList list;

    list.pushFront(10);
    list.pushFront(20);
    list.pushFront(30);

    cout << "Текущий список: ";
    list.print();

    list.popFront();
    cout << "После удаления первого элемента: ";
    list.print();

    return 0;
}
