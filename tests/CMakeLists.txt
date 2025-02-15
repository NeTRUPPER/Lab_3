# Укажите минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(BenchmarksAndTests)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Укажите путь к заголовочным файлам
include_directories(include)

# Найдите библиотеку Google Benchmark
find_package(benchmark REQUIRED)

# Найдите библиотеку Google Test
find_package(GTest REQUIRED)

# Добавьте исполняемый файл для бенчмарков
add_executable(runBenchmarks
    array_benchmark.cpp
    stack_benchmark.cpp
    queue_benchmark.cpp
    list_benchmark.cpp
    doublelist_benchmark.cpp
    hashtable_benchmark.cpp
    tree_benchmark.cpp
)

# Свяжите исполняемый файл с библиотекой Benchmark
target_link_libraries(runBenchmarks benchmark::benchmark)

# Укажите дополнительные флаги компилятора для бенчмарков
target_compile_options(runBenchmarks PRIVATE -O3)

# Добавьте исполняемый файл для тестов
add_executable(runTests
    array_test.cpp
    stack_test.cpp
    queue_test.cpp
    list_test.cpp
    doublelist_test.cpp
    hashtable_test.cpp
    tree_test.cpp
)

# Свяжите исполняемый файл с библиотеками GTest и pthread
target_link_libraries(runTests PRIVATE GTest::GTest GTest::Main pthread)

# Добавьте тестовый набор для CTest
enable_testing()
add_test(NAME runTests COMMAND runTests)
