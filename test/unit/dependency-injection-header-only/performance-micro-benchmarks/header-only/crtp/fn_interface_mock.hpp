#pragma once

#include <gmock/gmock.h>

#include <performance-micro-benchmarks/header-only/crtp/fn_interface.hpp>

namespace performance_micro_benchmarks::header_only::crtp {

class GoogleMock {
public:
  MOCK_METHOD(int, fn, (), ());
};

class FnInterfaceMock : public FnInterface<FnInterfaceMock> {
public:
  int fn() { return google_mock_->fn(); }
  GoogleMock &google_mock() { return *google_mock_; }

private:
  std::unique_ptr<GoogleMock> google_mock_ = std::make_unique<GoogleMock>();
};

} // namespace performance_micro_benchmarks::header_only::crtp
