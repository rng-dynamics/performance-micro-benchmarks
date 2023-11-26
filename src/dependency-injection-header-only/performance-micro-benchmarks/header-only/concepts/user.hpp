#pragma once

#include <utility>

#include "fn_concept.hpp"

namespace performance_micro_benchmarks::header_only::concepts {

template <FnConcept T> class User {
public:
  User(T fn_impl) : fn_impl_(std::move(fn_impl)) {}

  int fn() { return fn_impl_.fn(); }

private:
  T fn_impl_{};
};

} // namespace performance_micro_benchmarks::header_only::concepts
