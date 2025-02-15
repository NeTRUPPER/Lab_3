#include "twolist.h"
#include <benchmark/benchmark.h>

static void BM_DoublyLinkedListPushFront(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        DoublyLinkedList<int> list;
        for (int i = 0; i < capacity; ++i) {
            list.push_front(i);
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_DoublyLinkedListPushFront)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_DoublyLinkedListPushBack(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        DoublyLinkedList<int> list;
        for (int i = 0; i < capacity; ++i) {
            list.push_back(i);
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_DoublyLinkedListPushBack)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_DoublyLinkedListPopFront(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        DoublyLinkedList<int> list;
        for (int i = 0; i < capacity; ++i) {
            list.push_front(i);
        }
        for (int i = 0; i < capacity; ++i) {
            list.pop_front();
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_DoublyLinkedListPopFront)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_DoublyLinkedListPopBack(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        DoublyLinkedList<int> list;
        for (int i = 0; i < capacity; ++i) {
            list.push_back(i);
        }
        for (int i = 0; i < capacity; ++i) {
            list.pop_back();
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_DoublyLinkedListPopBack)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_DoublyLinkedListFind(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        DoublyLinkedList<int> list;
        for (int i = 0; i < capacity; ++i) {
            list.push_back(i);
        }
        for (int i = 0; i < capacity; ++i) {
            auto node = list.find(capacity / 2); // Поиск элемента в середине
            benchmark::DoNotOptimize(node);
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_DoublyLinkedListFind)->RangeMultiplier(10)->Range(10, 1000)->Complexity();
