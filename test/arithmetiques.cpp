#include <gtest/gtest.h>
#include "test.h"

#include "arithmetiques.h"

class test_arithmetiques : public ::testing::Test {
public:
    std::vector<size_t> premiers;

    explicit test_arithmetiques() {
        premiers = std::vector<size_t> {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                        31, 37, 41, 43, 47, 53, 59, 61, 67,
                                        71, 73, 79, 83, 89, 97};
    }

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    ~test_arithmetiques() override = default;
};

TEST_F(test_arithmetiques, pgcd) {
    EXPECT_EQ(arithmetiques::PGCD(456753ULL, 97643ULL), 1);
    EXPECT_EQ(arithmetiques::PGCD(456755ULL, 158665ULL), 65);
}

TEST_F(test_arithmetiques, ppcm) {
    EXPECT_EQ(arithmetiques::PPCM(456753ULL, 97643ULL), 44598733179ULL);
    EXPECT_EQ(arithmetiques::PPCM(456755ULL, 158665ULL), 1114938955);
}

TEST_F(test_arithmetiques, arrondi) {
    EXPECT_EQ(arithmetiques::arrondi(1000, 101), 10);
    EXPECT_EQ(arithmetiques::arrondi(12345678, 48), 257202);
}

TEST_F(test_arithmetiques, Bezout1) {
    long long u, v;
    long long a = 456753LL;
    long long b = 97643LL;
    arithmetiques::Bezout(a, b, u, v);

    EXPECT_EQ(u, 18947LL);
    EXPECT_EQ(v, -88630LL);
    EXPECT_EQ(a * u + b * v, 1); // PGCD(a, b) = 1
}

TEST_F(test_arithmetiques, Bezout2) {
    long long u, v;
    long long a = 456755ULL;
    long long b = 158665ULL;
    arithmetiques::Bezout(a, b, u, v);

    EXPECT_EQ(u, 602LL);
    EXPECT_EQ(v, -1733LL);
    EXPECT_EQ(a * u + b * v, 65); // PGCD(a, b) = 65
}


TEST_F(test_arithmetiques, nombre_diviseurs) {
    EXPECT_EQ(arithmetiques::nombre_diviseurs(3246999210ULL, premiers), 640);
}

TEST_F(test_arithmetiques, somme_diviseurs) {
    EXPECT_EQ(arithmetiques::somme_diviseurs(3246999210ULL, premiers), 11708928000ULL);
    EXPECT_EQ(arithmetiques::somme_diviseurs(496ULL, premiers), 992ULL);
}

TEST_F(test_arithmetiques, decomposition_1) {
    std::map<size_t, size_t> decomposition;
    std::map<size_t, size_t> result{{2,  1},
                                    {3,  4},
                                    {5,  1},
                                    {7,  3},
                                    {13, 1},
                                    {29, 1},
                                    {31, 1}};
    arithmetiques::decomposition(3246999210ULL, premiers, decomposition);
    EXPECT_EQ_COLLECTIONS(decomposition.begin(), decomposition.end(), result.begin(), result.end());
}

TEST_F(test_arithmetiques, decomposition_2) {
    std::map<size_t, size_t> decomposition;
    std::map<size_t, size_t> result{{2,  4},
                                    {31, 1}};
    arithmetiques::decomposition(496ULL, premiers, decomposition);
    EXPECT_EQ_COLLECTIONS(decomposition.begin(), decomposition.end(), result.begin(), result.end());
}

TEST_F(test_arithmetiques, radical) {
    EXPECT_EQ(arithmetiques::radical(3246999210ULL, premiers), 2454270ULL);
    EXPECT_EQ(arithmetiques::radical(496ULL, premiers), 62ULL);
}

TEST_F(test_arithmetiques, test_arithmetiques) {
    EXPECT_EQ(arithmetiques::nombre_facteur(3246999210ULL, 3ULL), 4ULL);
    EXPECT_EQ(arithmetiques::nombre_facteur(496ULL, 5ULL), 0ULL);
}

TEST_F(test_arithmetiques, phi) {
    EXPECT_EQ(arithmetiques::phi(3246999210ULL, premiers), 640120320);
    EXPECT_EQ(arithmetiques::phi(496ULL, premiers), 240);
}

TEST_F(test_arithmetiques, moebius) {
    EXPECT_EQ(arithmetiques::moebius(3246999210ULL, premiers), 0);
    EXPECT_EQ(arithmetiques::moebius(496ULL, premiers), 0);
    EXPECT_EQ(arithmetiques::moebius(19ULL, premiers), -1);
    EXPECT_EQ(arithmetiques::moebius(15ULL, premiers), 1);
}

TEST_F(test_arithmetiques, facteur_carre) {
    EXPECT_EQ(arithmetiques::facteur_carre(3246999210ULL, premiers), true);
    EXPECT_EQ(arithmetiques::facteur_carre(42315ULL, premiers), false);
}

TEST_F(test_arithmetiques, diviseurs) {
    auto d = arithmetiques::diviseurs(496ULL, premiers);
    std::vector<size_t> result{1, 2, 4, 8, 16, 31, 62, 124, 248, 496};
    EXPECT_EQ_COLLECTIONS(d.begin(), d.end(), result.begin(), result.end());
}

TEST_F(test_arithmetiques, repunit) {
    EXPECT_EQ(arithmetiques::repunit::A(11ULL), 2);
    EXPECT_EQ(arithmetiques::repunit::A(3ULL), 3);
    EXPECT_EQ(arithmetiques::repunit::A(7ULL), 6);
}

TEST_F(test_arithmetiques, inverse) {
    EXPECT_EQ(arithmetiques::inverse_modulaire<unsigned long>(3, 11, premiers), 4);
    EXPECT_EQ(arithmetiques::inverse_modulaire<unsigned long>(97643, 456753, premiers), 368123);
    EXPECT_EQ(arithmetiques::inverse_modulaire<unsigned long long>(107113, 3246999210ULL, premiers), 180730717ULL);
}


TEST_F(test_arithmetiques, chinois1) {
    std::vector<unsigned long> modulos{3, 5, 7};
    std::vector<unsigned long> restes{2, 3, 2};

    auto reste = arithmetiques::restes_chinois<unsigned long>(modulos, restes, premiers);
    EXPECT_EQ(reste, 23);
}

TEST_F(test_arithmetiques, chinois2) {
    std::vector<unsigned long> modulos{3, 4, 5};
    std::vector<unsigned long> restes{2, 3, 1};

    auto reste = arithmetiques::restes_chinois<unsigned long>(modulos, restes, premiers);
    EXPECT_EQ(reste, 11);
}

TEST_F(test_arithmetiques, racine) {
    EXPECT_EQ(arithmetiques::racine_carre<unsigned long long>(123456789ULL), 11111ULL);
    EXPECT_EQ(arithmetiques::racine_carre<unsigned long long>(1234567890987654321ULL), 1111111106ULL);
    EXPECT_EQ(arithmetiques::racine_carre<unsigned long long>(15241578750190521ULL), 123456789ULL);
}
