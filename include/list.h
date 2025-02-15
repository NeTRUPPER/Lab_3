#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

template<typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    ~SinglyLinkedList() {
        while (head) {
            pop_front();
        }
    }

    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        size++;
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!head) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
        size++;
    }

    void pop_front() {
        if (!head) throw out_of_range("List is empty");
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void pop_back() {
        if (!head) throw out_of_range("List is empty");
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next->next) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        size--;
    }

    void remove(const T& value) {
        if (!head) return;

        if (head->data == value) {
            pop_front();
            return;
        }

        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            cout << "Removed " << value << " from the singly linked list if it existed.\n";
        }else{ 
            cout << "Element not found.\n";
        }
        
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

    // Сериализация в бинарном формате
    void save_to_binary_file(const string& filename) const {
        ofstream file(filename, ios::binary | ios::trunc);
        if (file.is_open()) {
            Node* temp = head;
            while (temp != nullptr) {
                file.write(reinterpret_cast<const char*>(&temp->data), sizeof(T));  // Записываем данные в бинарном виде
                temp = temp->next;
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file");
        }
    }

    // Десериализация из бинарного файла
    void load_from_binary_file(const string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            T value;
            while (file.read(reinterpret_cast<char*>(&value), sizeof(T))) {  // Читаем данные в бинарном виде
                push_back(value);
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file");
        }
    }
};

#endif // SINGLY_LINKED_LIST_H
