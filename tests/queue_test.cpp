#include "queue.h"
#include <fstream>
#include <sstream>
#include <gtest/gtest.h>
#include <stdexcept>

TEST(QueueTest, PushAndFrontValue) {
    Queue<int> q;
    q.push(10);
    EXPECT_EQ(q.front_value(), 10);
    q.push(20);
    EXPECT_EQ(q.front_value(), 10);
}

TEST(QueueTest, Pop) {
    Queue<int> q;
    q.push(10);
    q.push(20);
    q.pop();
    EXPECT_EQ(q.front_value(), 20);
}

TEST(QueueTest, EmptyPop) {
    Queue<int> q;
    EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueTest, FrontValueOnEmpty) {
    Queue<int> q;
    EXPECT_THROW(q.front_value(), std::out_of_range);
}

TEST(QueueTest, GetSize) {
    Queue<int> q;
    EXPECT_EQ(q.get_size(), 0);
    q.push(10);
    EXPECT_EQ(q.get_size(), 1);
    q.push(20);
    EXPECT_EQ(q.get_size(), 2);
    q.pop();
    EXPECT_EQ(q.get_size(), 1);
}

TEST(QueueTest, SaveAndLoadFromFile) {
    Queue<int> q;
    q.push(10);
    q.push(20);
    q.save_to_file("queue.data");

    Queue<int> loadedQueue;
    loadedQueue.load_from_file("queue.data");
    EXPECT_EQ(loadedQueue.get_size(), 2);
    EXPECT_EQ(loadedQueue.front_value(), 10);
    loadedQueue.pop();
    EXPECT_EQ(loadedQueue.front_value(), 20);
}

TEST(QueueTest, TestPrint) {
    // Создаем очередь
    Queue<int> queue;

    // Добавляем элементы
    queue.push(10);
    queue.push(20);

    // Перехватываем вывод
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перенаправляем вывод в строковый поток

    queue.print();  // Вызываем метод print()

    // Возвращаем стандартный поток вывода
    std::cout.rdbuf(old);

    // Проверяем, что вывод не пустой
    std::string output = buffer.str();

    // Проверяем, что вывод содержит правильные элементы
    ASSERT_NE(output.find("10"), std::string::npos) << "Output does not contain expected element 10";
    ASSERT_NE(output.find("20"), std::string::npos) << "Output does not contain expected element 20";
}
