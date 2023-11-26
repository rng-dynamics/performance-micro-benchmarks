#pragma once

#include <gmock/gmock.h>

namespace performance_micro_benchmarks::header_only::template_duck_typing {

class FnInterfaceMock {
public:
  MOCK_METHOD(int, fn, (), ());
};

class FnInterfaceMockWrapper {
public:
  FnInterfaceMockWrapper(std::unique_ptr<FnInterfaceMock> mock)
      : mock_(std::move(mock)) {
    if (!mock_) {
      throw std::invalid_argument{"mock is equal to nullptr"};
    }
  }
  int fn() { return mock_->fn(); }
  FnInterfaceMock &mock() { return *mock_; }

private:
  std::unique_ptr<FnInterfaceMock> mock_{};
};

} // namespace performance_micro_benchmarks::header_only::template_duck_typing
