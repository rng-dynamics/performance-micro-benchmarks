#include <benchmark/benchmark.h>

#include <performance-micro-benchmarks/header-only/crtp/user.hpp>

#include "utility.hpp"

namespace performance_micro_benchmarks::header_only::crtp {

namespace {

class FnInterfaceImpl : public FnInterface<FnInterfaceImpl> {
public:
  int fn() {
    static volatile int value = 42;
    return value;
  }
};

} // namespace

class BenchmarkPerformanceBenchmarksHeaderOnlyCrtpUser
    : public ::benchmark::Fixture {};

BENCHMARK_DEFINE_F(BenchmarkPerformanceBenchmarksHeaderOnlyCrtpUser, CallFn)
(::benchmark::State &state) {
  auto user = User{FnInterfaceImpl()};
  for (auto _ : state) {
    REPEAT32(::benchmark::DoNotOptimize(user.fn());)
  }
  state.SetItemsProcessed(32 * state.iterations());
}
BENCHMARK_REGISTER_F(BenchmarkPerformanceBenchmarksHeaderOnlyCrtpUser, CallFn);

} // namespace performance_micro_benchmarks::header_only::crtp
