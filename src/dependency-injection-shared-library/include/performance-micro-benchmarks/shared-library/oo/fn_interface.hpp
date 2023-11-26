#pragma once

namespace performance_micro_benchmarks::shared_library::oo {

class FnInterface {
public:
  virtual ~FnInterface() noexcept = default;
  virtual int fn() = 0;
};

} // namespace performance_micro_benchmarks::shared_library::oo
