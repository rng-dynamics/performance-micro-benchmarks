#include <cstring>
#include <emmintrin.h>
#include <immintrin.h>
#include <memory>
#include <random>

#include <benchmark/benchmark.h>

#include "utility.hpp"

namespace performance_micro_benchmarks::memory_access {

void simple_memory_access(benchmark::State &state) {
  auto pd = std::make_unique<int>();
  volatile int *p1 = pd.get();
  for (auto _ : state) {
    REPEAT32(benchmark::DoNotOptimize(*p1);)
  }
  state.SetItemsProcessed(32 * state.iterations());
}

template <typename Word> void cache_sequential_read(benchmark::State &state) {
  const int64_t size = state.range(0);

  void *memory = nullptr;
  // posix_memalign allocates memory.
  if (::posix_memalign(&memory, 64, size) != 0) {
    abort();
  }
  Word *const p0 = static_cast<Word *>(memory);
  void *const end = static_cast<char *>(memory) + size;
  Word *p1 = static_cast<Word *>(end);
  { // check correctness
    if (size % 256 != 0) {
      abort();
    }
    if (size % sizeof(Word) != 0) {
      abort();
    }
    if ((p1 - p0) != (size / sizeof(Word))) {
      abort();
    }
  }

  for (auto _ : state) {
    for (volatile Word *ptr = p0; ptr != p1;) {
      REPEAT32(benchmark::DoNotOptimize(*ptr); ++ptr;)
    }
    benchmark::ClobberMemory();
  }

  ::free(memory);
  state.SetBytesProcessed(size * state.iterations());
  state.SetItemsProcessed((p1 - p0) * state.iterations());
}

template <typename Word> void cache_sequential_write(benchmark::State &state) {
  const int64_t size = state.range(0);

  void *memory = nullptr;
  // posix_memalign allocates memory.
  if (::posix_memalign(&memory, 64, size) != 0) {
    abort();
  }
  Word *const p0 = static_cast<Word *>(memory);
  void *const end = static_cast<char *>(memory) + size;
  Word *p1 = static_cast<Word *>(end);
  { // check correctness
    if (size % 256 != 0) {
      abort();
    }
    if (size % sizeof(Word) != 0) {
      abort();
    }
    if ((p1 - p0) != (size / sizeof(Word))) {
      abort();
    }
  }
  auto fill = Word{};

  for (auto _ : state) {
    for (volatile Word *ptr = p0; ptr != p1;) {
      REPEAT32(benchmark::DoNotOptimize(*ptr = fill); ++ptr;)
    }
    benchmark::ClobberMemory();
  }

  ::free(memory);
  state.SetBytesProcessed(size * state.iterations());
  state.SetItemsProcessed((p1 - p0) * state.iterations());
}

template <typename Word> void cache_random_read(benchmark::State &state) {
  const int64_t size = state.range(0);

  void *memory = nullptr;
  // posix_memalign allocates memory.
  if (::posix_memalign(&memory, 64, size) != 0) {
    abort();
  }
  Word *const p0 = static_cast<Word *>(memory);
  void *const end = static_cast<char *>(memory) + size;
  Word *p1 = static_cast<Word *>(end);
  { // check correctness
    if (size % 256 != 0) {
      abort();
    }
    if (size % sizeof(Word) != 0) {
      abort();
    }
    if ((p1 - p0) != (size / sizeof(Word))) {
      abort();
    }
  }
  const int64_t NN = size / sizeof(Word);
  auto v_index = std::vector<int>(NN, 0);
  for (int ii = 0; ii < NN; ++ii) {
    v_index[ii] = ii;
  }
  auto rd = std::random_device{};
  auto mt = std::mt19937{rd()};
  std::shuffle(v_index.begin(), v_index.end(), mt);
  int *const index = v_index.data();
  int *const i1 = index + NN;

  for (auto _ : state) {
    for (const int *ind = index; ind < i1;) {
      REPEAT32(benchmark::DoNotOptimize(p0[*ind]); ++ind;)
    }
    benchmark::ClobberMemory();
  }

  ::free(memory);
  state.SetBytesProcessed(size * state.iterations());
  state.SetItemsProcessed((p1 - p0) * state.iterations());
}

template <typename Word> void cache_random_write(benchmark::State &state) {
  const int64_t size = state.range(0);

  void *memory = nullptr;
  // posix_memalign allocates memory.
  if (::posix_memalign(&memory, 64, size) != 0) {
    abort();
  }
  Word *const p0 = static_cast<Word *>(memory);
  void *const end = static_cast<char *>(memory) + size;
  Word *p1 = static_cast<Word *>(end);
  { // check correctness
    if (size % 256 != 0) {
      abort();
    }
    if (size % sizeof(Word) != 0) {
      abort();
    }
    if ((p1 - p0) != (size / sizeof(Word))) {
      abort();
    }
  }
  const int64_t NN = size / sizeof(Word);
  auto v_index = std::vector<int>(NN);
  for (int ii = 0; ii < NN; ++ii) {
    v_index[ii] = ii;
  }
  auto rd = std::random_device{};
  auto mt = std::mt19937{rd()};
  std::shuffle(v_index.begin(), v_index.end(), mt);
  int *const index = v_index.data();
  int *const i1 = index + NN;

  auto fill = Word{};
  ::memset(&fill, 0x0f, sizeof(fill));

  for (auto _ : state) {
    for (const int *ind = index; ind < i1;) {
      REPEAT32(benchmark::DoNotOptimize(*(p0 + *ind) = fill); ++ind;)
    }
    benchmark::ClobberMemory();
  }

  ::free(memory);
  state.SetBytesProcessed(size * state.iterations());
  state.SetItemsProcessed((p1 - p0) * state.iterations());
}

template <typename Word>
void cache_sequential_read__experimental(benchmark::State &state) {
  const int64_t size = state.range(0);
  void *memory = nullptr;
  { // check preconditions
    if (::posix_memalign(&memory, 64, size) != 0) {
      abort();
    }
    if (size % 32 != 0) {
      abort();
    }
    if (size % sizeof(Word) != 0) {
      abort();
    }
  }
  volatile Word *const p0 = static_cast<Word *>(memory);
  void *const end = static_cast<char *>(memory) + size;
  Word *p1 = static_cast<Word *>(end);

  auto sink1 = Word{};
  ::memset(&sink1, 0xab, sizeof(sink1));
  Word sink = sink1;

  const int64_t NN = size / sizeof(Word);
  auto v_index = std::vector<int>(NN);
  for (int ii = 0; ii < NN; ++ii) {
    v_index[ii] = ii;
  }
  int *const index = v_index.data();
  int *const i1 = index + NN;

  for (auto _ : state) {
    for (volatile Word *ptr = p0; ptr != p1;) {
      REPEAT32(benchmark::DoNotOptimize(*ptr++);)
    }
    // for (const int* idx = index; idx < i1; ) {
    //     REPEAT32(sink = *(p0 + *idx++);)
    // }
    // Word another_sink;
    // for (volatile Word *ptr = p0; ptr != p1;) {
    //   REPEAT32(another_sink = *ptr++;
    //   benchmark::DoNotOptimize(another_sink);)
    // }
    benchmark::ClobberMemory();
  }
  benchmark::DoNotOptimize(sink);

  state.SetBytesProcessed(size * state.iterations());
  state.SetItemsProcessed((p1 - p0) * state.iterations());
}

} // namespace performance_micro_benchmarks::memory_access

