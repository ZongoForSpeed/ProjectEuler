#include <gtest/gtest.h>

#include <deque>

#include "premiers.h"
#include "test.h"

TEST(test_premiers, crible) {
    const std::vector<size_t> premiers100{2, 3, 5, 7, 11, 13, 17, 19, 23,
                                          29, 31, 37, 41, 43, 47, 53, 59,
                                          61, 67, 71, 73, 79, 83, 89, 97};
    std::deque<size_t> resultat;
    premiers::crible2<size_t>(100ULL, std::back_inserter(resultat));
    EXPECT_EQ_COLLECTIONS(premiers100.begin(), premiers100.end(), resultat.begin(), resultat.end());
}

TEST(test_premiers, crible23) {
    std::deque<size_t> resultat;
    premiers::crible23<size_t>(10000ULL, std::back_inserter(resultat));

    EXPECT_EQ(resultat.at(1), 3);
    EXPECT_EQ(resultat.at(2), 5);
    EXPECT_EQ(resultat.at(100), 547);
    EXPECT_EQ(resultat.at(1000), 7927);
}

TEST(test_premiers, crible235) {
    std::deque<size_t> resultat;
    premiers::crible235<size_t>(2000000ULL, std::back_inserter(resultat));

    EXPECT_EQ(resultat.at(1), 3);
    EXPECT_EQ(resultat.at(2), 5);
    EXPECT_EQ(resultat.at(100), 547);
    EXPECT_EQ(resultat.at(1000), 7927);
    EXPECT_EQ(resultat.at(10000), 104743);
    EXPECT_EQ(resultat.at(50000), 611957);
    EXPECT_EQ(resultat.at(100000), 1299721);
}
