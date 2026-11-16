#include <iostream>

class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    // Insert at the beginning
    void addFirst(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        size++;
    }

    // Insert at the end
    void addLast(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
        size++;
    }

    // Insert at a specific position
    void addAt(int val, int pos) {
        if (pos < 0 || pos > size) {
            std::cout << "Invalid position!\n";
            return;
        }
        if (pos == 0) {
            addFirst(val);
            return;
        }
        Node* newNode = new Node(val);
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }

    // Remove from the beginning
    void removeFirst() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    // Remove from the end
    void removeLast() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next->next)
                temp = temp->next;
            delete temp->next;
            temp->next = nullptr;
        }
        size--;
    }

    // Remove from a specific position
    void removeAt(int pos) {
        if (pos < 0 || pos >= size) {
            std::cout << "Invalid position!\n";
            return;
        }
        if (pos == 0) {
            removeFirst();
            return;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++)
            temp = temp->next;
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        size--;
    }

    // Print the list
    void print() {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }

    // Destructor to free memory
    ~LinkedList() {
        while (head)
            removeFirst();
    }
};

int main() {
    LinkedList list;
    list.addFirst(10);
    list.addLast(20);
    list.addLast(30);
    list.addAt(15, 1);  // Insert 15 at position 1
    list.print();        // Output: 10 -> 15 -> 20 -> 30 -> NULL

    list.removeAt(1);    // Remove value at position 1 (15)
    list.print();        // Output: 10 -> 20 -> 30 -> NULL

    list.removeFirst();  // Remove first node
    list.print();        // Output: 20 -> 30 -> NULL

    list.removeLast();   // Remove last node
    list.print();        // Output: 20 -> NULL

    return 0;
}