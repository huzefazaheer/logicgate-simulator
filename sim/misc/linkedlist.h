#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <vector>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next = nullptr;
    };

    Node* head = nullptr;

public:
    // Constructor and Destructor
    LinkedList() : head(nullptr) {}
    ~LinkedList() { clear(); }

    // Create list from array
    void createListFromArray(T data[], int size) {
        if (size == 0) return;
        head = new Node;
        Node* curr = head;
        curr->data = data[0];
        for (int i = 1; i < size; i++) {
            Node* newnode = new Node;
            newnode->data = data[i];
            curr->next = newnode;
            curr = curr->next;
        }
    }

    // Append at tail
    void appendAtTail(T data) {
        Node* newnode = new Node;
        newnode->data = data;
        if (head == nullptr) {
            head = newnode;
            return;
        }

        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newnode;
    }

    // Insert at head
    void insertAtHead(T data) {
        Node* newhead = new Node;
        newhead->data = data;
        newhead->next = head;
        head = newhead;
    }

    // Get length
    int getLength() const {
        Node* curr = head;
        int length = 0;
        while (curr != nullptr) {
            length++;
            curr = curr->next;
        }
        return length;
    }

    // Insert at position
    void insertAtPosition(T data, int pos) {
        if (pos == 0) return insertAtHead(data);
        if (pos == getLength()) return appendAtTail(data);

        Node* newnode = new Node;
        newnode->data = data;
        Node* curr = head;
        bool invalidPos = false;
        for (int i = 0; i < pos - 1; i++) {
            if (curr->next == nullptr) {
                invalidPos = true;
                break;
            }
            curr = curr->next;
        }
        if (!invalidPos) {
            if (curr->next == nullptr) curr->next = newnode;
            else {
                newnode->next = curr->next;
                curr->next = newnode;
            }
        }
    }

    // Delete at head
    void deleteAtHead() {
        if (head == nullptr) return;
        Node* newhead = head->next;
        delete head;
        head = newhead;
    }

    // Delete at tail
    void deleteAtTail() {
        if (head == nullptr) return;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* curr = head;
        while (curr->next->next != nullptr) {
            curr = curr->next;
        }
        delete curr->next;
        curr->next = nullptr;
    }

    // Delete at position
    void deleteAtPosition(int pos) {
        if (pos == 0) return deleteAtHead();
        Node* curr = head;
        bool invalidPos = false;
        for (int i = 0; i < pos - 1; i++) {
            if (curr->next == nullptr) {
                invalidPos = true;
                break;
            }
            curr = curr->next;
        }
        if (!invalidPos) {
            if (curr->next == nullptr) deleteAtTail();
            else {
                Node* tmp = curr->next->next;
                delete curr->next;
                curr->next = tmp;
            }
        }
    }

    // Search
    int search(T value) const {
        Node* curr = head;
        int index = 1;
        while (curr != nullptr) {
            if (curr->data == value) return index - 1;
            curr = curr->next;
            index++;
        }
        return -1;
    }

    // Print list
    void printList() const {
        Node* curr = head;
        while (curr != nullptr) {
            std::cout << curr->data << " -> ";
            curr = curr->next;
        }
        std::cout << "NULL" << std::endl;
    }

    std::vector<T> getArray(){
        std::vector <T> arr;
        Node* curr = head;
        while (curr != nullptr) {
            arr.push_back(curr->data);
            curr = curr->next;
        }
        return arr;
    }

    // Clear list
    void clear() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
        head = nullptr;
    }
};


#endif