#include <gtest/gtest.h>

#include "chiffres.h"
#include "test.h"

TEST(test_chiffres, nombre_chiffres) {
    EXPECT_EQ(9, chiffres::nombre_chiffres(123456789ULL));
}

TEST(test_chiffres, somme_chiffres) {
    EXPECT_EQ(45, chiffres::somme_chiffres(123456789ULL));
}

TEST(test_chiffres, extraire_chiffres) {
    auto c = chiffres::extraire_chiffres(123456789ULL);
    std::deque<size_t> r{1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ_COLLECTIONS(c.begin(), c.end(), r.begin(), r.end());
}

TEST(test_chiffres, palindrome) {
    EXPECT_EQ(false, chiffres::palindrome(123456789ULL));
    EXPECT_EQ(true, chiffres::palindrome(123454321ULL));
}

TEST(test_chiffres, pandigital) {
    EXPECT_EQ(true, chiffres::pandigital(123456789ULL));
    EXPECT_EQ(false, chiffres::pandigital(1234567890ULL));
    EXPECT_EQ(false, chiffres::pandigital(123454321ULL));
}

TEST(test_chiffres, conversion_nombre) {
    std::deque<size_t> c{1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(123456789ULL, chiffres::conversion_nombre<size_t>(c.begin(), c.end()));
}

TEST(test_chiffres, permutation_chiffres) {
    EXPECT_EQ(true, chiffres::permutation_chiffres(123456789ULL, 918273645ULL));
    EXPECT_EQ(true, chiffres::permutation_chiffres(123ULL, 1234ULL));
}

TEST(test_chiffres, inverser_nombre) {
    EXPECT_EQ(987654321ULL, chiffres::inverser_nombre(123456789ULL));
}

TEST(test_chiffres, concatener) {
    EXPECT_EQ(123456789ULL, chiffres::concatener(12ULL, 3456789ULL));
    EXPECT_EQ(123456789ULL, chiffres::concatener(12ULL, 345ULL, 6789ULL));
    EXPECT_EQ(123456789ULL, chiffres::concatener(12ULL, 34ULL, 567ULL, 89ULL));
}
