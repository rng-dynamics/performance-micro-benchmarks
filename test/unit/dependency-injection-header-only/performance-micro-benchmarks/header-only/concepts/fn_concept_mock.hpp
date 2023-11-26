#pragma once

#include <gmock/gmock.h>

namespace performance_micro_benchmarks::header_only::concepts {

struct GoogleMock {
  MOCK_METHOD(int, fn, (), ());
};

class FnConceptMock {
public:
  int fn() { return google_mock_->fn(); }

  GoogleMock &google_mock() { return *google_mock_; }

private:
  std::unique_ptr<GoogleMock> google_mock_ = std::make_unique<GoogleMock>();
};

} // namespace performance_micro_benchmarks::header_only::concepts
