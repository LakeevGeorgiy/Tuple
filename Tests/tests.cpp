#include <gtest/gtest.h>
#include <random>
#include "TupleLib/Tuple.h"

class SomeTuples : public ::testing::Test {
protected:
    tuple<int, int, int, int, int> t1;
    tuple<char, char, char, char> t2;
    tuple<float, double, char, std::string, std::string_view, int64_t> t3;
    tuple<std::string, std::vector<size_t>, std::variant<int, double, char>> t4;
};

TEST_F(SomeTuples, CreateTuple){
    // If there are no Segfault, then tuples are created
    ASSERT_TRUE(true);
}

TEST_F(SomeTuples, MakeTuple) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist_int(INT_MIN, INT_MAX);
    std::uniform_int_distribution<char> dist_char(CHAR_MIN, CHAR_MAX);
    std::uniform_real_distribution<double> dist_double(INT_MIN, INT_MAX);

    for (uint8_t i = 0; i < 5; ++i) {
        t1 = make_tuple(dist_int(rd), dist_int(rd), dist_int(rd), dist_int(rd), dist_int(rd));
    }

    for (uint8_t i = 0; i < 5; ++i) {
        t2 = make_tuple(dist_char(rd), dist_char(rd), dist_char(rd), dist_char(rd));
    }

}