#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array.h"
#include "list.h"
#include "twolist.h"
#include "queue.h"
#include "stack.h"
#include "hashtable.h"
#include "completetree.h"

using namespace std;

void execute_query(const string& query, Array<string>& array, SinglyLinkedList<string>& singly_list, DoublyLinkedList<string>& doubly_list, Queue<string>& queue, Stack<string>& stack, HashTable<size_t, string>& hash_table, CompleteBinaryTree<int>& tree, string& filename) {
    istringstream iss(query);
    string command;
    iss >> command;

    if (command == "MPUSH") {
        array.load_from_text_file(filename);
        string value;
        iss >> value;
        array.push_back(value);
        array.save_to_text_file(filename);
        cout << "Added " << value << " to the array.\n";
    } else if (command == "MINSETRT") {
        array.load_from_text_file(filename);
        string value;
        size_t index;
        iss >> index >> value;
        try {
            array.insert_at(index, value);
            array.save_to_text_file(filename);
            cout << "Inserted " << value << " at index " << index << " in the array.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "MDEL") {
        array.load_from_text_file(filename);
        size_t index;
        iss >> index;
        try {
            array.remove_at(index);
            array.save_to_text_file(filename);
            cout << "Removed element at index " << index << " from the array.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "MREPLACE") {
        array.load_from_text_file(filename);
        size_t index;
        string value;
        iss >> index >> value;
        try {
            array.replace_at(index, value);
            array.save_to_text_file(filename);
            cout << "Replaced element at index " << index << " with " << value << " in the array.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "MGET") {
        array.load_from_text_file(filename);
        size_t index;
        iss >> index;
        try {
            string value = array.get_at(index);
            cout << "Element at index " << index << " in the array: " << value << "\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "MLENGTH") {
        array.save_to_text_file(filename);
        cout << "Array length: " << array.size() << "\n";
    } else if (command == "LPUSH_HEAD") {
        singly_list.load_from_file(filename);
        string value;
        iss >> value;
        singly_list.push_front(value);
        singly_list.save_to_file(filename);
        cout << "Added " << value << " to the front of the singly linked list.\n";
    } else if (command == "LPUSH_TAIL") {
        singly_list.load_from_file(filename);
        string value;
        iss >> value;
        singly_list.push_back(value);
        singly_list.save_to_file(filename);
        cout << "Added " << value << " to the back of the singly linked list.\n";
    } else if (command == "LPOP_HEAD") {
        singly_list.load_from_file(filename);
        try {
            singly_list.pop_front();
            singly_list.save_to_file(filename);
            cout << "Removed the front element from the singly linked list.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "LPOP_TAIL") {
        singly_list.load_from_file(filename);
        try {
            singly_list.pop_back();
            singly_list.save_to_file(filename);
            cout << "Removed the back element from the singly linked list.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "LREMOVE") {
        singly_list.load_from_file(filename);
        string value;
        iss >> value;
        singly_list.remove(value);
        singly_list.save_to_file(filename);
    } else if (command == "LFIND") {
        singly_list.load_from_file(filename);
        string value;
        iss >> value;
        auto node = singly_list.find(value);
        if (node) {
            cout << "Found: " << node->data << " in singly linked list.\n";
        } else {
            cout << "Not found in singly linked list.\n";
        }
    } else if (command == "LPRINT") {
        singly_list.load_from_file(filename);
        singly_list.print();
    } else if (command == "LGET_SIZE") {
        singly_list.load_from_file(filename);
        cout << "Singly linked list size: " << singly_list.get_size() << "\n";
    }else if (command == "L2PUSH_HEAD") {
        doubly_list.load_from_file(filename);
        string value;
        iss >> value;
        doubly_list.push_front(value);
        doubly_list.save_to_file(filename);
        cout << "Added " << value << " to the front of the doubly linked list.\n";
    } else if (command == "L2PUSH_TAIL") {
        doubly_list.load_from_file(filename);
        string value;
        iss >> value;
        doubly_list.push_back(value);
        doubly_list.save_to_file(filename);
        cout << "Added " << value << " to the back of the doubly linked list.\n";
    } else if (command == "L2POP_HEAD") {
        doubly_list.load_from_file(filename);
        try {
            doubly_list.pop_front();
            doubly_list.save_to_file(filename);
            cout << "Removed the front element from the doubly linked list.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "L2POP_TAIL") {
        doubly_list.load_from_file(filename);
        try {
            doubly_list.pop_back();
            doubly_list.save_to_file(filename);
            cout << "Removed the back element from the doubly linked list.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "L2REMOVE") {
        doubly_list.load_from_file(filename);
        string value;
        iss >> value;
        doubly_list.remove(value);
        doubly_list.save_to_file(filename);
    } else if (command == "L2FIND") {
        doubly_list.load_from_file(filename);
        string value;
        iss >> value;
        auto node = doubly_list.find(value);
        if (node) {
            cout << "Found: " << node->data << " in doubly linked list.\n";
        } else {
            cout << "Not found in doubly linked list.\n";
        }
    } else if (command == "L2PRINT") {
        doubly_list.load_from_file(filename);
        doubly_list.print();
    } else if (command == "L2GET_SIZE") {
        doubly_list.load_from_file(filename);
        cout << "Doubly linked list size: " << doubly_list.get_size() << "\n";
    }else if (command == "QPUSH") {
        queue.load_from_file(filename);
        string value;
        iss >> value;
        queue.push(value);
        queue.save_to_file(filename);
        cout << "Added " << value << " to the queue.\n";
    } else if (command == "QPOP") {
        queue.load_from_file(filename);
        try {
            queue.pop();
            queue.save_to_file(filename);
            cout << "Removed the front element from the queue.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "QFRONT") {
        queue.load_from_file(filename);
        try {
            cout << "Front of queue: " << queue.front_value()  << "\n";
            queue.save_to_file(filename);
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "QPRINT") {
        queue.load_from_file(filename);
        queue.print();
    } else if (command == "QGET_SIZE") {
        queue.load_from_file(filename);
        cout << "Queue size: " << queue.get_size() << "\n";
    } else if (command == "SPUSH") {
        stack.load_from_file(filename);
        string value;
        iss >> value;
        stack.push(value);
        stack.save_to_file(filename);
        cout << "Added " << value << " to the stack.\n";
    } else if (command == "SPOP") {
        stack.load_from_file(filename);
        try {
            stack.pop();
            stack.save_to_file(filename);
            cout << "Removed the top element from the stack.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "SHEAD") {
        stack.load_from_file(filename);
        try {
            cout << "Top of stack: " << stack.head_value() << "\n";
            stack.save_to_file(filename);
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "SPRINT") {
        stack.load_from_file(filename);
        stack.print();
    } else if (command == "SGET_SIZE") {
        stack.load_from_file(filename);
        cout << "Stack size: " << stack.get_size() << "\n";
    } else if (command == "HPUSH") {
        hash_table.load_from_file(filename);
        string value;
        size_t key;
        iss >> key >> value;
        hash_table.insert(key, value);
        hash_table.save_to_file(filename);
        cout << "Added (" << key << ", " << value << ") to the hash table.\n";
    } else if (command == "HGET") {
        hash_table.load_from_file(filename);
        size_t key;
        iss >> key;
        try {
            string value = hash_table.get(key);
            cout << "Value for key " << key << ": " << value << "\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "HDEL") {
        hash_table.load_from_file(filename);
        size_t key;
        iss >> key;
        try {
            hash_table.remove(key);
            hash_table.save_to_file(filename);
            cout << "Removed key " << key << " from the hash table.\n";
        } catch (const out_of_range& e) {
            cerr << e.what() << "\n";
        }
    } else if (command == "HPRINT") {
        hash_table.load_from_file(filename);
        hash_table.print();
    } else if (command == "TPUSH") {
        tree.load_from_file(filename);
        int value;
        iss >> value;
        tree.add(value);
        tree.save_to_file(filename);
        cout << "Added: " << value << endl;
    } else if (command == "TDEL") {
        tree.load_from_file(filename);
        int value;
        iss >> value;
        tree.remove(value);
        tree.save_to_file(filename);
        cout << "Remove: " << value << endl;
    } else if (command == "TFIND") {
        tree.load_from_file(filename);
        int value;
        iss >> value;
        bool found = tree.find(value);
        cout << "Element " << value << (found ? " found" : " not found") << endl;
    } else if (command == "TCHECK") {
        tree.load_from_file(filename);
        bool complete = tree.is_complete_tree();
        cout << "Tree is " << (complete ? "complete." : "not complete or there is no tree.") << endl;
    } else if (command == "TPRINT") {
        tree.load_from_file(filename);
        tree.print();
    } else {
        cerr << "Unknown command: " << command << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: ./dbms --file <file.data> --query '<command>'\n";
        return 1;
    }

    Array<string> array;
    SinglyLinkedList<string> singly_list;
    DoublyLinkedList<string> doubly_list;
    Queue<string> queue;
    Stack<string> stack;
    HashTable<size_t, string> hash_table;
    CompleteBinaryTree<int> tree;

    string filename;
    string query;
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "--file") {
            filename = argv[++i];
        } else if (string(argv[i]) == "--query") {
            query = argv[++i];
        }
    }

    // Выполнение запроса
    execute_query(query, array, singly_list, doubly_list, queue, stack, hash_table, tree, filename);

    return 0;
}
