#pragma once

namespace performance_micro_benchmarks::header_only::crtp {

template <typename Derived> class FnInterface {
public:
  FnInterface(const FnInterface &) = default;
  FnInterface(FnInterface &&) noexcept = default;
  FnInterface &operator=(const FnInterface &) = default;
  FnInterface &operator=(FnInterface &&) noexcept = default;

  int fn() { return derived().fn(); }

protected:
  FnInterface() = default;
  ~FnInterface() noexcept = default;

private:
  Derived &derived() { return static_cast<Derived &>(*this); }
  Derived const &derived() const { return static_cast<Derived const &>(*this); }
};

} // namespace performance_micro_benchmarks::header_only::crtp
