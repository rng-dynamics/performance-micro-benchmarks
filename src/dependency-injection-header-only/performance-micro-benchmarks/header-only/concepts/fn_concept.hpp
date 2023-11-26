#pragma once

#include <concepts>

namespace performance_micro_benchmarks::header_only::concepts {

template <typename T>
concept FnConcept = requires(T value) {
  { value.fn() } -> std::same_as<int>;
};

} // namespace performance_micro_benchmarks::header_only::concepts
