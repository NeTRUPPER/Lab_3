#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head) {
            pop_front();
        }
    }

    void push_front(const T& value) {
        Node* new_node = new Node(value);
        if (!head) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        size++;
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!head) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        size++;
    }

    void pop_front() {
        if (!head) throw out_of_range("List is empty");
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr; // Если список стал пустым
        delete temp;
        size--;
    }

    void pop_back() {
        if (!tail) throw out_of_range("List is empty");
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr; // Если список стал пустым
        delete temp;
        size--;
    }

    void remove(const T& value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current == head) {
                    pop_front();
                    cout << "Removed " << value << " from the doubly linked list if it existed.\n";
                } else if (current == tail) {
                    pop_back();
                    cout << "Removed " << value << " from the doubly linked list if it existed.\n";
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    size--;
                    cout << "Removed " << value << " from the doubly linked list if it existed.\n";
                }
                return;
            }
            current = current->next;
        }

        cout << "Element not found.\n";
    }

    Node* find(const T& value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    size_t get_size() const {
        return size;
    }

    void load_from_file(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            T value;
            while (file >> value) {
                push_back(value);
            }
            file.close();
        }
    }

    void save_to_file(const string& filename) const {
        ofstream file(filename, ios::out | ios::trunc);
        if (file.is_open()) {
            Node* temp = head;
            while (temp != nullptr) {
                file << temp->data << " ";
                temp = temp->next;
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file");
        }
    }

    // Сохранение в бинарный формат
    void save_to_binary(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (!file) throw runtime_error("Unable to open file for binary saving");

        Node* current = head;
        while (current) {
            file.write(reinterpret_cast<const char*>(&current->data), sizeof(T));
            current = current->next;
        }

        file.close();
    }

    // Загрузка из бинарного формата
    void load_from_binary(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file) throw runtime_error("Unable to open file for binary loading");

        while (file) {
            T value;
            file.read(reinterpret_cast<char*>(&value), sizeof(T));
            if (file) push_back(value);
        }

        file.close();
    }
};

#endif // DOUBLY_LINKED_LIST_H
