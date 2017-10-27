#include <boost/test/unit_test.hpp>

#include "polygonal.h"
#include "arithmetiques.h"

BOOST_AUTO_TEST_SUITE(test_polygonal)
    BOOST_AUTO_TEST_CASE(carre)
    {
        BOOST_CHECK_EQUAL(arithmetiques::racine_carre(15241383936ULL), 123456ULL);
        BOOST_CHECK_EQUAL(polygonal::est_carre(15241383936ULL), true);
        BOOST_CHECK_EQUAL(polygonal::est_carre(15241383935ULL), false);
    }
    
    BOOST_AUTO_TEST_CASE(cubique)
    {
        BOOST_CHECK_EQUAL(arithmetiques::racine_cubique(1881365963625ULL), 12345ULL);
        BOOST_CHECK_EQUAL(polygonal::est_cubique(1881365963625ULL), true);
        BOOST_CHECK_EQUAL(polygonal::est_cubique(1881365963624ULL), false);
    }
    
    BOOST_AUTO_TEST_CASE(triangulaire)
    {
        BOOST_CHECK_EQUAL(polygonal::triangulaire(100), 5050);
        BOOST_CHECK_EQUAL(polygonal::est_triangulaire(5050), true);
        BOOST_CHECK_EQUAL(polygonal::est_triangulaire(5000), false);
    }
    
    BOOST_AUTO_TEST_CASE(pentagonal)
    {
        BOOST_CHECK_EQUAL(polygonal::pentagonal(100), 14950);
        BOOST_CHECK_EQUAL(polygonal::est_pentagonal(3151), true);
        BOOST_CHECK_EQUAL(polygonal::est_pentagonal(3150), false);
    }
    
    BOOST_AUTO_TEST_CASE(hexagonal)
    {
        BOOST_CHECK_EQUAL(polygonal::hexagonal(100), 19900);
        BOOST_CHECK_EQUAL(polygonal::est_hexagonal(4560), true);
        BOOST_CHECK_EQUAL(polygonal::est_hexagonal(4550), false);
    }
    
    BOOST_AUTO_TEST_CASE(heptagonal)
    {
        BOOST_CHECK_EQUAL(polygonal::heptagonal(100), 24850);
        BOOST_CHECK_EQUAL(polygonal::est_heptagonal(5688), true);
        BOOST_CHECK_EQUAL(polygonal::est_heptagonal(5689), false);
    }
    
    BOOST_AUTO_TEST_CASE(octagonal)
    {
        BOOST_CHECK_EQUAL(polygonal::octagonal(100), 29800);
        BOOST_CHECK_EQUAL(polygonal::est_octagonal(5461), true);
        BOOST_CHECK_EQUAL(polygonal::est_octagonal(5460), false);
    }
BOOST_AUTO_TEST_SUITE_END()
