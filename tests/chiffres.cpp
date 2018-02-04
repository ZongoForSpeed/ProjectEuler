#include <boost/test/unit_test.hpp>

#include "chiffres.h"

BOOST_AUTO_TEST_SUITE(test_chiffres)

    BOOST_AUTO_TEST_CASE(nombre_chiffres) {
        BOOST_CHECK_EQUAL(9, chiffres::nombre_chiffres(123456789ULL));
    }

    BOOST_AUTO_TEST_CASE(somme_chiffres) {
        BOOST_CHECK_EQUAL(45, chiffres::somme_chiffres(123456789ULL));
    }

    BOOST_AUTO_TEST_CASE(extraire_chiffres) {
        auto c = chiffres::extraire_chiffres(123456789ULL);
        std::deque<size_t> r{1, 2, 3, 4, 5, 6, 7, 8, 9};
        BOOST_CHECK_EQUAL_COLLECTIONS(c.begin(), c.end(), r.begin(), r.end());
    }

    BOOST_AUTO_TEST_CASE(palindrome) {
        BOOST_CHECK_EQUAL(false, chiffres::palindrome(123456789ULL));
        BOOST_CHECK_EQUAL(true, chiffres::palindrome(123454321ULL));
    }

    BOOST_AUTO_TEST_CASE(pandigital) {
        BOOST_CHECK_EQUAL(true, chiffres::pandigital(123456789ULL));
        BOOST_CHECK_EQUAL(false, chiffres::pandigital(1234567890ULL));
        BOOST_CHECK_EQUAL(false, chiffres::pandigital(123454321ULL));
    }

    BOOST_AUTO_TEST_CASE(conversion_nombre) {
        std::deque<size_t> c{1, 2, 3, 4, 5, 6, 7, 8, 9};
        BOOST_CHECK_EQUAL(123456789ULL, chiffres::conversion_nombre<size_t>(c.begin(), c.end()));
    }

    BOOST_AUTO_TEST_CASE(permutation_chiffres) {
        BOOST_CHECK_EQUAL(true, chiffres::permutation_chiffres(123456789ULL, 918273645ULL));
        BOOST_CHECK_EQUAL(true, chiffres::permutation_chiffres(123ULL, 1234ULL));
    }

    BOOST_AUTO_TEST_CASE(inverser_nombre) {
        BOOST_CHECK_EQUAL(987654321ULL, chiffres::inverser_nombre(123456789ULL));
    }

    BOOST_AUTO_TEST_CASE(concatener) {
        BOOST_CHECK_EQUAL(123456789ULL, chiffres::concatener(12ULL, 3456789ULL));
        BOOST_CHECK_EQUAL(123456789ULL, chiffres::concatener(12ULL, 345ULL, 6789ULL));
        BOOST_CHECK_EQUAL(123456789ULL, chiffres::concatener(12ULL, 34ULL, 567ULL, 89ULL));
    }

BOOST_AUTO_TEST_SUITE_END()
