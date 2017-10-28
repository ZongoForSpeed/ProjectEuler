#include <gtest/gtest.h>

#include "polynome.h"

TEST(test_polynome, initialization_1) {
    Polynome<long long> p(10);
    EXPECT_EQ(p.taille(), 1);
    EXPECT_EQ(p.valeur(42), 10);
}

TEST(test_polynome, initialization_2) {
    Polynome<long long> p{-1, 0, 1};
    EXPECT_EQ(p.taille(), 3);
    EXPECT_EQ(p.valeur(2), 3);
}

TEST(test_polynome, comparaison) {
    Polynome<long long> p{-1, 0, 1};
    Polynome<long long> q{-1, 0, 1};
    Polynome<long long> r{1, 0, 1};
    EXPECT_EQ(p, q);
    EXPECT_NE(p, r);
}

TEST(test_polynome, addition) {
    Polynome<long long> p{-1, 0, 1};
    Polynome<long long> q{0, 1};
    Polynome<long long> r{-1, 1, 1};
    EXPECT_EQ(p + q, r);
}

TEST(test_polynome, soustraction) {
    Polynome<long long> p{-1, 1, 1};
    Polynome<long long> q{0, 0, 1};
    Polynome<long long> r{-1, 1};
    EXPECT_EQ(p - q, r);
}

TEST(test_polynome, multiplication) {
    Polynome<long long> p{1, -1, 1, -1, 1};
    Polynome<long long> q{1, 1,};
    Polynome<long long> r{1, 0, 0, 0, 0, 1};
    EXPECT_EQ(p * q, r);
}

TEST(test_polynome, affiche_1) {
    Polynome<long long> p{1, -1, 1, -1, 1};
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "X^4 - X^3 + X^2 - X + 1");
}

TEST(test_polynome, affiche_2) {
    Polynome<long long> p{1, 1,};
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "X + 1");
}

TEST(test_polynome, affiche_3) {
    Polynome<long long> p{1, 0, 0, 0, 0, 1};
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "X^5 + 1");
}

TEST(test_polynome, division_euclidienne_1) {
    Polynome<long long> A{0, -2, 3, -1, -1, 1};
    Polynome<long long> B{1, -1, 1};


    Polynome<long long> Q;
    Polynome<long long> R;
    Polynome<long long>::division_euclidienne(A, B, Q, R);

    Polynome<long long> Q1{1, -2, 0, 1};
    Polynome<long long> R1{-1, 1};

    EXPECT_EQ(Q, Q1);
    EXPECT_EQ(R, R1);
}

TEST(test_polynome, division_euclidienne_2) {
    Polynome<long long> A{-1, 0, 0, 0, 0, 0, 0, 1};
    Polynome<long long> B{-1, 1};

    Polynome<long long> Q;
    Polynome<long long> R;

    Polynome<long long>::division_euclidienne(A, B, Q, R);
    Polynome<long long> Q1{1, 1, 1, 1, 1, 1, 1};
    Polynome<long long> R1;

    EXPECT_EQ(Q, Q1);
    EXPECT_EQ(R, R1);
}
