#include "hashtable.h"
#include <benchmark/benchmark.h>

// Бенчмарк вставки элементов
static void BM_HashTableInsert(benchmark::State& state) {
    size_t capacity = state.range(0);
    HashTable<int, int> hashTable(1000);
    for (auto _ : state) {
        for (int i = 0; i < capacity; ++i) {
            hashTable.insert(i, i * 10);
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_HashTableInsert)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

// Бенчмарк получения элементов
static void BM_HashTableGet(benchmark::State& state) {
    size_t capacity = state.range(0);
    HashTable<int, int> hashTable(1000);
    for (int i = 0; i < capacity; ++i) {
        hashTable.insert(i, i * 10);
    }

    for (auto _ : state) {
        for (int i = 0; i < capacity; ++i) {
            benchmark::DoNotOptimize(hashTable.get(i));
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_HashTableGet)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

// Бенчмарк удаления элементов
static void BM_HashTableRemove(benchmark::State& state) {
    size_t capacity = state.range(0);
    HashTable<int, int> hashTable(1000);
    for (int i = 0; i < capacity; ++i) {
        hashTable.insert(i, i * 10);
    }

    for (auto _ : state) {
        for (int i = 0; i < capacity; ++i) {
            hashTable.remove(i);
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_HashTableRemove)->RangeMultiplier(10)->Range(10, 1000)->Complexity();