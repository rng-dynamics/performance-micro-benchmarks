#pragma once

#include <utility>

namespace performance_micro_benchmarks::header_only::template_duck_typing {

template <typename FnImpl> class User {
public:
  User() = delete;
  ~User() noexcept = default;
  User(const User &) = delete;
  User(User &&) noexcept = delete;
  User &operator=(const User &) = delete;
  User &operator=(User &&) noexcept = delete;

  explicit User(FnImpl fn_impl) : fn_impl_(std::move(fn_impl)) {}

  int fn() { return fn_impl_.fn(); }

private:
  FnImpl fn_impl_{};
};

} // namespace performance_micro_benchmarks::header_only::template_duck_typing
