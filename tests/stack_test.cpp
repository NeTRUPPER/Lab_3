#include "stack.h"
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

// Тест конструктора
TEST(StackTest, Constructor) {
    Stack<int> stack(10);
    EXPECT_EQ(stack.get_size(), 0);
}

// Тест метода push и get_size
TEST(StackTest, PushAndSize) {
    Stack<int> stack(5);
    stack.push(10);
    stack.push(20);
    EXPECT_EQ(stack.get_size(), 2);
}

// Тест метода pop
TEST(StackTest, Pop) {
    Stack<int> stack(5);
    stack.push(10);
    stack.push(20);
    stack.pop();
    EXPECT_EQ(stack.get_size(), 1);
    EXPECT_EQ(stack.peek(), 10);
}

// Тест выброса исключения при pop на пустом стеке
TEST(StackTest, PopEmpty) {
    Stack<int> stack(5);
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

// Тест метода peek
TEST(StackTest, Peek) {
    Stack<int> stack(5);
    stack.push(10);
    EXPECT_EQ(stack.peek(), 10);
}

// Тест выброса исключения при peek на пустом стеке
TEST(StackTest, PeekEmpty) {
    Stack<int> stack(5);
    EXPECT_THROW(stack.peek(), std::out_of_range);
}

// Тест загрузки из файла
TEST(StackTest, LoadFromFile) {
    Stack<int> stack(10);
    std::ofstream file("stack_test.data");
    file << "10 20 30";
    file.close();

    stack.load_from_file("stack_test.data");
    EXPECT_EQ(stack.get_size(), 3);
    EXPECT_EQ(stack.peek(), 10);
}

// Тест сохранения в файл
TEST(StackTest, SaveToFile) {
    Stack<int> stack(10);
    stack.push(10);
    stack.push(20);
    stack.save_to_file("stack.data");

    std::ifstream file("stack.data");
    std::string content;
    if (file.is_open()) {
        std::getline(file, content); // Считываем всю строку из файла
        file.close();
    }
    EXPECT_EQ(content, "20 10 ");
}
// Тест переполнения стека
TEST(StackTest, Overflow) {
    Stack<int> stack(2);
    stack.push(10);
    stack.push(20);
    testing::internal::CaptureStderr();
    stack.push(30);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Stack is full, cannot push new value: 30\n");
}

TEST(StackTest, TestPrint) {
    // Создаем очередь
    Stack<int> stack;

    // Добавляем элементы
    stack.push(10);
    stack.push(20);

    // Перехватываем вывод
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перенаправляем вывод в строковый поток

    stack.print();  // Вызываем метод print()

    // Возвращаем стандартный поток вывода
    std::cout.rdbuf(old);

    // Проверяем, что вывод не пустой
    std::string output = buffer.str();

    // Проверяем, что вывод содержит правильные элементы
    ASSERT_NE(output.find("10"), std::string::npos) << "Output does not contain expected element 10";
    ASSERT_NE(output.find("20"), std::string::npos) << "Output does not contain expected element 20";
}