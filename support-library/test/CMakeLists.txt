include(GoogleTest)

add_executable(
  support-library-tests
)
target_sources(
  support-library-tests
  PRIVATE
    "performance-micro-benchmarks/support-library/test_utility.cpp"
)
target_link_libraries(
  support-library-tests
  PRIVATE
    support-library
    gtest_main
)
