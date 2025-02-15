#include "stack.h"
#include <benchmark/benchmark.h>

static void BM_StackPush(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        Stack<int> stack(state.range(0));
        for (size_t i = 0; i < capacity; ++i) {
            stack.push(42);
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StackPush)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_StackPop(benchmark::State& state) {
    size_t capacity = state.range(0);
    for (auto _ : state) {
        Stack<int> stack(state.range(0));
        for (int i = 0; i < state.range(0); ++i) {
            stack.push(i);
        }
        for (size_t i = 0; i < capacity; ++i) {
            stack.pop();
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StackPop)->RangeMultiplier(10)->Range(10, 1000)->Complexity();

static void BM_StackPeek(benchmark::State& state) {
    Stack<int> stack(state.range(0));
    stack.push(42);
    for (auto _ : state) {
        benchmark::DoNotOptimize(stack.peek());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StackPeek)->RangeMultiplier(10)->Range(10, 1000)->Complexity();
