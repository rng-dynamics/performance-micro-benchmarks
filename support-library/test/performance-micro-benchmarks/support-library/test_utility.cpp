#include <emmintrin.h>
#include <immintrin.h>

#include <gtest/gtest.h>

#include <performance-micro-benchmarks/support-library/utility.hpp>

namespace support_library::utility {

template <typename T> class TestSupportLibraryUtility : public ::testing::Test {
public:
  using Type = T;
};

using RelevantTypes = ::testing::Types<unsigned long, __m128i, __m256i>;
TYPED_TEST_SUITE(TestSupportLibraryUtility, RelevantTypes);

TYPED_TEST(TestSupportLibraryUtility, WriteIntIntoWordAndReadToInt) {
  using Word = TypeParam;

  auto test_cases = std::array{int{42}, int{}, int{-8}, int{INT_MAX}};

  for (const auto &int_value : test_cases) {
    auto word = Word{};

    // functions under test
    WriteIntIntoWord(word, int_value);
    int read = ReadIntFromWord(word);

    EXPECT_EQ(int_value, read);
  }
}

TYPED_TEST(TestSupportLibraryUtility, FillAndReadDataArray) {
  using Word = TypeParam;

  auto values = std::vector<int>{1, 3, 0, 2};
  auto size = std::ssize(values);
  auto data_vector = std::vector<Word>(size, Word{});
  const Word *data_array_ptr = data_vector.data();

  // functions under test
  FillDataArray(data_array_ptr, size, values);
  std::vector<int> encoded_result = ReadDataArray(data_array_ptr, size);
  std::vector<int> decoded_result =
      ComputeRandomSequenceFromDataArray(data_array_ptr, size);

  EXPECT_EQ((std::vector<int>{2, 3, 1, 0}), encoded_result);
  EXPECT_EQ(values, decoded_result);
}

} // namespace support_library::utility
