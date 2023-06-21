#include <gtest/gtest.h>
#include <random>
#include <list>
#include "TupleLib/Tuple.h"

class SomeTuples : public ::testing::Test {
protected:
    tuple<int, int, int, int, int> t1;
    tuple<char, char, char, char> t2;
    tuple<float, double, char, std::string, std::string_view, int64_t> t3;
    tuple<std::string, std::vector<size_t>, std::list<double>> t4;

    char str[27] = {"Some c-str for string_view"};
    std::string_view view = str;
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

TEST_F(SomeTuples, GetByType){

    t3 = make_tuple(54.5f, 234.32, 'f', std::string("Hello World!!!"), view, LLONG_MAX);
    ASSERT_EQ(get<float>(t3), 54.5f);
    ASSERT_EQ(get<double>(t3), 234.32);
    ASSERT_EQ(get<char>(t3), 'f');
    ASSERT_EQ(get<std::string>(t3), "Hello World!!!");
    ASSERT_EQ(get<std::string_view>(t3), "Some c-str for string_view");
    ASSERT_EQ(get<int64_t>(t3), LLONG_MAX);

    std::vector<size_t> vector({45, 54, 23, 34453});
    std::list<double> list{56.4, -324.5, -342.34523};
    t4 = make_tuple(std::string("Tuple"), vector, list);

    ASSERT_EQ(get<std::string>(t4), "Tuple");

    auto vec = get<std::vector<size_t>>(t4);
    for (size_t i = 0; i < vector.size(); ++i)
        ASSERT_EQ(vector[i], vec[i]);

    auto lst = get<std::list<double>>(t4);
    auto it_lst = lst.begin();
    for (auto now : list){
        ASSERT_EQ(now, *it_lst);
        ++it_lst;
    }

}