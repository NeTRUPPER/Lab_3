#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
#include <fstream>

using namespace std;

template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head; // Указатель на верхний элемент стека
    size_t size;
    size_t capacity;

public:
    Stack(size_t capacity = 100000) : head(nullptr), size(0), capacity(capacity) {}

    ~Stack() {
        while (size > 0) {
            pop();
        }
    }

    void push(const T& value) {
        if (size >= capacity) {
            cerr << "Stack is full, cannot push new value: " << value << endl;
            return; // Не добавляем элемент, если стек полон
        }
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        size++;
    }

     T peek() const {
        if (size == 0) {
            throw out_of_range("Stack is empty");
        }
        return head->data;
    }

    void pop() {
        if (!head) throw out_of_range("Stack is empty");
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    T head_value() const {
        if (!head) throw out_of_range("Stack is empty");
        return head->data;
    }

    size_t get_size() const {
        return size;
    }

    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Загрузка данных из файла
    void load_from_file(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            Stack<T> temp_stack;  // Временный стек для чтения из файла
            T value;

            // Читаем элементы из файла и добавляем их во временный стек
            while (file >> value) {
                temp_stack.push(value);
            }

            file.close();

            // Перекладываем элементы из временного стека в основной стек
            // Таким образом элементы попадут в основной стек в том порядке, как они шли в файле
            while (temp_stack.get_size() > 0) {
                push(temp_stack.peek());
                temp_stack.pop();
            }
        } else {
            throw runtime_error("Unable to open file for loading");
        }
    }

    // Сохранение данных в файл
    void save_to_file(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            Node* current = head;
            while (current) {
                file << current->data << " ";
                current = current->next;
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for saving");
        }
    }

    // Сериализация в бинарном формате
    void save_to_binary_file(const string& filename) const {
        ofstream file(filename, ios::binary | ios::trunc);
        if (file.is_open()) {
            Node* current = head;
            while (current) {
                file.write(reinterpret_cast<const char*>(&current->data), sizeof(T));  // Записываем данные в бинарном формате
                current = current->next;
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for saving");
        }
    }

    // Десериализация из бинарного файла
    void load_from_binary_file(const string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            T value;
            while (file.read(reinterpret_cast<char*>(&value), sizeof(T))) {  // Читаем данные в бинарном формате
                push(value);
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for loading");
        }
    }

};

#endif // STACK_H
