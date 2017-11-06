#include <gtest/gtest.h>

#include "polygonal.h"

TEST(test_polygonal, carre) {
    EXPECT_EQ(123456ULL, arithmetiques::racine_carre(15241383936ULL));
    EXPECT_TRUE(polygonal::est_carre(15241383936ULL));
    EXPECT_FALSE(polygonal::est_carre(15241383935ULL));
}

TEST(test_polygonal, cubique) {
    EXPECT_EQ(12345ULL, arithmetiques::racine_cubique(1881365963625ULL));
    EXPECT_TRUE(polygonal::est_cubique(1881365963625ULL));
    EXPECT_FALSE(polygonal::est_cubique(1881365963624ULL));
}

TEST(test_polygonal, triangulaire) {
    EXPECT_EQ(5050, polygonal::triangulaire(100));
    EXPECT_TRUE(polygonal::est_triangulaire(5050));
    EXPECT_FALSE(polygonal::est_triangulaire(5000));
}

TEST(test_polygonal, pentagonal) {
    EXPECT_EQ(14950, polygonal::pentagonal(100));
    EXPECT_TRUE(polygonal::est_pentagonal(3151));
    EXPECT_FALSE(polygonal::est_pentagonal(3150));
}

TEST(test_polygonal, hexagonal) {
    EXPECT_EQ(19900, polygonal::hexagonal(100));
    EXPECT_TRUE(polygonal::est_hexagonal(4560));
    EXPECT_FALSE(polygonal::est_hexagonal(4550));
}

TEST(test_polygonal, heptagonal) {
    EXPECT_EQ(24850, polygonal::heptagonal(100));
    EXPECT_TRUE(polygonal::est_heptagonal(5688));
    EXPECT_FALSE(polygonal::est_heptagonal(5689));
}

TEST(test_polygonal, octagonal) {
    EXPECT_EQ(29800, polygonal::octagonal(100));
    EXPECT_TRUE(polygonal::est_octagonal(5461));
    EXPECT_FALSE(polygonal::est_octagonal(5460));
}

TEST(test_polygonal, somme_carres) {
    EXPECT_EQ(338350, polygonal::somme_carres(100));
    EXPECT_EQ(54301841231, polygonal::somme_carres(5461ll));
    EXPECT_EQ(54272018710, polygonal::somme_carres(5460ll));
}

TEST(test_polygonal, somme_cubes) {
    EXPECT_EQ(25502500, polygonal::somme_cubes(100));
    EXPECT_EQ(222427127548081, polygonal::somme_cubes(5461ll));
    EXPECT_EQ(222264266760900, polygonal::somme_cubes(5460ll));
}
