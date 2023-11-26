#include <gtest/gtest.h>

#include <performance-micro-benchmarks/header-only/template-duck-typing/user.hpp>

#include "fn_interface_mock.hpp"

namespace performance_micro_benchmarks::header_only::template_duck_typing {

class TestPerformanceBenchmarksHeaderOnlyTemplateDuckTypingUser
    : public ::testing::Test {};

TEST_F(TestPerformanceBenchmarksHeaderOnlyTemplateDuckTypingUser,
       CallToFnPasses) {
  auto mock_wrapper =
      FnInterfaceMockWrapper{std::make_unique<FnInterfaceMock>()};
  EXPECT_CALL(mock_wrapper.mock(), fn()).WillOnce(::testing::Return(42));
  auto user = User<FnInterfaceMockWrapper>{std::move(mock_wrapper)};

  ASSERT_EQ(42, user.fn());
}

} // namespace performance_micro_benchmarks::header_only::template_duck_typing
