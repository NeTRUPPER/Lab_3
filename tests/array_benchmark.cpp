#include <benchmark/benchmark.h>
#include "array.h"

// Бенчмарк для добавления элементов в конец массива
static void BM_ArrayPushBack(benchmark::State& state) {
    size_t capacity = state.range(0); // Ёмкость массива
    for (auto _ : state) {
        Array<int> arr(capacity); // Инициализация массива с заданной ёмкостью
        for (size_t i = 0; i < capacity; ++i) {
            arr.push_back(42); // Добавление элемента
        }
    }
    state.SetComplexityN(state.range(0)); // Установка сложности
}

// Бенчмарк для вставки элемента по индексу
static void BM_ArrayInsertAt(benchmark::State& state) {
    size_t capacity = state.range(0); // Ёмкость массива
    for (auto _ : state) {
        Array<int> arr(capacity);
        for (size_t i = 0; i < capacity - 1; ++i) {
            arr.push_back(i); // Заполнение массива
        }
        arr.insert_at(capacity / 2, 42); // Вставка в середину
    }
    state.SetComplexityN(state.range(0)); // Установка сложности
}

// Бенчмарк для удаления элемента
static void BM_ArrayRemoveAt(benchmark::State& state) {
    for (auto _ : state) {
        Array<int> arr(state.range(0));
        for (size_t i = 0; i < state.range(0); ++i) {
            arr.push_back(i); // Заполнение массива
        }
            arr.remove_at(state.range(0) / 2); // Удаление элемента из середины
    }
    state.SetComplexityN(state.range(0)); // Установка сложности
}

// Указание диапазона тестируемых размеров массива
BENCHMARK(BM_ArrayPushBack)->RangeMultiplier(10)->Range(10, 1000)->Complexity();
BENCHMARK(BM_ArrayInsertAt)->RangeMultiplier(10)->Range(10, 1000)->Complexity();
BENCHMARK(BM_ArrayRemoveAt)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

BENCHMARK_MAIN();
