#include "performance-micro-benchmarks/static-library/oo/user.hpp"

namespace performance_micro_benchmarks::static_library::oo {

User::User(std::unique_ptr<FnInterface> fn_impl)
    : fn_impl_(std::move(fn_impl)) {}

int User::fn() { return fn_impl_->fn(); }

} // namespace performance_micro_benchmarks::static_library::oo
