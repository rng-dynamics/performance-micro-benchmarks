Perfomance Micro Benchmarks
===========================

A collection of performance micro benchmarks in C++.


Build
-----

```
$ mkdir build && cd build
$ cmake .. && make
```
Executable build artifacts are located in the folders `benchmark` and `test`.
```
$ find benchmark test -type f -executable
benchmark/dependency-injection-header-only/dependency-injection-header-only-benchmarks
benchmark/memory-access/memory-access-benchmarks
benchmark/dependency-injection-static-library/dependency-injection-static-library-benchmarks
benchmark/syscall/syscall-benchmarks
benchmark/dependency-injection-shared-library/dependency-injection-shared-library-benchmarks
test/unit/dependency-injection-header-only/dependency-injection-header-only-unit-tests
```


Content
-------

- [Benchmarks for system calls](benchmark/syscall/performance-micro-benchmarks/syscall/benchmark_syscall.cpp).
- [Benchmarks for memory and cache access time](benchmark/memory-access/performance-micro-benchmarks/memory-access/benchmark_memory_access.cpp).
- Benchmark for dependency injection using C++ concepts:
  - [dependency injection using C++ concepts source files](src/dependency-injection-header-only/performance-micro-benchmarks/header-only/concepts/),
  - [dependency injection using C++ concepts benchmark](benchmark/dependency-injection-header-only/performance-micro-benchmarks/header-only/concepts/benchmark_user.cpp),
  - [dependency injection using C++ concepts unit tests](test/unit/dependency-injection-header-only/performance-micro-benchmarks/header-only/concepts/).
- Benchmark for dependency injection using the Curiously Recurring Template Pattern (CRTP):
  - [dependency injection using CRTP source files](src/dependency-injection-header-only/performance-micro-benchmarks/header-only/crtp/),
  - [dependency injection using CRTP benchmark](benchmark/dependency-injection-header-only/performance-micro-benchmarks/header-only/crtp/benchmark_user.cpp),
  - [dependency injection using CRTP unit tests](test/unit/dependency-injection-header-only/performance-micro-benchmarks/header-only/crtp/).
- Benchmark for dependency injection using pure virtual interface classes:
  - [dependency injection using pure virtual interface class source files](src/dependency-injection-header-only/performance-micro-benchmarks/header-only/oo/),
  - [dependency injection using pure virtual interface class benchmark](benchmark/dependency-injection-header-only/performance-micro-benchmarks/header-only/oo/benchmark_user.cpp),
  - [dependency injection using pure virtual interface class unit tests](test/unit/dependency-injection-header-only/performance-micro-benchmarks/header-only/oo/).
- Benchmark for dependency injection using template duck typing:
  - [dependency injection using template duck typing source files](src/dependency-injection-header-only/performance-micro-benchmarks/header-only/template-duck-typing/),
  - [dependency injection using template duck typing benchmark](benchmark/dependency-injection-header-only/performance-micro-benchmarks/header-only/template-duck-typing/benchmark_user.cpp),
  - [dependency injection using template duck typing unit tests](test/unit/dependency-injection-header-only/performance-micro-benchmarks/header-only/template-duck-typing/).
- Benchmark for dependency injection into a static library:
  - [static library source files](src/dependency-injection-static-library/include/performance-micro-benchmarks/static-library/oo/),
  - [static library benchmark](benchmark/dependency-injection-static-library/performance-micro-benchmarks/static-library/oo/benchmark_user.cpp).
- Benchmark for dependency injection into a shared library:
  - [shared library source files](src/dependency-injection-shared-library/include/performance-micro-benchmarks/shared-library/oo/),
  - [shared library benchmark](benchmark/dependency-injection-shared-library/performance-micro-benchmarks/shared-library/oo/benchmark_user.cpp).


License
-------

This project is licensed under the BSD-3-Clause license - see the [LICENSE.md](LICENSE.md) file for details
