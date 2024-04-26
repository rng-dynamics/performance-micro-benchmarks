#include <benchmark/benchmark.h>

#include <performance-micro-benchmarks/header-only/oo/fn_interface.hpp>
#include <performance-micro-benchmarks/header-only/oo/user.hpp>

#include <performance-micro-benchmarks/support-library/utility.hpp>

namespace performance_micro_benchmarks::header_only::oo {

namespace {

class FnInterfaceImpl : public oo::FnInterface {
public:
  int fn() override {
    static volatile int value = 42;
    return value;
  }
};

} // namespace

class BenchmarkPerformanceBenchmarksHeaderOnlyOoUser
    : public ::benchmark::Fixture {};

BENCHMARK_DEFINE_F(BenchmarkPerformanceBenchmarksHeaderOnlyOoUser, CallFn)
(::benchmark::State &state) {
  if (auto success = support_library::utility::SetThreadAffinityToCore(0);
      !success) {
    abort();
  }

  auto user = User{std::make_unique<FnInterfaceImpl>()};
  for (auto _ : state) {
    REPEAT32(::benchmark::DoNotOptimize(user.fn());)
  }
  state.SetItemsProcessed(32 * state.iterations());
}
BENCHMARK_REGISTER_F(BenchmarkPerformanceBenchmarksHeaderOnlyOoUser, CallFn);

} // namespace performance_micro_benchmarks::header_only::oo
