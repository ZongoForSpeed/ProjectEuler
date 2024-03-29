#include <boost/test/unit_test.hpp>

#include "numerique.h"
#include "combinatoire.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

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

    BOOST_AUTO_TEST_CASE(numeric_limits_int128) {
        BOOST_CHECK_EQUAL("170141183460469231731687303715884105727",
                          std::to_string(std::numeric_limits<int128_t>::max()));

        BOOST_CHECK_EQUAL("-170141183460469231731687303715884105728",
                          std::to_string(std::numeric_limits<int128_t>::min()));
    }

    BOOST_AUTO_TEST_CASE(numeric_limits_uint128) {
        BOOST_CHECK_EQUAL("340282366920938463463374607431768211455",
                          std::to_string(std::numeric_limits<uint128_t>::max()));

        BOOST_CHECK_EQUAL(0,
                          std::numeric_limits<uint128_t>::min());
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
