#include <boost/test/unit_test.hpp>

#include "mpz_nombre.h"
#include "crible_quadratique.h"

BOOST_AUTO_TEST_SUITE(test_crible_quadratique)

    BOOST_AUTO_TEST_CASE(test_pollard_rho) {

        auto rho1 = crible::pollard_rho<size_t>(8051);
        BOOST_CHECK_EQUAL(rho1.has_value(), true);
        BOOST_CHECK_EQUAL(rho1.value(), 97);

        auto rho2 = crible::pollard_rho<size_t>(32416189909);
        BOOST_CHECK_EQUAL(rho2.has_value(), false);

        auto rho3 = crible::pollard_rho<mpz_nombre>(2305843009213693997);
        BOOST_CHECK_EQUAL(rho3.has_value(), true);
        BOOST_CHECK_EQUAL(rho3.value(), 128053);

        auto rho4 = crible::pollard_rho<size_t>(10863617);
        BOOST_CHECK_EQUAL(rho4.has_value(), true);
        BOOST_CHECK_EQUAL(rho4.value(), 2213);

        auto rho5 = crible::pollard_rho<size_t>(6796381);
        BOOST_CHECK_EQUAL(rho5.has_value(), true);
        BOOST_CHECK_EQUAL(rho5.value(), 1753);

        // auto rho6 = crible::pollard_rho<size_t>(6785153);
        // BOOST_CHECK_EQUAL(rho6.has_value(), true);
        // BOOST_CHECK_EQUAL(rho6.value(), 1753);

        // 6785153
        // 6796381
    }

    /*
    BOOST_AUTO_TEST_CASE(test_pollard_brent) {

        auto rho1 = crible::pollard_brent<size_t>(8051);
        BOOST_CHECK_EQUAL(rho1.has_value(), true);
        BOOST_CHECK_EQUAL(rho1.value(), 83);

        // auto rho2 = crible::pollard_brent<size_t>(32416189909);
        // BOOST_CHECK_EQUAL(rho2.has_value(), false);

        // auto rho3 = crible::pollard_brent<mpz_nombre>(2305843009213693997);
        // BOOST_CHECK_EQUAL(rho3.has_value(), true);
        // BOOST_CHECK_EQUAL(rho3.value(), 128053);

        auto rho4 = crible::pollard_brent<size_t>(10863617);
        BOOST_CHECK_EQUAL(rho4.has_value(), true);
        BOOST_CHECK_EQUAL(rho4.value(), 2213);

        auto rho5 = crible::pollard_brent<size_t>(6796381);
        BOOST_CHECK_EQUAL(rho5.has_value(), true);
        BOOST_CHECK_EQUAL(rho5.value(), 1753);

        auto rho6 = crible::pollard_brent<size_t>(6785153);
        BOOST_CHECK_EQUAL(rho6.has_value(), true);
        BOOST_CHECK_EQUAL(rho6.value(), 1609);

        // 6785153
        // 6796381
    }
    */

    BOOST_AUTO_TEST_CASE(test_facteurs_premiers) {
        auto facteurs1 = crible::facteurs_premiers<size_t>(8051);
        const std::deque<size_t> resultats1{83, 97};
        BOOST_CHECK_EQUAL(resultats1, facteurs1);

        auto facteurs2 = crible::facteurs_premiers<size_t>(32416189909);
        const std::deque<size_t> resultats2{32416189909};
        BOOST_CHECK_EQUAL(resultats2, facteurs2);

        // auto facteurs3 = crible::facteurs_premiers<mpz_nombre>(2305843009213693997);
        // const std::deque<mpz_nombre> resultats3{128053, 18006942509849};
        // BOOST_CHECK_EQUAL(resultats3, facteurs3);
    }

BOOST_AUTO_TEST_SUITE_END()
