#include <boost/test/unit_test.hpp>
#include "puissance.h"

BOOST_AUTO_TEST_SUITE(test_puissance)

    BOOST_AUTO_TEST_CASE(test_puissance_modulaire) {
        BOOST_CHECK_EQUAL(puissance::puissance_modulaire(2u, 10u, 100u), 24u);
        BOOST_CHECK_EQUAL(puissance::puissance_modulaire<unsigned long long>(97643, 276799u, 456753), 368123);
    }

    BOOST_AUTO_TEST_CASE(test_puissance) {
        BOOST_CHECK_EQUAL(puissance::puissance(2u, 10u), 1024u);
    }

BOOST_AUTO_TEST_SUITE_END()
