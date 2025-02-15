#include "list.h"
#include <benchmark/benchmark.h>

static void BM_SinglyLinkedListPushFront(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        SinglyLinkedList<int> list;
        for (int i = 0; i < capacity; ++i) {
            list.push_front(i);
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_SinglyLinkedListPushFront)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_SinglyLinkedListPushBack(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        SinglyLinkedList<int> list;
        for (int i = 0; i < capacity; ++i) {
            list.push_back(i);
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SinglyLinkedListPushBack)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_SinglyLinkedListFind(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        SinglyLinkedList<int> list;
        for (int i = 0; i < capacity; ++i) {
            list.push_back(i);
        }

        for (int i = 0; i < capacity; ++i) {
            list.find(capacity / 2);
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SinglyLinkedListFind)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_SinglyLinkedListPopFront(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        SinglyLinkedList<int> list;
        for (int i = 0; i < capacity; ++i) {
            list.push_back(i);
        }

        for (int i = 0; i < capacity; ++i) {
            list.pop_front();
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SinglyLinkedListPopFront)->RangeMultiplier(10)->Range(10, 1000)->Complexity();