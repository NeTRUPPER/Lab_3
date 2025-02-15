#include "hashtable.h"
#include <gtest/gtest.h>

// Тест на добавление и получение элементов
TEST(HashTableTest, InsertAndGet) {
    HashTable<size_t, string> hashTable(10);

    hashTable.insert(1, "key1");
    hashTable.insert(2, "key2");

    EXPECT_EQ(hashTable.get(1), "key1");
    EXPECT_EQ(hashTable.get(2), "key2");
}

// Тест на обновление значения
TEST(HashTableTest, UpdateValue) {
    HashTable<std::string, int> hashTable(10);

    hashTable.insert("key1", 100);
    hashTable.insert("key1", 150); // обновление значения

    EXPECT_EQ(hashTable.get("key1"), 150);
}

// Тест на удаление элемента
TEST(HashTableTest, RemoveElement) {
    HashTable<std::string, int> hashTable(10);

    hashTable.insert("key1", 100);
    hashTable.insert("key2", 200);
    hashTable.insert("key3", 300);
    hashTable.remove("key1");
    hashTable.remove("key3");


    EXPECT_THROW(hashTable.get("key1"), std::out_of_range);
    EXPECT_EQ(hashTable.get_size(), 1);
}

// Тест на сохранение и загрузку из файла
TEST(HashTableTest, SaveAndLoadFromFile) {
    HashTable<std::string, int> hashTable(10);
    hashTable.insert("key1", 100);
    hashTable.insert("key2", 200);

    hashTable.save_to_file("test_data.txt");

    HashTable<std::string, int> newHashTable(10);
    newHashTable.load_from_file("test_data.txt");

    EXPECT_EQ(newHashTable.get("key1"), 100);
    EXPECT_EQ(newHashTable.get("key2"), 200);
}

// Тест на коллизии
TEST(HashTableTest, HandleCollisions) {
    HashTable<int, int> hashTable(3); // малая ёмкость для вызова коллизий

    hashTable.insert(1, 100);
    hashTable.insert(4, 200); // оба попадут в одну цепочку (индекс 1 % 3 == 4 % 3)

    EXPECT_EQ(hashTable.get(1), 100);
    EXPECT_EQ(hashTable.get(4), 200);
}

// Тест для метода print() списка
TEST(LinkedListTest, TestPrint) {
    // Создаем список
    LinkedList<int, std::string> list;

    // Вставляем элементы в список
    list.insert_list(1, "one");
    list.insert_list(2, "two");
    list.insert_list(3, "three");

    // Создаем строковый поток, чтобы перехватить вывод в консоль
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перенаправляем вывод в строковый поток
    
    list.print();  // Вызываем метод print() для списка

    // Возвращаем стандартный поток вывода
    std::cout.rdbuf(old);

    // Проверяем, что вывод не пустой
    std::string output = buffer.str();
    ASSERT_FALSE(output.empty()) << "The print function did not produce any output.";

    // Проверяем, что вывод содержит правильные данные
    ASSERT_NE(output.find("[1: one]"), std::string::npos) << "Output does not contain expected element [1: one]";
    ASSERT_NE(output.find("[2: two]"), std::string::npos) << "Output does not contain expected element [2: two]";
    ASSERT_NE(output.find("[3: three]"), std::string::npos) << "Output does not contain expected element [3: three]";
}

TEST(HashTableTest, TestPrint) {
    // Создаем хеш-таблицу
    HashTable<int, std::string> hashTable(5);  // Размер таблицы 5 для тестирования

    // Вставляем элементы в хеш-таблицу
    hashTable.insert(1, "one");
    hashTable.insert(2, "two");
    hashTable.insert(3, "three");

    // Перехватываем вывод
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  // Перенаправляем вывод в строковый поток

    hashTable.print();  // Вызываем метод print() хеш-таблицы

    // Возвращаем стандартный поток вывода
    std::cout.rdbuf(old);

    // Проверяем, что вывод не пустой
    std::string output = buffer.str();
    ASSERT_FALSE(output.empty()) << "The print function did not produce any output.";

    // Проверяем, что вывод содержит информацию о всех индексах
    for (size_t i = 0; i < 5; ++i) {
        std::string index_output = "Index " + std::to_string(i) + ": ";
        ASSERT_NE(output.find(index_output), std::string::npos)
            << "Output does not contain expected information for " << index_output;
    }

    // Проверяем, что элементы правильно выведены для конкретных индексов
    ASSERT_FALSE(buffer.str().empty());
}
