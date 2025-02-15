#include "list.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Тесты для метода push_front
TEST(SinglyLinkedListTest, PushFront) {
    SinglyLinkedList<int> list;
    list.push_front(10);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.find(10)->data, 10);

    list.push_front(20);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.find(20)->data, 20);
    EXPECT_EQ(list.find(10)->data, 10);
}

// Тесты для метода push_back
TEST(SinglyLinkedListTest, PushBack) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.find(10)->data, 10);

    list.push_back(20);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.find(20)->data, 20);
}

// Тесты для метода pop_front
TEST(SinglyLinkedListTest, PopFront) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_front();
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.find(20)->data, 20);

    list.pop_front();
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_EQ(list.find(10), nullptr);

    EXPECT_THROW(list.pop_front(), std::out_of_range);
}

// Тесты для метода pop_back
TEST(SinglyLinkedListTest, PopBack) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.find(10)->data, 10);

    list.pop_back();
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_EQ(list.find(10), nullptr);

    EXPECT_THROW(list.pop_back(), std::out_of_range);
}

// Тесты для метода remove
TEST(SinglyLinkedListTest, Remove) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.remove(20);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.find(20), nullptr);
    EXPECT_NE(list.find(10), nullptr);
    EXPECT_NE(list.find(30), nullptr);

    list.remove(10);
    EXPECT_EQ(list.get_size(), 1);
    list.remove(30);
    EXPECT_EQ(list.get_size(), 0);

    list.remove(40); // Удаление несуществующего элемента
    EXPECT_EQ(list.get_size(), 0);
}

// Тесты для метода find
TEST(SinglyLinkedListTest, Find) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    EXPECT_NE(list.find(10), nullptr);
    EXPECT_NE(list.find(20), nullptr);
    EXPECT_NE(list.find(30), nullptr);
    EXPECT_EQ(list.find(40), nullptr);
}

// Тесты для метода load_from_file и save_to_file
TEST(SinglyLinkedListTest, SaveAndLoadFromFile) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.save_to_file("list.data");

    SinglyLinkedList<int> loadedList;
    loadedList.load_from_file("list.data");

    EXPECT_EQ(loadedList.get_size(), 2);
    EXPECT_NE(loadedList.find(10), nullptr);
    EXPECT_NE(loadedList.find(20), nullptr);
}

// Тесты для метода get_size
TEST(SinglyLinkedListTest, GetSize) {
    SinglyLinkedList<int> list;
    EXPECT_EQ(list.get_size(), 0);

    list.push_back(10);
    EXPECT_EQ(list.get_size(), 1);

    list.push_back(20);
    EXPECT_EQ(list.get_size(), 2);

    list.pop_front();
    EXPECT_EQ(list.get_size(), 1);

    list.pop_back();
    EXPECT_EQ(list.get_size(), 0);
}

// Тесты для метода print
TEST(SinglyLinkedListTest, Print) {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);

    // Визуальный тест (нужно проверить вывод на консоль вручную)
    list.print();
}
