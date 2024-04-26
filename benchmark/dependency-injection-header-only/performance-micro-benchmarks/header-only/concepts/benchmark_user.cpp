#include <benchmark/benchmark.h>

#include <performance-micro-benchmarks/header-only/concepts/user.hpp>

#include "performance-micro-benchmarks/utility.hpp"

namespace performance_micro_benchmarks::header_only::concepts {

namespace {

class FnInterfaceImpl {
public:
  int fn() {
    static volatile int value = 42;
    return value;
  }
};

} // namespace

class BenchmarkPerformanceBenchmarksHeaderOnlyConceptsUser
    : public ::benchmark::Fixture {};

BENCHMARK_DEFINE_F(BenchmarkPerformanceBenchmarksHeaderOnlyConceptsUser, CallFn)
(::benchmark::State &state) {
  if (auto success = set_thread_affinity_to_core(0); !success) {
    abort();
  }

  auto user = User{FnInterfaceImpl{}};
  for (auto _ : state) {
    REPEAT32(::benchmark::DoNotOptimize(user.fn());)
  }
  state.SetItemsProcessed(32 * state.iterations());
}
BENCHMARK_REGISTER_F(BenchmarkPerformanceBenchmarksHeaderOnlyConceptsUser,
                     CallFn);

} // namespace performance_micro_benchmarks::header_only::concepts
