#include <boost/test/unit_test.hpp>

#include "polynome.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_polynome)

    BOOST_AUTO_TEST_CASE(initialization_1) {
        Polynome<long long> p(10);
        BOOST_CHECK_EQUAL(p.taille(), 1);
        BOOST_CHECK_EQUAL(p.valeur(42), 10);
    }

    BOOST_AUTO_TEST_CASE(initialization_2) {
        Polynome<long long> p{-1, 0, 1};
        BOOST_CHECK_EQUAL(p.taille(), 3);
        BOOST_CHECK_EQUAL(p.valeur(2), 3);
    }

    BOOST_AUTO_TEST_CASE(comparaison) {
        Polynome<long long> p{-1, 0, 1};
        Polynome<long long> q{-1, 0, 1};
        Polynome<long long> r{1, 0, 1};
        BOOST_CHECK_EQUAL(p, q);
        BOOST_CHECK_NE(p, r);
    }

    BOOST_AUTO_TEST_CASE(addition) {
        Polynome<long long> p{-1, 0, 1};
        Polynome<long long> q{0, 1};
        Polynome<long long> r{-1, 1, 1};
        BOOST_CHECK_EQUAL(p + q, r);
    }

    BOOST_AUTO_TEST_CASE(soustraction) {
        Polynome<long long> p{-1, 1, 1};
        Polynome<long long> q{0, 0, 1};
        Polynome<long long> r{-1, 1};
        BOOST_CHECK_EQUAL(p - q, r);
    }

    BOOST_AUTO_TEST_CASE(multiplication) {
        Polynome<long long> p{1, -1, 1, -1, 1};
        Polynome<long long> q{1, 1,};
        Polynome<long long> r{1, 0, 0, 0, 0, 1};
        BOOST_CHECK_EQUAL(p * q, r);
    }

    BOOST_AUTO_TEST_CASE(affiche_1) {
        Polynome<long long> p{1, -1, 1, -1, 1};
        std::ostringstream oss;
        oss << p;
        BOOST_CHECK_EQUAL(oss.str(), "X^4 - X^3 + X^2 - X + 1");
    }

    BOOST_AUTO_TEST_CASE(affiche_2) {
        Polynome<long long> p{1, 1,};
        std::ostringstream oss;
        oss << p;
        BOOST_CHECK_EQUAL(oss.str(), "X + 1");
    }

    BOOST_AUTO_TEST_CASE(affiche_3) {
        Polynome<long long> p{1, 0, 0, 0, 0, 1};
        std::ostringstream oss;
        oss << p;
        BOOST_CHECK_EQUAL(oss.str(), "X^5 + 1");
    }

    BOOST_AUTO_TEST_CASE(division_euclidienne_1) {
        Polynome<long long> A{0, -2, 3, -1, -1, 1};
        Polynome<long long> B{1, -1, 1};


        Polynome<long long> Q;
        Polynome<long long> R;
        Polynome<long long>::division_euclidienne(A, B, Q, R);

        Polynome<long long> Q1{1, -2, 0, 1};
        Polynome<long long> R1{-1, 1};

        BOOST_CHECK_EQUAL(Q, Q1);
        BOOST_CHECK_EQUAL(R, R1);
    }

    BOOST_AUTO_TEST_CASE(division_euclidienne_2) {
        Polynome<long long> A{-1, 0, 0, 0, 0, 0, 0, 1};
        Polynome<long long> B{-1, 1};

        Polynome<long long> Q;
        Polynome<long long> R;

        Polynome<long long>::division_euclidienne(A, B, Q, R);
        Polynome<long long> Q1{1, 1, 1, 1, 1, 1, 1};
        Polynome<long long> R1;

        BOOST_CHECK_EQUAL(Q, Q1);
        BOOST_CHECK_EQUAL(R, R1);
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
