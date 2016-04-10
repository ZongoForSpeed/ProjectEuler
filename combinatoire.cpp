#include <boost/test/unit_test.hpp>

#include "combinatoire.h"

BOOST_AUTO_TEST_SUITE(test_combinatoire)
    BOOST_AUTO_TEST_CASE(coefficient_binomial)
    {
        BOOST_CHECK_EQUAL(combinatoire::coefficient_binomial(7, 3), 35);
        BOOST_CHECK_EQUAL(combinatoire::coefficient_binomial(8, 4), 70);
        BOOST_CHECK_EQUAL(combinatoire::coefficient_binomial(40, 0), 1);
    }

    BOOST_AUTO_TEST_CASE(factorielle)
    {
        BOOST_CHECK_EQUAL(combinatoire::factorielle(5), 120);
        BOOST_CHECK_EQUAL(combinatoire::factorielle(6), 720);
    }
BOOST_AUTO_TEST_SUITE_END()
