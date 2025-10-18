#include <boost/test/unit_test.hpp>

#include "combinatoire.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_combinatoire)

    BOOST_AUTO_TEST_CASE(coefficient_binomial) {
        BOOST_CHECK_EQUAL(35, combinatoire::coefficient_binomial_u(7u, 3u));
        BOOST_CHECK_EQUAL(70, combinatoire::coefficient_binomial_u(8u, 4u));
        BOOST_CHECK_EQUAL(1, combinatoire::coefficient_binomial_u(40u, 0u));
    }

    BOOST_AUTO_TEST_CASE(catalan) {
        BOOST_CHECK_EQUAL(1, combinatoire::catalan_u(0u));
        BOOST_CHECK_EQUAL(1, combinatoire::catalan_u(1u));
        BOOST_CHECK_EQUAL(16796, combinatoire::catalan_ull(10ull));
    }

    BOOST_AUTO_TEST_CASE(factorielle) {
        BOOST_CHECK_EQUAL(120, combinatoire::factorielle_u(5u));
        BOOST_CHECK_EQUAL(720, combinatoire::factorielle_u(6u));
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
