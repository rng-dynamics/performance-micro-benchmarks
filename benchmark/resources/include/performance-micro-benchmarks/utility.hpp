#pragma once

#include <pthread.h>

namespace performance_micro_benchmarks {

#define REPEAT2(x) x x
#define REPEAT4(x) REPEAT2(x) REPEAT2(x)
#define REPEAT8(x) REPEAT4(x) REPEAT4(x)
#define REPEAT16(x) REPEAT8(x) REPEAT8(x)
#define REPEAT32(x) REPEAT16(x) REPEAT16(x)

inline bool set_thread_affinity_to_core(int core_id) noexcept {
  auto cpu_set = cpu_set_t{};
  CPU_ZERO(&cpu_set);
  CPU_SET(core_id, &cpu_set);
  return ::pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t),
                                  &cpu_set) == 0;
}

} // namespace performance_micro_benchmarks
