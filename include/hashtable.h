#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

template<typename K, typename V>
class LinkedList {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void insert_list(const K& key, const V& value) {
        Node* current = head;
        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        Node* new_node = new Node(key, value);
        new_node->next = head;
        head = new_node;
    }

    V get_list(const K& key) const {
        Node* current = head;
        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        throw out_of_range("Key not found");
    }

    void remove_list(const K& key) {
        if (!head) return;
        if (head->key == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next && current->next->key != key) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    void print() const {
        Node* current = head;
        while (current) {
            cout << "[" << current->key << ": " << current->value << "] ";
            current = current->next;
        }
        cout <<endl;
    }

    bool contains(const K& key) const {
        Node* current = head;
        while (current) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void save_to_file(ofstream& file) const {
        Node* current = head;
        while (current) {
            file << current->key << " " << current->value << "\n";
            current = current->next;
        }
    }

    void save_to_binary_file(ofstream& file) const {
        Node* current = head;
        while (current) {
            size_t key_size = current->key.size();
            file.write(reinterpret_cast<char*>(&key_size), sizeof(key_size));
            file.write(current->key.c_str(), key_size);
            file.write(reinterpret_cast<char*>(&current->value), sizeof(current->value));
            current = current->next;
        }
    }

    void load_from_binary_file(ifstream& file) {
        while (file.peek() != EOF) {
            size_t key_size;
            file.read(reinterpret_cast<char*>(&key_size), sizeof(key_size));

            char* buffer = new char[key_size + 1];
            file.read(buffer, key_size);
            buffer[key_size] = '\0';
            K key = string(buffer);
            delete[] buffer;

            V value;
            file.read(reinterpret_cast<char*>(&value), sizeof(value));

            insert_list(key, value);
        }
    }
};

template<typename K, typename V>
class HashTable {
private:
    LinkedList<K, V>* table;
    size_t capacity;
    size_t size;

    size_t hash(const string& key) const {
        size_t hash_value = 0;
        for (char ch : key) {
            hash_value = 37 * hash_value + ch;
        }
        return hash_value % capacity;
    }

    size_t hash(int key) const {
        return key % capacity;
    }

public:
    HashTable(size_t table_size = 10) : capacity(table_size), size(0) {
        table = new LinkedList<K, V>[capacity];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(const K& key, const V& value) {
        size_t index = hash(key);
        if (!table[index].contains(key)) {
            size++;
        }
        table[index].insert_list(key, value);
    }

    V get(const K& key) const {
        size_t index = hash(key);
        return table[index].get_list(key);
    }

    void remove(const K& key) {
        size_t index = hash(key);
        if (table[index].contains(key)) {
            size--;
        }
        table[index].remove_list(key);
    }

    void print() const {
        for (size_t i = 0; i < capacity; ++i) {
            cout << "Index " << i << ": ";
            table[i].print();
        }
    }

    size_t get_size() const {
        return size;
    }

    void load_from_file(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            K key;
            V value;
            while (file >> key >> value) {
                insert(key, value);
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for loading");
        }
    }

    void save_to_file(const string& filename) const {
        ofstream file(filename, ios::out | ios::trunc);
        if (file.is_open()) {
            for (size_t i = 0; i < capacity; ++i) {
                table[i].save_to_file(file);
                file << "\n";
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for saving");
        }
    }

    void save_to_binary_file(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (file.is_open()) {
            for (size_t i = 0; i < capacity; ++i) {
                table[i].save_to_binary_file(file);
            }
            file.close();
        } else {
            throw runtime_error("Unable to open binary file for saving");
        }
    }

    void load_from_binary_file(const string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            for (size_t i = 0; i < capacity; ++i) {
                table[i].load_from_binary_file(file);
            }
            file.close();
        } else {
            throw runtime_error("Unable to open binary file for loading");
        }
    }
};

#endif // HASH_TABLE_H
