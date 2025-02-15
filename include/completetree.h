#ifndef COMPLETE_BINARY_TREE_H
#define COMPLETE_BINARY_TREE_H

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Реализация очереди на основе связного списка
template<typename T>
class Queue2 {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front_node;
    Node* back_node;
    size_t size;

public:
    Queue2() : front_node(nullptr), back_node(nullptr), size(0) {}

    ~Queue2() {
        while (!is_empty()) {
            pop();
        }
    }

    // Добавление элемента в конец очереди
    void push(const T& value) {
        Node* new_node = new Node(value);
        if (!back_node) {
            front_node = back_node = new_node;
        } else {
            back_node->next = new_node;
            back_node = new_node;
        }
        size++;
    }

    // Удаление элемента из начала очереди
    void pop() {
        if (is_empty()) throw out_of_range("Queue is empty");
        Node* temp = front_node;
        front_node = front_node->next;
        if (!front_node) back_node = nullptr;  // Очередь пуста
        delete temp;
        size--;
    }

    // Получение элемента из начала очереди
    T& front() {
        if (is_empty()) throw out_of_range("Queue is empty");
        return front_node->data;
    }

    const T& front() const {
        if (is_empty()) throw out_of_range("Queue is empty");
        return front_node->data;
    }

    // Проверка, пуста ли очередь
    bool is_empty() const {
        return size == 0;
    }

    // Получение размера очереди
    size_t get_size() const {
        return size;
    }
};

// Реализация полного двоичного дерева
template<typename T>
class CompleteBinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t size;

    // Вспомогательная функция для поиска первого пустого места для добавления нового узла
    void add_node(Node* new_node) {
        Queue2<Node*> queue2;
        queue2.push(root);

        while (!queue2.is_empty()) {
            Node* current = queue2.front();
            queue2.pop();

            // Если есть место для левого ребенка, добавляем новый узел
            if (!current->left) {
                current->left = new_node;
                return;
            } else {
                queue2.push(current->left);
            }

            // Если есть место для правого ребенка, добавляем новый узел
            if (!current->right) {
                current->right = new_node;
                return;
            } else {
                queue2.push(current->right);
            }
        }
    }

    // Вспомогательная функция для проверки, является ли дерево полным
    bool is_complete_queue() const {
        if (!root) return false;  // Пустое дерево считается полным

        Queue2<Node*> queue2;
        queue2.push(root);
        bool must_be_leaf = false;  // Этот флаг указывает, что все последующие узлы должны быть листьями

        while (!queue2.is_empty()) {
            Node* current = queue2.front();
            queue2.pop();

            // Если текущий узел - "пустой" узел (0), устанавливаем флаг must_be_leaf и проверяем далее
            if (current->data == 0) {
                must_be_leaf = true;
                continue;  // Пропускаем этот узел, так как это пустое место
            }

            // Проверяем левый потомок
            if (current->left && current->left->data != 0) {
                if (must_be_leaf == true){ 
                    return false;  // Если левый ребенок найден после установки флага, дерево не полное
                }
                queue2.push(current->left);
            } else {
                must_be_leaf = true;  // Если нет левого ребенка, все последующие узлы должны быть листьями
            }       

            // Проверяем правый потомок
            if (current->right && current->right->data != 0) {
                if (must_be_leaf == true){ 
                    return false;  // Если правый ребенок найден после установки флага, дерево не полное
                }
                queue2.push(current->right);
            } else {
                must_be_leaf = true;  // Если нет правого ребенка, все последующие узлы должны быть листьями
            }
        }

        return true;  // Если мы прошли через все узлы и не нарушили условие, дерево полное
    }





    // Вспомогательная функция для поиска элемента
    Node* find_node(Node* node, const T& value) const {
        if (!node) return nullptr;

        if (node->data == value) return node;

        Node* left_result = find_node(node->left, value);
        if (left_result) return left_result;

        return find_node(node->right, value);
    }

    // Вспомогательная функция для удаления дерева
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    // Вспомогательная функция для загрузки данных в дерево
    void load_from_queue(Queue2<T>& data_queue) {
        while (!data_queue.is_empty()) {
            add(data_queue.front());
            data_queue.pop();
        }
    }

