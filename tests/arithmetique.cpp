#include <boost/test/unit_test.hpp>

#include "arithmetique.h"
#include "format/tuple.h"
#include "utilitaires.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_arithmetique)
    struct fixure_arithmetiques {
        std::vector<size_t> premiers;

        explicit fixure_arithmetiques() {
            premiers = std::vector<size_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                           31, 37, 41, 43, 47, 53, 59, 61, 67,
                                           71, 73, 79, 83, 89, 97};
        }

        ~fixure_arithmetiques() = default;
    };

    BOOST_FIXTURE_TEST_CASE(pgcd, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::PGCD(456753ULL, 97643ULL), 1);
        BOOST_CHECK_EQUAL(arithmetique::PGCD(456755ULL, 158665ULL), 65);
    }

    BOOST_FIXTURE_TEST_CASE(ppcm, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::PPCM(456753ULL, 97643ULL), 44598733179ULL);
        BOOST_CHECK_EQUAL(arithmetique::PPCM(456755ULL, 158665ULL), 1114938955);
    }

    BOOST_FIXTURE_TEST_CASE(arrondi, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::arrondi(1000, 101), 10);
        BOOST_CHECK_EQUAL(arithmetique::arrondi(12345678, 48), 257202);
    }

    BOOST_FIXTURE_TEST_CASE(Bezout1, fixure_arithmetiques) {
        long long u, v;
        long long a = 456753LL;
        long long b = 97643LL;
        arithmetique::Bezout(a, b, u, v);

        BOOST_CHECK_EQUAL(u, 18947LL);
        BOOST_CHECK_EQUAL(v, -88630LL);
        BOOST_CHECK_EQUAL(a * u + b * v, 1); // PGCD(a, b) = 1
    }

    BOOST_FIXTURE_TEST_CASE(Bezout2, fixure_arithmetiques) {
        long long u, v;
        long long a = 456755ULL;
        long long b = 158665ULL;
        arithmetique::Bezout(a, b, u, v);

        BOOST_CHECK_EQUAL(u, 602LL);
        BOOST_CHECK_EQUAL(v, -1733LL);
        BOOST_CHECK_EQUAL(a * u + b * v, 65); // PGCD(a, b) = 65
    }


    BOOST_FIXTURE_TEST_CASE(nombre_diviseurs, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::nombre_diviseurs(3246999210ULL, premiers), 640);
    }

    BOOST_FIXTURE_TEST_CASE(somme_diviseurs, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::somme_diviseurs(3246999210ULL, premiers), 11708928000ULL);
        BOOST_CHECK_EQUAL(arithmetique::somme_diviseurs(496ULL, premiers), 992ULL);
    }

    BOOST_FIXTURE_TEST_CASE(decomposition_1, fixure_arithmetiques) {
        std::map<size_t, size_t> decomposition;
        std::map<size_t, size_t> result{{2,  1},
                                        {3,  4},
                                        {5,  1},
                                        {7,  3},
                                        {13, 1},
                                        {29, 1},
                                        {31, 1}};
        arithmetique::decomposition(3246999210ULL, premiers, decomposition);
        BOOST_CHECK_EQUAL_COLLECTIONS(decomposition.begin(), decomposition.end(), result.begin(), result.end());
    }

    BOOST_FIXTURE_TEST_CASE(decomposition_2, fixure_arithmetiques) {
        std::map<size_t, size_t> decomposition;
        std::map<size_t, size_t> result{{2,  4},
                                        {31, 1}};
        arithmetique::decomposition(496ULL, premiers, decomposition);
        BOOST_CHECK_EQUAL_COLLECTIONS(decomposition.begin(), decomposition.end(), result.begin(), result.end());
    }

    BOOST_FIXTURE_TEST_CASE(radical, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::radical(3246999210ULL, premiers), 2454270ULL);
        BOOST_CHECK_EQUAL(arithmetique::radical(496ULL, premiers), 62ULL);
    }

    BOOST_FIXTURE_TEST_CASE(nombre_facteur, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::nombre_facteur(3246999210ULL, 3ULL), 4ULL);
        BOOST_CHECK_EQUAL(arithmetique::nombre_facteur(496ULL, 5ULL), 0ULL);
    }

    BOOST_FIXTURE_TEST_CASE(phi, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::phi(3246999210ULL, premiers), 640120320);
        BOOST_CHECK_EQUAL(arithmetique::phi(496ULL, premiers), 240);
    }

    BOOST_FIXTURE_TEST_CASE(moebius, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::moebius(3246999210ULL, premiers), 0);
        BOOST_CHECK_EQUAL(arithmetique::moebius(496ULL, premiers), 0);
        BOOST_CHECK_EQUAL(arithmetique::moebius(19ULL, premiers), -1);
        BOOST_CHECK_EQUAL(arithmetique::moebius(15ULL, premiers), 1);
    }

    BOOST_FIXTURE_TEST_CASE(facteur_carre, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::facteur_carre(3246999210ULL, premiers), true);
        BOOST_CHECK_EQUAL(arithmetique::facteur_carre(42315ULL, premiers), false);
    }

    BOOST_FIXTURE_TEST_CASE(diviseurs, fixure_arithmetiques) {
        auto d = arithmetique::diviseurs(496ULL, premiers);
        std::vector<size_t> result{1, 2, 4, 8, 16, 31, 62, 124, 248, 496};
        BOOST_CHECK_EQUAL_COLLECTIONS(d.begin(), d.end(), result.begin(), result.end());
    }

    BOOST_FIXTURE_TEST_CASE(repunit, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique::repunit::A(11ULL), 2);
        BOOST_CHECK_EQUAL(arithmetique::repunit::A(3ULL), 3);
        BOOST_CHECK_EQUAL(arithmetique::repunit::A(7ULL), 6);
    }

    BOOST_FIXTURE_TEST_CASE(derivee, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(24ULL, arithmetique::derivee(20ULL, premiers));
        BOOST_CHECK_EQUAL(192ULL, arithmetique::derivee(64ULL, premiers));
        BOOST_CHECK_EQUAL(1ULL, arithmetique::derivee(67ULL, premiers));
        BOOST_CHECK_EQUAL(2916ULL, arithmetique::derivee(1080ULL, premiers));
        BOOST_CHECK_EQUAL(136ULL, arithmetique::derivee(4399ULL, premiers));
        BOOST_CHECK_EQUAL(31424ULL, arithmetique::derivee(8320ULL, premiers));
        BOOST_CHECK_EQUAL(28000ULL, arithmetique::derivee(10000ULL, premiers));
    }

    BOOST_FIXTURE_TEST_CASE(jacobi, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(1, arithmetique::jacobi(20ULL, 16ULL));
        BOOST_CHECK_EQUAL(1, arithmetique::jacobi(64ULL, 13ULL));
        BOOST_CHECK_EQUAL(-1, arithmetique::jacobi(67ULL, 7ULL));
        BOOST_CHECK_EQUAL(0, arithmetique::jacobi(1080ULL, 3ULL));
        BOOST_CHECK_EQUAL(1, arithmetique::jacobi(4399ULL, 9ULL));
        BOOST_CHECK_EQUAL(-1, arithmetique::jacobi(8320ULL, 32156ULL));
        BOOST_CHECK_EQUAL(1, arithmetique::jacobi(10000ULL, 77777ULL));
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
