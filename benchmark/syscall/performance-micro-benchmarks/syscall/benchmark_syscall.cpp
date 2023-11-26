#include <sys/syscall.h>
#include <unistd.h>

#include <benchmark/benchmark.h>

#include "utility.hpp"

namespace performance_micro_benchmarks::syscall {

class BenchmarkPerformanceBenchmarksSyscall : public ::benchmark::Fixture {};

BENCHMARK_DEFINE_F(BenchmarkPerformanceBenchmarksSyscall, CallGetPid)
(::benchmark::State &state) {
  for (auto _ : state) {
    REPEAT32(::benchmark::DoNotOptimize(::syscall(SYS_getpid));)
  }
  state.SetItemsProcessed(32 * state.iterations());
}
BENCHMARK_REGISTER_F(BenchmarkPerformanceBenchmarksSyscall, CallGetPid);

} // namespace performance_micro_benchmarks::syscall

BENCHMARK_MAIN();
