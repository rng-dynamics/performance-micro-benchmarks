#include <benchmark/benchmark.h>

#include <performance-micro-benchmarks/shared-library/oo/fn_interface.hpp>
#include <performance-micro-benchmarks/shared-library/oo/user.hpp>

#include "performance-micro-benchmarks/utility.hpp"

namespace performance_micro_benchmarks::shared_library::oo {

namespace {

class FnInterfaceImpl : public oo::FnInterface {
public:
  int fn() override {
    static volatile int value = 42;
    return value;
  }
};

} // namespace

class BenchmarkPerformanceBenchmarksSharedLibraryOoUser
    : public ::benchmark::Fixture {};

BENCHMARK_DEFINE_F(BenchmarkPerformanceBenchmarksSharedLibraryOoUser, CallFn)
(::benchmark::State &state) {
  if (auto success = set_thread_affinity_to_core(0); !success) {
    abort();
  }

  auto user = User{std::make_unique<FnInterfaceImpl>()};
  for (auto _ : state) {
    REPEAT32(::benchmark::DoNotOptimize(user.fn());)
  }
  state.SetItemsProcessed(32 * state.iterations());
}
BENCHMARK_REGISTER_F(BenchmarkPerformanceBenchmarksSharedLibraryOoUser, CallFn);

} // namespace performance_micro_benchmarks::shared_library::oo
