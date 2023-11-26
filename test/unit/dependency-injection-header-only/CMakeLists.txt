include(GoogleTest)

add_executable(dependency-injection-header-only-unit-tests)
target_sources(dependency-injection-header-only-unit-tests
  PRIVATE
    "performance-micro-benchmarks/header-only/concepts/test_user.cpp"
    "performance-micro-benchmarks/header-only/crtp/test_user.cpp"
    "performance-micro-benchmarks/header-only/oo/test_user.cpp"
    "performance-micro-benchmarks/header-only/template-duck-typing/test_user.cpp"
)
target_link_libraries(dependency-injection-header-only-unit-tests
  PRIVATE
    dependency-injection-header-only
    gtest_main
    gmock
)
