#include <gtest/gtest.h>

#include <performance-micro-benchmarks/header-only/concepts/user.hpp>

#include "fn_concept_mock.hpp"

namespace performance_micro_benchmarks::header_only::concepts {

class TestPerformanceBenchmarksHeaderOnlyConceptsUser : public ::testing::Test {
};

TEST_F(TestPerformanceBenchmarksHeaderOnlyConceptsUser, CallToFnPasses) {
  auto mock = FnConceptMock{};
  EXPECT_CALL(mock.google_mock(), fn()).WillOnce(::testing::Return(42));
  auto user = User{std::move(mock)};

  ASSERT_EQ(42, user.fn());
}

} // namespace performance_micro_benchmarks::header_only::concepts
