#include <gtest/gtest.h>

#include "combinatoire.h"

TEST(test_combinatoire, coefficient_binomial) {
    EXPECT_EQ(35, combinatoire::coefficient_binomial(7, 3));
    EXPECT_EQ(70, combinatoire::coefficient_binomial(8, 4));
    EXPECT_EQ(1, combinatoire::coefficient_binomial(40, 0));
}

TEST(test_combinatoire, catalan) {
    EXPECT_EQ(1, combinatoire::catalan(0));
    EXPECT_EQ(1, combinatoire::catalan(1));
    EXPECT_EQ(16796, combinatoire::catalan<unsigned long long>(10));
}

TEST(test_combinatoire, factorielle) {
    EXPECT_EQ(120, combinatoire::factorielle(5));
    EXPECT_EQ(720, combinatoire::factorielle(6));
}
