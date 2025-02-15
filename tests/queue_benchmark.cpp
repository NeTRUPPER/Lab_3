#include <benchmark/benchmark.h>
#include "queue.h"

static void BM_QueuePush(benchmark::State& state) {
    Queue<int> queue;
    for (auto _ : state) {
        queue.push(42);
    }
    state.SetComplexityN(state.range(0));
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_QueuePush)->RangeMultiplier(10)->Range(10, 1000)->Complexity();;

static void BM_QueuePop(benchmark::State& state) {
    size_t capacity = state.range(0);
    Queue<int> queue;
    for (auto _ : state) {
        for (int i = 0; i < capacity; ++i) {
            queue.push(i);
        }
        for (int i = 0; i < capacity; ++i) {
            queue.pop();
        }
    }
    state.SetComplexityN(state.range(0));
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_QueuePop)->RangeMultiplier(10)->Range(10, 1000)->Complexity();;

static void BM_QueueLoadFromFile(benchmark::State& state) {
    size_t capacity = state.range(0);
    std::ofstream file("queue_benchmark.data");
    for (int i = 0; i < capacity; ++i) {
        file << i << " ";
    }
    file.close();

    for (auto _ : state) {
        Queue<int> queue;
        queue.load_from_file("queue_benchmark.data");
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_QueueLoadFromFile)->RangeMultiplier(10)->Range(10, 1000)->Complexity();;

static void BM_QueueSaveToFile(benchmark::State& state) {
    size_t capacity = state.range(0);
    Queue<int> queue;
    for (int i = 0; i < capacity; ++i) {
        queue.push(i);
    }

    for (auto _ : state) {
        queue.save_to_file("queue_benchmark_save.data");
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_QueueSaveToFile)->RangeMultiplier(10)->Range(10, 1000)->Complexity();;
