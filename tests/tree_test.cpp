#include "completetree.h"
#include <gtest/gtest.h>

// Тесты для очереди
// Тест для получения размера очереди
TEST(Queue2Test, SizeTest) {
    Queue2<int> queue;
    EXPECT_EQ(queue.get_size(), 0);  // Очередь пуста

    queue.push(10);
    queue.push(20);
    EXPECT_EQ(queue.get_size(), 2);  // Два элемента в очереди

    queue.pop();
    EXPECT_EQ(queue.get_size(), 1);  // Один элемент в очереди

    queue.pop();
    EXPECT_EQ(queue.get_size(), 0);  // Очередь пуста
}

// Тест для получения элемента из пустой очереди
TEST(Queue2Test, FrontOnEmptyQueueTest) {
    Queue2<int> queue;
    EXPECT_THROW(queue.front(), std::out_of_range);  // Очередь пуста, ошибка
}

// Тест для удаления элемента из пустой очереди
TEST(Queue2Test, PopOnEmptyQueueTest) {
    Queue2<int> queue;
    EXPECT_THROW(queue.pop(), std::out_of_range);  // Очередь пуста, ошибка
}

// Тест для последовательного добавления и удаления элементов
TEST(Queue2Test, PushPopSequenceTest) {
    Queue2<int> queue;

    for (int i = 1; i <= 5; ++i) {
        queue.push(i);
        EXPECT_EQ(queue.get_size(), i);  // Проверка размера после каждого добавления
    }

    for (int i = 1; i <= 5; ++i) {
        EXPECT_EQ(queue.front(), i);  // Проверка первого элемента
        queue.pop();
        EXPECT_EQ(queue.get_size(), 5 - i);  // Проверка размера после каждого удаления
    }

    EXPECT_TRUE(queue.is_empty());  // Очередь должна быть пуста
}

TEST(Queue2Test, PushPopTest) {
    Queue2<int> queue;
    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(queue.front(), 10);
    queue.pop();
    EXPECT_EQ(queue.front(), 20);
    queue.pop();
    EXPECT_EQ(queue.front(), 30);
    queue.pop();
    EXPECT_TRUE(queue.is_empty());
}

TEST(Queue2Test, EmptyQueueTest) {
    Queue2<int> queue;
    EXPECT_TRUE(queue.is_empty());
    EXPECT_THROW(queue.pop(), std::out_of_range);
    EXPECT_THROW(queue.front(), std::out_of_range);
}

// Тесты для класса CompleteBinaryTree
TEST(CompleteBinaryTreeTest, AddTest) {
    CompleteBinaryTree<int> tree;
    tree.add(1);
    tree.add(2);
    tree.add(3);

    EXPECT_EQ(tree.get_size(), 3);
    EXPECT_TRUE(tree.find(1));
    EXPECT_TRUE(tree.find(2));
    EXPECT_TRUE(tree.find(3));
    EXPECT_FALSE(tree.find(4));
}

TEST(CompleteBinaryTreeTest, RemoveTest) {
    CompleteBinaryTree<int> tree;
    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.remove(2);

    EXPECT_EQ(tree.get_size(), 2);
    EXPECT_FALSE(tree.find(2));
    EXPECT_TRUE(tree.find(1));
    EXPECT_TRUE(tree.find(3));
}

TEST(CompleteBinaryTreeTest, IsCompleteTreeTest) {
    CompleteBinaryTree<int> tree;
    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.add(5);
    tree.add(6);
    tree.add(7);
    tree.add(0);
    tree.add(9);

    EXPECT_FALSE(tree.is_complete_tree());
}

TEST(CompleteBinaryTreeTest, RemoveSingleNodeTest) {
    CompleteBinaryTree<int> tree;
    tree.add(1);
    tree.remove(1);

    EXPECT_EQ(tree.get_size(), 0);
    EXPECT_FALSE(tree.find(1));
}

TEST(CompleteBinaryTreeTest, RemoveNonExistentNodeTest) {
    CompleteBinaryTree<int> tree;
    tree.add(1);
    tree.add(2);

    EXPECT_THROW(tree.remove(3), std::runtime_error);
}

TEST(CompleteBinaryTreeTest, LoadSaveTest) {
    CompleteBinaryTree<int> tree;
    tree.add(1);
    tree.add(2);
    tree.add(3);

    tree.save_to_file("tree.txt");

    CompleteBinaryTree<int> new_tree;
    new_tree.load_from_file("tree.txt");

    EXPECT_EQ(new_tree.get_size(), 3);
    EXPECT_TRUE(new_tree.find(1));
    EXPECT_TRUE(new_tree.find(2));
    EXPECT_TRUE(new_tree.find(3));
}

TEST(CompleteBinaryTreeTest, LoadEmptyFileTest) {
    CompleteBinaryTree<int> tree;

    EXPECT_THROW(tree.load_from_file("empty_tree.txt"), std::runtime_error);
}

TEST(CompleteBinaryTreeTest, IsCompleteTreeWithOneNodeTest) {
    CompleteBinaryTree<int> tree;
    tree.add(1);

    EXPECT_TRUE(tree.is_complete_tree());
}

TEST(CompleteBinaryTreeTest, AddToCompleteTreeTest) {
    CompleteBinaryTree<int> tree;
    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.add(5);
    tree.add(6);

    EXPECT_TRUE(tree.is_complete_tree());
}

TEST(CompleteBinaryTreeTest, FindNonExistentNodeTest) {
    CompleteBinaryTree<int> tree;
    tree.add(1);
    tree.add(2);

    EXPECT_FALSE(tree.find(3));  // Элемент не найден
}

TEST(CompleteBinaryTreeTest, AddMultipleElementsTest) {
    CompleteBinaryTree<int> tree;
    for (int i = 1; i <= 100; ++i) {
        tree.add(i);
    }

    EXPECT_EQ(tree.get_size(), 100);
    EXPECT_TRUE(tree.find(50));  // Проверяем, что элемент найден
}

// Тест для функции print() дерева, проверяющий отсутствие ошибок при выводе
TEST(CompleteBinaryTreeTest, TestPrint) {
    CompleteBinaryTree<int> tree;

    // Добавление элементов в дерево
    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.add(5);

    // Создаем строковый поток, чтобы перехватить вывод в консоль
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перенаправляем вывод в строковый поток

    // Проверяем, что при вызове print() не возникает исключений
    try {
        tree.print();  // Предполагаем, что print() - это функция вывода дерева
    } catch (const std::exception& e) {
        FAIL() << "Function print() threw an exception: " << e.what();
    } catch (...) {
        FAIL() << "Function print() threw an unknown exception";
    }

    // Возвращаем стандартный поток вывода
    std::cout.rdbuf(old);

    // Проверяем, что в процессе вызова print() не возникло ошибок, например, вывод должен быть корректным
    ASSERT_FALSE(buffer.str().empty()) << "The print function did not produce any output.";
}
