#include <boost/test/unit_test.hpp>

#include "combinatoire.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_combinatoire)

    BOOST_AUTO_TEST_CASE(coefficient_binomial) {
        BOOST_CHECK_EQUAL(35, combinatoire::coefficient_binomial(7, 3));
        BOOST_CHECK_EQUAL(70, combinatoire::coefficient_binomial(8, 4));
        BOOST_CHECK_EQUAL(1, combinatoire::coefficient_binomial(40, 0));
    }

    BOOST_AUTO_TEST_CASE(catalan) {
        BOOST_CHECK_EQUAL(1, combinatoire::catalan(0));
        BOOST_CHECK_EQUAL(1, combinatoire::catalan(1));
        BOOST_CHECK_EQUAL(16796, combinatoire::catalan<unsigned long long>(10));
    }

    BOOST_AUTO_TEST_CASE(factorielle) {
        BOOST_CHECK_EQUAL(120, combinatoire::factorielle(5));
        BOOST_CHECK_EQUAL(720, combinatoire::factorielle(6));
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
