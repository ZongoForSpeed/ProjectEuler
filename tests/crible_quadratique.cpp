#include <boost/test/unit_test.hpp>

#include "utilitaires.h"
#include "mpz_nombre.h"
#include "crible_quadratique.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_crible_quadratique)

    BOOST_AUTO_TEST_CASE(test_pollard_rho) {
        auto rho1 = crible::pollard_rho(8051ul);
        BOOST_CHECK_EQUAL(rho1.has_value(), true);
        BOOST_CHECK_EQUAL(rho1.value(), 97);

        auto rho2 = crible::pollard_rho(32416189909ul);
        BOOST_CHECK_EQUAL(rho2.has_value(), false);

        auto rho3 = crible::pollard_rho(2305843009213693997ull);
        BOOST_CHECK_EQUAL(rho3.has_value(), true);
        BOOST_CHECK_EQUAL(rho3.value(), 128053);

        auto rho4 = crible::pollard_rho(10863617ul);
        BOOST_CHECK_EQUAL(rho4.has_value(), true);
        BOOST_CHECK_EQUAL(rho4.value(), 2213);

        auto rho5 = crible::pollard_rho(6796381ull);
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

        auto rho2 = crible::pollard_brent<size_t>(32416189909);
        BOOST_CHECK_EQUAL(rho2.has_value(), false);

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
        const std::vector<size_t> premiers{
            2, 3, 5, 7, 11, 13, 17, 19, 23,
            29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
            71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
            113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
            173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
            229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
            281, 283, 293, 307, 311, 313, 317, 331, 337, 347,
            349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
            409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
            463, 467, 479, 487, 491, 499, 503, 509, 521, 523,
            541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
            601, 607, 613, 617, 619, 631, 641, 643, 647, 653,
            659, 661, 673, 677, 683, 691, 701, 709, 719, 727,
            733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
            809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
            863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
            941, 947, 953, 967, 971, 977, 983, 991, 997
        };
        auto facteurs1 = crible::facteurs_premiers<size_t>(8051, premiers);
        const std::deque<size_t> resultats1{83, 97};
        BOOST_CHECK_EQUAL(resultats1, facteurs1);

        auto facteurs2 = crible::facteurs_premiers<size_t>(32416189909, premiers);
        const std::deque<size_t> resultats2{32416189909};
        BOOST_CHECK_EQUAL(resultats2, facteurs2);

        auto facteurs3 = crible::facteurs_premiers<unsigned long long>(2305843009213693997, premiers);
        const std::deque<unsigned long long> resultats3{128053, 18006942509849};
        BOOST_CHECK_EQUAL(resultats3, facteurs3);
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
