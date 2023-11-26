#pragma once

#include <memory>

#include "fn_interface.hpp"

namespace performance_micro_benchmarks::header_only::oo {

class User {
public:
  User() = delete;
  ~User() noexcept = default;
  User(const User &) = delete;
  User(User &&) noexcept = default;
  User &operator=(const User &) = delete;
  User &operator=(User &&) noexcept = default;

  explicit User(std::unique_ptr<FnInterface> fn_impl)
      : fn_impl_(std::move(fn_impl)) {}

  int fn() { return fn_impl_->fn(); }

private:
  std::unique_ptr<FnInterface> fn_impl_{};
};

} // namespace performance_micro_benchmarks::header_only::oo
