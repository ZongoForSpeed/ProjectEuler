#include <boost/test/unit_test.hpp>

#include "utilitaires.h"

BOOST_AUTO_TEST_SUITE(test_utilitaires)
    BOOST_AUTO_TEST_CASE(racine)
    {
        BOOST_CHECK_EQUAL(racine_carre<unsigned long long>(123456789ULL), 11111ULL);
        BOOST_CHECK_EQUAL(racine_carre<unsigned long long>(1234567890987654321ULL), 1111111106ULL);
        BOOST_CHECK_EQUAL(racine_carre<unsigned long long>(15241578750190521ULL), 123456789ULL);
    }
BOOST_AUTO_TEST_SUITE_END()
