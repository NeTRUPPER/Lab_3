#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    size_t size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (size > 0) {
            pop();
        }
    }

    void push(const T& value) {
        Node* new_node = new Node(value);
        if (!rear) {
            front = rear = new_node;
        } else {
            rear->next = new_node;
            rear = new_node;
        }
        size++;
    }

    void pop() {
        if (!front) throw out_of_range("Queue is empty");
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr; // Если очередь стала пустой
        delete temp;
        size--;
    }

    T front_value() const {
        if (!front) throw out_of_range("Queue is empty");
        return front->data;
    }

    size_t get_size() const {
        return size;
    }

    void print() const {
        Node* current = front;
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
            T value;
            while (file >> value) {
                push(value);
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for loading");
        }
    }

    // Сохранение данных в файл
    void save_to_file(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            Node* current = front;
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
            Node* current = front;
            while (current) {
                file.write(reinterpret_cast<const char*>(&current->data), sizeof(T));  // Записываем данные в бинарном виде
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
            while (file.read(reinterpret_cast<char*>(&value), sizeof(T))) {  // Читаем данные в бинарном виде
                push(value);
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for loading");
        }
    }
};

#endif // QUEUE_H