// NOLINTNEXTLINE
BENCHMARK(performance_micro_benchmarks::memory_access::simple_memory_access);

// BENCHMARK_TEMPLATE does not work with names containing a namespace.
template <typename T>
constexpr auto cache_sequential_read =
    performance_micro_benchmarks::memory_access::cache_sequential_read<T>;
template <typename T>
constexpr auto cache_sequential_write =
    performance_micro_benchmarks::memory_access::cache_sequential_write<T>;
template <typename T>
constexpr auto cache_random_read =
    performance_micro_benchmarks::memory_access::cache_random_read<T>;
template <typename T>
constexpr auto cache_random_write =
    performance_micro_benchmarks::memory_access::cache_random_write<T>;

// // NOLINTNEXTLINE
// BENCHMARK_TEMPLATE1(cache_sequential_read, char)
//     ->RangeMultiplier(2)->Range(1U << 10U, 1U << 30U);
// NOLINTNEXTLINE
// BENCHMARK_TEMPLATE1(cache_sequential_read, unsigned int)
//     ->RangeMultiplier(2)->Range(1U << 10U, 1U << 30U);
// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_sequential_read, unsigned long)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_sequential_read, __m128i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_sequential_read, __m256i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_sequential_write, unsigned long)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_sequential_write, __m128i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_sequential_write, __m256i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_random_read, unsigned long)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_random_read, __m128i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_random_read, __m256i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_random_write, unsigned long)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_random_write, __m128i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_TEMPLATE1(cache_random_write, __m256i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

// NOLINTNEXTLINE
BENCHMARK_MAIN();
