#pragma once

#include <memory>

#include "fn_interface.hpp"

namespace performance_micro_benchmarks::static_library::oo {

class User {
public:
  User() = delete;
  ~User() = default;
  User(const User &) = delete;
  User(User &&) noexcept = default;
  User &operator=(const User &) = delete;
  User &operator=(User &&) noexcept = default;

  explicit User(std::unique_ptr<FnInterface> fn_impl);

  int fn();

private:
  std::unique_ptr<FnInterface> fn_impl_{};
};

} // namespace performance_micro_benchmarks::static_library::oo
