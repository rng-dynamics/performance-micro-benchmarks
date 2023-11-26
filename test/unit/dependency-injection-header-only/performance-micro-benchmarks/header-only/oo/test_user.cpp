#include <gtest/gtest.h>

#include <performance-micro-benchmarks/header-only/oo/user.hpp>

#include "fn_interface_mock.hpp"

namespace performance_micro_benchmarks::header_only::oo {

class TestPerformanceBenchmarksHeaderOnlyOoUser : public ::testing::Test {};

TEST_F(TestPerformanceBenchmarksHeaderOnlyOoUser, CallToFnPasses) {
  auto mock = std::make_unique<FnInterfaceMock>();
  EXPECT_CALL(*mock, fn()).WillOnce(::testing::Return(42));
  auto user = User{std::move(mock)};

  ASSERT_EQ(42, user.fn());
}

} // namespace performance_micro_benchmarks::header_only::oo
