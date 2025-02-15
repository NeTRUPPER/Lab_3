#include <gtest/gtest.h>
#include <stdexcept>
#include "array.h"

// Проверка переполнения при push_back
TEST(ArrayTest, PushBackThrowsOnOverflow) {
    Array<int> arr(2);
    arr.push_back(1);
    arr.push_back(2);
    EXPECT_THROW(arr.push_back(3), std::overflow_error);
}

// Проверка insert_at
TEST(ArrayTest, InsertAtWorks) {
    Array<int> arr(5);
    arr.push_back(1);
    arr.push_back(3);
    arr.insert_at(1, 2);
    EXPECT_EQ(arr.get_at(1), 2);
    EXPECT_EQ(arr.size(), 3);
}

// Проверка insert_at на переполнение
TEST(ArrayTest, InsertAtThrowsOnOverflow) {
    Array<int> arr(2);
    arr.push_back(1);
    arr.push_back(2);
    EXPECT_THROW(arr.insert_at(1, 3), std::out_of_range);
}

// Проверка удаления элемента
TEST(ArrayTest, RemoveAtWorks) {
    Array<int> arr(5);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.remove_at(1);
    EXPECT_EQ(arr.get_at(1), 3);
    EXPECT_EQ(arr.size(), 2);
}

// Проверка удаления с недопустимым индексом
TEST(ArrayTest, RemoveAtThrowsOnInvalidIndex) {
    Array<int> arr(5);
    EXPECT_THROW(arr.remove_at(0), std::out_of_range);
}

// Проверка замены элемента
TEST(ArrayTest, ReplaceAtWorks) {
    Array<int> arr(5);
    arr.push_back(1);
    arr.replace_at(0, 2);
    EXPECT_EQ(arr.get_at(0), 2);
}

// Проверка получения элемента
TEST(ArrayTest, GetAtWorks) {
    Array<int> arr(5);
    arr.push_back(1);
    EXPECT_EQ(arr.get_at(0), 1);
}

// Проверка загрузки из файла
TEST(ArrayTest, LoadFromFileWorks) {
    Array<int> arr(5);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.save_to_text_file("test.txt");


    arr.load_from_text_file("test.txt");
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr.get_at(0), 1);
    EXPECT_EQ(arr.get_at(1), 2);
    EXPECT_EQ(arr.get_at(2), 3);
}

// Проверка сохранения в файл
TEST(ArrayTest, SaveToFileWorks) {
    Array<int> arr(5);
    arr.push_back(1);
    arr.save_to_text_file("test_output.txt");

    std::ifstream file("test_output.txt");
    std::string content;
    file >> content;
    EXPECT_EQ(content, "1");
}
