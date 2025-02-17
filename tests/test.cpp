#include "twolist.h"

int main(){
    DoublyLinkedList<int> list;
    list.push_front(20);
    list.push_front(30);
    list.push_front(40);
    list.push_back(20);

    //list.save_to_binary("test_binary.bin");
    list.save_to_file("test_txt.txt");

    cout << endl;

    list.remove(40);
    list.remove(30);
    list.remove(20);
    list.remove(20);

    //list.load_from_binary("test_binary.bin");
    list.load_from_file("test_txt.txt");

    cout << endl;

    list.print();
}