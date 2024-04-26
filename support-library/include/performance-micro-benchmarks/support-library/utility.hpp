#pragma once

#include <iostream>
#include <ostream>
#include <pthread.h>
#include <stdexcept>
#include <vector>

#define REPEAT2(x) x x
#define REPEAT4(x) REPEAT2(x) REPEAT2(x)
#define REPEAT8(x) REPEAT4(x) REPEAT4(x)
#define REPEAT16(x) REPEAT8(x) REPEAT8(x)
#define REPEAT32(x) REPEAT16(x) REPEAT16(x)

#define READ_INT_FROM_WORD(word) *((int *)(void *)(&word))

namespace support_library::utility {

inline bool SetThreadAffinityToCore(int core_id) noexcept {
  auto cpu_set = cpu_set_t{};
  CPU_ZERO(&cpu_set);
  CPU_SET(core_id, &cpu_set);
  return ::pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t),
                                  &cpu_set) == 0;
}

inline void OnInvalidArgument(bool condition, const std::string &message) {
  if (!condition) {
    throw std::invalid_argument{message};
  }
}

inline void OnLogicError(bool condition, const std::string &message) {
  if (!condition) {
    throw std::logic_error{message};
  }
}

template <typename Word> inline void WriteIntIntoWord(Word &word, int value) {
  *(int *)(&word) = value;
}

template <typename Word> inline int ReadIntFromWord(const Word &word) {
  return READ_INT_FROM_WORD(word);
}

template <typename Word>
inline void FillDataArray(const Word *array_begin, const int array_size,
                          const std::vector<int> &values) {
  OnInvalidArgument(array_size == std::ssize(values), "precondition");

  if (values.empty()) {
    return;
  }
  if (values.size() == 1) {
    WriteIntIntoWord(*(array_begin), values.front());
    return;
  }

  int write_idx = values.front();
  int read_idx = 1;
  for (int lidx = 0; lidx < array_size; ++lidx) {
    const int value = values.at(read_idx);
    WriteIntIntoWord(*(array_begin + write_idx), value);
    write_idx = value;
    read_idx = (read_idx + 1) % array_size;
  }
}

template <typename Word>
inline std::vector<int> ReadDataArray(const Word *array_begin,
                                      const int array_size) {
  auto result = std::vector<int>{};
  result.reserve(array_size);
  for (int idx = 0; idx < array_size; ++idx) {
    int int_value = ReadIntFromWord(*(array_begin + idx));
    result.push_back(int_value);
  }
  return result;
}

template <typename Word>
inline std::vector<int>
ComputeRandomSequenceFromDataArray(const Word *array_begin,
                                   const int array_size) {
  std::vector<int> array_as_vec = ReadDataArray(array_begin, array_size);
  if (array_as_vec.empty()) {
    return {};
  }
  int read_idx = array_as_vec.front();
  int vec_size = array_as_vec.size();

  auto result = std::vector<int>();
  result.reserve(vec_size);
  for (int lidx = 0; lidx < vec_size; ++lidx) {
    auto array_value = array_as_vec.at(read_idx);
    result.push_back(array_value);
    read_idx = array_value;
  }

  return result;
}

inline void PrintVec(std::ostream &stream, const std::vector<int> &vec) {
  auto seperator = std::string{","};
  auto ss = std::string{""};
  stream << "std::vector<int>{";
  for (const auto &value : vec) {
    stream << ss << value;
    ss = seperator;
  }
  stream << "}";
}

} // namespace support_library::utility
