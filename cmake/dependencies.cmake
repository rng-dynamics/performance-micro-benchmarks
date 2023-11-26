include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.2.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(googletest)

set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
set(CMAKE_BUILD_TYPE_BACKUP ${CMAKE_BUILD_TYPE})
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(googlebenchmark)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_BACKUP} CACHE STRING "" FORCE)
