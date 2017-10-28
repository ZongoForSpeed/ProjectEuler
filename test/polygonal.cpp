#include <gtest/gtest.h>

#include "polygonal.h"

TEST(test_polygonal, carre) {
    EXPECT_EQ(arithmetiques::racine_carre(15241383936ULL), 123456ULL);
    EXPECT_EQ(polygonal::est_carre(15241383936ULL), true);
    EXPECT_EQ(polygonal::est_carre(15241383935ULL), false);
}

TEST(test_polygonal, cubique) {
    EXPECT_EQ(arithmetiques::racine_cubique(1881365963625ULL), 12345ULL);
    EXPECT_EQ(polygonal::est_cubique(1881365963625ULL), true);
    EXPECT_EQ(polygonal::est_cubique(1881365963624ULL), false);
}

TEST(test_polygonal, triangulaire) {
    EXPECT_EQ(polygonal::triangulaire(100), 5050);
    EXPECT_EQ(polygonal::est_triangulaire(5050), true);
    EXPECT_EQ(polygonal::est_triangulaire(5000), false);
}

TEST(test_polygonal, pentagonal) {
    EXPECT_EQ(polygonal::pentagonal(100), 14950);
    EXPECT_EQ(polygonal::est_pentagonal(3151), true);
    EXPECT_EQ(polygonal::est_pentagonal(3150), false);
}

TEST(test_polygonal, hexagonal) {
    EXPECT_EQ(polygonal::hexagonal(100), 19900);
    EXPECT_EQ(polygonal::est_hexagonal(4560), true);
    EXPECT_EQ(polygonal::est_hexagonal(4550), false);
}

TEST(test_polygonal, heptagonal) {
    EXPECT_EQ(polygonal::heptagonal(100), 24850);
    EXPECT_EQ(polygonal::est_heptagonal(5688), true);
    EXPECT_EQ(polygonal::est_heptagonal(5689), false);
}

TEST(test_polygonal, octagonal) {
    EXPECT_EQ(polygonal::octagonal(100), 29800);
    EXPECT_EQ(polygonal::est_octagonal(5461), true);
    EXPECT_EQ(polygonal::est_octagonal(5460), false);
}
