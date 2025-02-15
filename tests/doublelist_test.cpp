#include "twolist.h"
#include <gtest/gtest.h>

// Тест конструктора
TEST(DoublyLinkedListTest, Constructor) {
    DoublyLinkedList<int> list;
    EXPECT_EQ(list.get_size(), 0);
}

// Тест метода push_front
TEST(DoublyLinkedListTest, PushFront) {
    DoublyLinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);

    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.find(30)->data, 30);
    EXPECT_EQ(list.find(20)->data, 20);
    EXPECT_EQ(list.find(10)->data, 10);
}

// Тест метода push_back
TEST(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.find(10)->data, 10);
    EXPECT_EQ(list.find(20)->data, 20);
    EXPECT_EQ(list.find(30)->data, 30);
}

// Тест метода pop_front
TEST(DoublyLinkedListTest, PopFront) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.pop_front();
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.find(10), nullptr);
    EXPECT_EQ(list.find(20)->data, 20);
}

// Тест метода pop_back
TEST(DoublyLinkedListTest, PopBack) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.pop_back();
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.find(30), nullptr);
    EXPECT_EQ(list.find(20)->data, 20);
}

// Тест метода remove
TEST(DoublyLinkedListTest, Remove) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.remove(20);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.find(20), nullptr);
    EXPECT_EQ(list.find(10)->data, 10);
    EXPECT_EQ(list.find(30)->data, 30);
}

// Тест метода find
TEST(DoublyLinkedListTest, Find) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    auto node = list.find(20);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->data, 20);

    EXPECT_EQ(list.find(40), nullptr);
}

// Тест записи и чтения из файла
TEST(DoublyLinkedListTest, SaveLoad) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.save_to_file("test_file.txt");

    DoublyLinkedList<int> new_list;
    new_list.load_from_file("test_file.txt");

    EXPECT_EQ(new_list.get_size(), 3);
    EXPECT_EQ(new_list.find(10)->data, 10);
    EXPECT_EQ(new_list.find(20)->data, 20);
    EXPECT_EQ(new_list.find(30)->data, 30);
}

TEST(DoublyLinkedListTest, TestPrint) {
    // Создаем список
    DoublyLinkedList<int> list;

    // Добавляем элементы
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    // Перехватываем вывод
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перенаправляем вывод в строковый поток

    // Печатаем содержимое списка
    try {
        list.print();  // Вызываем метод print()
    } catch (const std::exception& e) {
        FAIL() << "Function print() threw an exception: " << e.what();
    } catch (...) {
        FAIL() << "Function print() threw an unknown exception";
    }

    // Возвращаем стандартный поток вывода
    std::cout.rdbuf(old);

    // Проверяем, что вывод не пустой
    std::string output = buffer.str();
    ASSERT_FALSE(output.empty()) << "The print function did not produce any output.";

    // Проверяем, что вывод содержит правильные элементы
    ASSERT_NE(output.find("10"), std::string::npos) << "Output does not contain expected element 10";
    ASSERT_NE(output.find("20"), std::string::npos) << "Output does not contain expected element 20";
    ASSERT_NE(output.find("30"), std::string::npos) << "Output does not contain expected element 30";
    ASSERT_NE(output.find("40"), std::string::npos) << "Output does not contain expected element 40";
}
