#pragma once

#include <type_traits>
#include <utility>

#include "fn_interface.hpp"

namespace performance_micro_benchmarks::header_only::crtp {

template <typename T,
          typename = std::enable_if_t<std::is_base_of_v<FnInterface<T>, T>>>
class User {
public:
  User() = delete;
  ~User() noexcept = default;
  User(const User &) = default;
  User(User &&) noexcept = default;
  User &operator=(const User &) = default;
  User &operator=(User &&) noexcept = default;

  explicit User(T &&fn_impl) : fn_impl_{std::move(fn_impl)} {}

  int fn() { return fn_impl_.fn(); }

private:
  T fn_impl_{};
};

} // namespace performance_micro_benchmarks::header_only::crtp
