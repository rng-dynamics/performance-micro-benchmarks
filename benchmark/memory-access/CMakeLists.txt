add_executable(
  memory-access-benchmarks
)
target_sources(
  memory-access-benchmarks
  PRIVATE
    "performance-micro-benchmarks/memory-access/benchmark_memory_access.cpp"
)
target_link_libraries(
  memory-access-benchmarks
  PRIVATE
    support-library
    benchmark::benchmark
)
target_include_directories(
  memory-access-benchmarks
  PRIVATE
    support-library
)

add_custom_target(memory-access-benchmarks-assembly
  ALL
  DEPENDS
    memory-access-benchmarks
  COMMAND
    objdump -CdlS -M intel "${CMAKE_BINARY_DIR}/benchmark/memory-access/memory-access-benchmarks" > "${CMAKE_BINARY_DIR}/benchmark/memory-access/memory-access-benchmarks.asm"
)
