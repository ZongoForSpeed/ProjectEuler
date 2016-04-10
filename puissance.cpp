#include <boost/test/unit_test.hpp>

#include "puissance.h"

BOOST_AUTO_TEST_SUITE(test_puissance)
    BOOST_AUTO_TEST_CASE(test_puissance_modulaire)
    {
        BOOST_CHECK_EQUAL(puissance::puissance_modulaire(2, 10, 100), 24);
    }

    BOOST_AUTO_TEST_CASE(test_puissance)
    {
        BOOST_CHECK_EQUAL(puissance::puissance(2, 10), 1024);
    }
BOOST_AUTO_TEST_SUITE_END()
