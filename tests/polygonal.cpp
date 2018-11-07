#include <boost/test/unit_test.hpp>

#include "polygonal.h"

BOOST_AUTO_TEST_SUITE(test_polygonal)

    BOOST_AUTO_TEST_CASE(carre) {
        BOOST_CHECK_EQUAL(123456ULL, arithmetique::racine_carre(15241383936ULL));
        BOOST_CHECK(polygonal::est_carre(15241383936ULL));
        BOOST_CHECK(!polygonal::est_carre(15241383935ULL));
    }

    BOOST_AUTO_TEST_CASE(cubique) {
        BOOST_CHECK_EQUAL(12345ULL, arithmetique::racine_cubique(1881365963625ULL));
        BOOST_CHECK(polygonal::est_cubique(1881365963625ULL));
        BOOST_CHECK(!polygonal::est_cubique(1881365963624ULL));
    }

    BOOST_AUTO_TEST_CASE(triangulaire) {
        BOOST_CHECK_EQUAL(5050, polygonal::triangulaire(100));
        BOOST_CHECK(polygonal::est_triangulaire(5050));
        BOOST_CHECK(!polygonal::est_triangulaire(5000));
    }

    BOOST_AUTO_TEST_CASE(pentagonal) {
        BOOST_CHECK_EQUAL(14950, polygonal::pentagonal(100));
        BOOST_CHECK(polygonal::est_pentagonal(3151));
        BOOST_CHECK(!polygonal::est_pentagonal(3150));
    }

    BOOST_AUTO_TEST_CASE(hexagonal) {
        BOOST_CHECK_EQUAL(19900, polygonal::hexagonal(100));
        BOOST_CHECK(polygonal::est_hexagonal(4560));
        BOOST_CHECK(!polygonal::est_hexagonal(4550));
    }

    BOOST_AUTO_TEST_CASE(heptagonal) {
        BOOST_CHECK_EQUAL(24850, polygonal::heptagonal(100));
        BOOST_CHECK(polygonal::est_heptagonal(5688));
        BOOST_CHECK(!polygonal::est_heptagonal(5689));
    }

    BOOST_AUTO_TEST_CASE(octagonal) {
        BOOST_CHECK_EQUAL(29800, polygonal::octagonal(100));
        BOOST_CHECK(polygonal::est_octagonal(5461));
        BOOST_CHECK(!polygonal::est_octagonal(5460));
    }

    BOOST_AUTO_TEST_CASE(somme_carres) {
        BOOST_CHECK_EQUAL(338350, polygonal::somme_carres(100));
        BOOST_CHECK_EQUAL(54301841231, polygonal::somme_carres(5461ll));
        BOOST_CHECK_EQUAL(54272018710, polygonal::somme_carres(5460ll));
    }

    BOOST_AUTO_TEST_CASE(somme_cubes) {
        BOOST_CHECK_EQUAL(25502500, polygonal::somme_cubes(100));
        BOOST_CHECK_EQUAL(222427127548081, polygonal::somme_cubes(5461ll));
        BOOST_CHECK_EQUAL(222264266760900, polygonal::somme_cubes(5460ll));
    }

BOOST_AUTO_TEST_SUITE_END()
