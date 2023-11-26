#pragma once

#include <gmock/gmock.h>

#include <performance-micro-benchmarks/header-only/oo/fn_interface.hpp>

namespace performance_micro_benchmarks::header_only::oo {

class FnInterfaceMock : public FnInterface {
public:
  MOCK_METHOD(int, fn, (), (override));
};

} // namespace performance_micro_benchmarks::header_only::oo
