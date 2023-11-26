#include <gtest/gtest.h>

#include <performance-micro-benchmarks/header-only/crtp/user.hpp>

#include "fn_interface_mock.hpp"

namespace performance_micro_benchmarks::header_only::crtp {

class TestPerformanceBenchmarksHeaderOnlyCrtpUser : public ::testing::Test {};

TEST_F(TestPerformanceBenchmarksHeaderOnlyCrtpUser, CallToFnPasses) {
  auto mock = FnInterfaceMock{};
  EXPECT_CALL(mock.google_mock(), fn()).WillOnce(::testing::Return(42));
  auto user = User<FnInterfaceMock>{std::move(mock)};

  ASSERT_EQ(42, user.fn());
}

} // namespace performance_micro_benchmarks::header_only::crtp
