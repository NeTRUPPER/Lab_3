#include "completetree.h"
#include <benchmark/benchmark.h>

// Бенчмарки для класса CompleteBinaryTree
static void BM_CompleteBinaryTreeAdd(benchmark::State& state) {
    size_t capacity = state.range(0);
    CompleteBinaryTree<int> tree;
    for (auto _ : state) {
        for (int i = 0; i < capacity; ++i) {
            tree.add(i);
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_CompleteBinaryTreeAdd)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_CompleteBinaryTreeFind(benchmark::State& state) {
    size_t capacity = state.range(0);
    CompleteBinaryTree<int> tree;
    for (int i = 0; i < capacity; ++i) {
        tree.add(i);
    }

    for (auto _ : state) {
        for (int i = 0; i < capacity; ++i) {
            benchmark::DoNotOptimize(tree.find(i));
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_CompleteBinaryTreeFind)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_CompleteBinaryTreeRemove(benchmark::State& state) {
    size_t capacity = state.range(0);
    CompleteBinaryTree<int> tree;
    for (int i = 0; i < capacity; ++i) {
        tree.add(i);
    }

    for (auto _ : state) {
        for (int i = 0; i < capacity; ++i) {
            if (tree.get_size() > 0) {
                tree.remove(i);
            }
        }
    }
    state.SetComplexityN(capacity);
}
BENCHMARK(BM_CompleteBinaryTreeRemove)->RangeMultiplier(10)->Range(10, 1000)->Complexity();