#include <algorithm>
#include <cstring>
#include <emmintrin.h>
#include <immintrin.h>
#include <memory>
#include <random>

#include <benchmark/benchmark.h>

#include <performance-micro-benchmarks/support-library/utility.hpp>

namespace performance_micro_benchmarks::memory_access {

constexpr std::size_t alignment = 1 << 15;

void simple_memory_access(benchmark::State &state) {
  if (auto success = support_library::utility::SetThreadAffinityToCore(0);
      !success) {
    abort();
  }

  auto pd = std::make_unique<int>();
  volatile int *p1 = pd.get();
  for (auto _ : state) {
    REPEAT32(benchmark::DoNotOptimize(*p1);)
  }
  state.SetItemsProcessed(32 * state.iterations());
}

template <typename Word> void cache_sequential_read(benchmark::State &state) {
  const int64_t size = state.range(0);

  if (auto success = support_library::utility::SetThreadAffinityToCore(0);
      !success) {
    abort();
  }

  void *memory = nullptr;
  // posix_memalign allocates memory.
  if (::posix_memalign(&memory, alignment, size) != 0) {
    abort();
  }
  Word *const p0 = static_cast<Word *>(memory);
  void *const end = static_cast<char *>(memory) + size;
  Word *p1 = static_cast<Word *>(end);
  const int64_t NN = size / sizeof(Word);
  { // check correctness
    if (size % 256 != 0) {
      abort();
    }
    if (size % sizeof(Word) != 0) {
      abort();
    }
    if ((p1 - p0) != NN) {
      abort();
    }
    if (NN % 32 != 0) {
      abort();
    }
  }

  Word ww = {};
  for (auto _ : state) {
    benchmark::ClobberMemory();
    for (Word *ptr = p0; ptr != p1;) {
      REPEAT32(                         //
          ww = *ptr;                    //
          benchmark::DoNotOptimize(ww); //
          ++ptr;                        //
      )
    }
  }

  ::free(memory);
  state.SetBytesProcessed(size * state.iterations());
  state.SetItemsProcessed((p1 - p0) * state.iterations());
}

template <typename Word> void cache_sequential_write(benchmark::State &state) {
  const int64_t size = state.range(0);

  if (auto success = support_library::utility::SetThreadAffinityToCore(0);
      !success) {
    abort();
  }

  void *memory = nullptr;
  // posix_memalign allocates memory.
  if (::posix_memalign(&memory, alignment, size) != 0) {
    abort();
  }
  Word *const p0 = static_cast<Word *>(memory);
  void *const end = static_cast<char *>(memory) + size;
  Word *p1 = static_cast<Word *>(end);
  const int64_t NN = size / sizeof(Word);
  { // check correctness
    if (size % 256 != 0) {
      abort();
    }
    if (size % sizeof(Word) != 0) {
      abort();
    }
    if ((p1 - p0) != NN) {
      abort();
    }
    if (NN % 32 != 0) {
      abort();
    }
  }
  auto fill = Word{};

  for (auto _ : state) {
    benchmark::ClobberMemory();
    for (volatile Word *ptr = p0; ptr != p1;) {
      REPEAT32(                               //
              *ptr = fill;                    //
              benchmark::DoNotOptimize(*ptr); //
              ++ptr;                          //
      )
    }
  }

  ::free(memory);
  state.SetBytesProcessed(size * state.iterations());
  state.SetItemsProcessed((p1 - p0) * state.iterations());
}

template <typename Word> void cache_random_read(benchmark::State &state) {
  const int64_t size = state.range(0);

  if (auto success = support_library::utility::SetThreadAffinityToCore(0);
      !success) {
    abort();
  }

  void *memory = nullptr;
  // posix_memalign allocates memory.
  if (::posix_memalign(&memory, alignment, size) != 0) {
    abort();
  }
  Word *const p0 = static_cast<Word *>(memory);
  void *const end = static_cast<char *>(memory) + size;
  Word *p1 = static_cast<Word *>(end);
  const int64_t NN = size / sizeof(Word);
  { // check correctness
    if (size % 256 != 0) {
      abort();
    }
    if (size % sizeof(Word) != 0) {
      abort();
    }
    if ((p1 - p0) != NN) {
      abort();
    }
    if (NN % 32 != 0) {
      abort();
    }
  }
  auto v_index = std::vector<int>{};
  v_index.reserve(NN);
  for (int ii = 0; ii < NN; ++ii) {
    v_index.push_back(ii);
  }
  auto rd = std::random_device{};
  auto minstd_rand = std::minstd_rand{rd()};
  std::shuffle(v_index.begin(), v_index.end(), minstd_rand);

  int start_aidx = v_index.front();

  support_library::utility::FillDataArray(p0, NN, v_index);

  Word next_idx = *(p0 + start_aidx);
  int idx_as_int = 0;

  for (auto _ : state) {
    benchmark::ClobberMemory();
    for (int lidx = 0; lidx < NN;) {
      REPEAT32(                                      //
          idx_as_int = READ_INT_FROM_WORD(next_idx); //
          next_idx = *(p0 + idx_as_int);             //
          benchmark::DoNotOptimize(next_idx);        //
          ++lidx;)
    }
  }

  ::free(memory);
  state.SetBytesProcessed(size * state.iterations());
  state.SetItemsProcessed((p1 - p0) * state.iterations());
}

} // namespace performance_micro_benchmarks::memory_access

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

BENCHMARK_TEMPLATE1(cache_sequential_read, unsigned long)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

BENCHMARK_TEMPLATE1(cache_sequential_read, __m128i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

BENCHMARK_TEMPLATE1(cache_sequential_read, __m256i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

BENCHMARK_TEMPLATE1(cache_sequential_write, unsigned long)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

BENCHMARK_TEMPLATE1(cache_sequential_write, __m128i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

BENCHMARK_TEMPLATE1(cache_sequential_write, __m256i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

BENCHMARK_TEMPLATE1(cache_random_read, unsigned long)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

BENCHMARK_TEMPLATE1(cache_random_read, __m128i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

BENCHMARK_TEMPLATE1(cache_random_read, __m256i)
    ->RangeMultiplier(2)
    ->Range(1U << 10U, 1U << 30U);

BENCHMARK_MAIN();