public:
    CompleteBinaryTree() : root(nullptr), size(0) {}

    ~CompleteBinaryTree() {
        clear(root);
    }

    // Добавление элемента
    void add(const T& value) {
        Node* new_node = new Node(value);
        if (!root) {
            root = new_node;
        } else {
            add_node(new_node);
        }

        size++;
    }

// Удаление элемента
    void remove(const T& value) {
        if (!root) {
            throw runtime_error("Tree is empty");
        }

        // Если дерево состоит из одного узла
        if (size == 1 && root->data == value) {
            delete root;
            root = nullptr;
            size--;
            return;
        }

        Queue2<Node*> queue;
        queue.push(root);

        Node* node_to_delete = nullptr;  // Указатель на узел, который нужно удалить
        Node* last_node = nullptr;       // Указатель на последний узел в дереве
        Node* last_node_parent = nullptr;// Указатель на родителя последнего узла

        // Поиск узла для удаления и последнего узла
        while (!queue.is_empty()) {
            Node* current = queue.front();
            queue.pop();

            if (current->data == value) {
                node_to_delete = current;  // Найден узел для удаления
            }

            if (current->left) {
                queue.push(current->left);
                last_node_parent = current;
                last_node = current->left;
            }

            if (current->right) {
                queue.push(current->right);
                last_node_parent = current;
                last_node = current->right;
            }
        }

        // Если узел для удаления не найден
        if (!node_to_delete) {
            throw runtime_error("Element not found");
        }

        // Если найден последний узел и узел для удаления
        if (last_node) {
            node_to_delete->data = last_node->data;  // Замена данных
            // Удаляем последний узел
            if (last_node_parent->right == last_node) {
                delete last_node_parent->right;
                last_node_parent->right = nullptr;
            } else {
                delete last_node_parent->left;
                last_node_parent->left = nullptr;
            }
        }

        size--;  // Уменьшаем размер дерева
    }

    // Поиск элемента
    bool find(const T& value) const {
        return find_node(root, value) != nullptr;
    }

    // Проверка, является ли дерево полным
    bool is_complete_tree() const {
        return is_complete_queue();
    }

    // Печать дерева (обход в ширину)
    void print() const {
        if (!root) return;

        Queue2<Node*> queue2;
        queue2.push(root);

        while (!queue2.is_empty()) {
            Node* current = queue2.front();
            queue2.pop();
            cout << current->data << " ";

            if (current->left) queue2.push(current->left);
            if (current->right) queue2.push(current->right);
        }
        cout << endl;
    }


    // Получение размера дерева
    size_t get_size() const {
        return size;
    }

    // Загрузка данных из файла
    void load_from_file(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            Queue2<T> data_queue;  // Используем очередь для хранения данных, пока не загрузим их в дерево
            T value;
            while (file >> value) {
                data_queue.push(value);
            }
            file.close();
            load_from_queue(data_queue);  // Загружаем элементы в дерево
        } else {
            throw runtime_error("Unable to open file for loading");
        }
    }


    // Сохранение дерева в файл (обход в ширину)
    void save_to_file(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            Queue2<Node*> queue;
            queue.push(root);

            while (!queue.is_empty()) {
                Node* current = queue.front();
                queue.pop();
                file << current->data << " ";

                if (current->left) queue.push(current->left);
                if (current->right) queue.push(current->right);
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for saving");
        }
    }

    // Сохранение дерева в бинарный файл
    void save_to_binary_file(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (file.is_open()) {
            Queue2<Node*> queue;
            queue.push(root);

            while (!queue.is_empty()) {
                Node* current = queue.front();
                queue.pop();
                file.write(reinterpret_cast<const char*>(&current->data), sizeof(T));  // Запись данных узла

                if (current->left) queue.push(current->left);
                if (current->right) queue.push(current->right);
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for saving");
        }
    }

    // Загрузка дерева из бинарного файла
    void load_from_binary_file(const string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            Queue2<T> data_queue;
            T value;
            while (file.read(reinterpret_cast<char*>(&value), sizeof(T))) {
                data_queue.push(value);
            }
            file.close();
            load_from_queue(data_queue);  // Загружаем элементы в дерево
        } else {
            throw runtime_error("Unable to open file for loading");
        }
    }

};

#endif // COMPLETE_BINARY_TREE_H
