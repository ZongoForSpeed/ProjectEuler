#include <boost/test/unit_test.hpp>

#include "nombre_modulaire.h"
#include "utilitaires.h"

BOOST_AUTO_TEST_SUITE(test_nombre_modulaires)

    BOOST_AUTO_TEST_CASE(coefficient_binomial) {
        size_t n = 1'000'000'000'000'000'000ull;
        size_t k = 1'000'000'000ull;
        nombre_modulaire Cnk = nombre_modulaire::coefficient_binomial(4999, n, k);

        BOOST_CHECK_EQUAL("2982[4999]", std::to_string(Cnk));
    }

    BOOST_AUTO_TEST_CASE(factoriel_1) {
        nombre_modulaire factoriel = nombre_modulaire::factoriel(4999, 5000);
        BOOST_CHECK_EQUAL("0[4999]", std::to_string(factoriel));
    }

    BOOST_AUTO_TEST_CASE(factoriel_2) {
        nombre_modulaire factoriel = nombre_modulaire::factoriel(4999, 1234);
        BOOST_CHECK_EQUAL("3912[4999]", std::to_string(factoriel));
    }

BOOST_AUTO_TEST_SUITE_END()
