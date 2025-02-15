#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

template <typename T>
class Array {
private:
    T* data;
    size_t capacity;
    size_t length;

public:
    Array(size_t cap = 1000) : capacity(cap), length(0) {
        data = new T[capacity];
    }

    ~Array() {
        delete[] data;
    }

    // Добавление элемента в конец массива
    void push_back(const T& value) {
        if (length >= capacity) {
            throw overflow_error("Array is full");
        }
        data[length++] = value;
    }

    // Добавление элемента по индексу
    void insert_at(size_t index, const T& value) {
        if (index > length || length >= capacity) {
            throw out_of_range("Index out of range or array is full");
        }
        for (size_t i = length; i > index ; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++length;
    }

    // Удаление элемента по индексу
    void remove_at(size_t index) {
        if (index >= length) {
            throw out_of_range("Index out of range");
        }
        for (size_t i = index; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }
        --length;
    }

    // Замена элемента по индексу
    void replace_at(size_t index, const T& value) {
        if (index >= length) {
            throw out_of_range("Index out of range");
        }
        data[index] = value;
    }

    // Получение элемента по индексу
    T get_at(size_t index) const {
        if (index >= length) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Получение длины массива
    size_t size() const {
        return length;
    }

        // Сериализация в текстовый формат
    void save_to_text_file(const std::string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            // Сохраняем размер массива, чтобы можно было при чтении точно знать его размер
            file << length << "\n";  
            for (size_t i = 0; i < length; ++i) {
                file << data[i] << " ";
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for saving in text format");
        }
    }

    // Десериализация из текстового формата
    void load_from_text_file(const std::string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> length;  // Считываем длину массива
            for (size_t i = 0; i < length; ++i) {
                file >> data[i];  // Считываем каждый элемент массива
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for loading from text format");
        }
    }

    // Сериализация в бинарный формат
    void save_to_binary_file(const std::string& filename) const {
        ofstream file(filename, ios::binary);
        if (file.is_open()) {
            // Сохраняем размер массива в бинарном формате
            file.write(reinterpret_cast<const char*>(&length), sizeof(length));
            
            // Сохраняем элементы массива
            file.write(reinterpret_cast<const char*>(data), sizeof(T) * length);
            file.close();
        } else {
            throw runtime_error("Unable to open file for saving in binary format");
        }
    }

    // Десериализация из бинарного формата
    void load_from_binary_file(const std::string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            // Считываем размер массива
            file.read(reinterpret_cast<char*>(&length), sizeof(length));
            
            // Считываем элементы массива
            file.read(reinterpret_cast<char*>(data), sizeof(T) * length);
            file.close();
        } else {
            throw runtime_error("Unable to open file for loading from binary format");
        }
    }
};

#endif // ARRAY_H
