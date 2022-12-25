#include <boost/test/unit_test.hpp>
#include "puissance.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_puissance)

    BOOST_AUTO_TEST_CASE(test_puissance_modulaire) {
        BOOST_CHECK_EQUAL(puissance::puissance_modulaire(2u, 10u, 100u), 24u);
        BOOST_CHECK_EQUAL(puissance::puissance_modulaire<unsigned long long>(97643u, 276799u, 456753u), 368123u);
    }

    BOOST_AUTO_TEST_CASE(test_puissance) {
        BOOST_CHECK_EQUAL(puissance::puissance(2u, 10u), 1024u);
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
