#include <boost/test/unit_test.hpp>

#include "numerique.h"
#include "combinatoire.h"

BOOST_AUTO_TEST_SUITE(test_numerique)

    BOOST_AUTO_TEST_CASE(ostringstream_signed) {
        auto f = combinatoire::factorielle<int128_t>(30);
        std::ostringstream oss;
        oss << f;
        BOOST_CHECK_EQUAL("265252859812191058636308480000000", oss.str());

        int128_t n;
        std::istringstream iss(oss.str());
        iss >> n;
        BOOST_CHECK_EQUAL(n, f);

        std::ostringstream oss2;
        oss2 << -f;
        BOOST_CHECK_EQUAL("-265252859812191058636308480000000", oss2.str());

        int128_t n2;
        std::istringstream iss2(oss2.str());
        iss2 >> n2;
        BOOST_CHECK_EQUAL(n2, -f);

    }

    BOOST_AUTO_TEST_CASE(ostringstream_unsigned) {
        auto f = combinatoire::factorielle<uint128_t>(30);
        std::ostringstream oss;
        oss << f;
        BOOST_CHECK_EQUAL("265252859812191058636308480000000", oss.str());

        uint128_t n;
        std::istringstream iss(oss.str());
        iss >> n;
        BOOST_CHECK_EQUAL(n, f);
    }

BOOST_AUTO_TEST_SUITE_END()
