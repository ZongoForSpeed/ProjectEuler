#define BOOST_TEST_MODULE Project Euler
#include <boost/test/included/unit_test.hpp>

#include "arithmetiques.h"
#include "chiffres.h"
#include "combinatoire.h"
#include "puissance.h"

#include "utilitaires.h"

BOOST_AUTO_TEST_SUITE(test_arithmetiques)
    BOOST_AUTO_TEST_CASE(pgcd)
    {
        BOOST_CHECK_EQUAL(arithmetiques::PGCD(456753ULL, 97643ULL), 1);
        BOOST_CHECK_EQUAL(arithmetiques::PGCD(456755ULL, 158665ULL), 65);
    }
    
    BOOST_AUTO_TEST_CASE(ppcm)
    {
        BOOST_CHECK_EQUAL(arithmetiques::PPCM(456753ULL, 97643ULL), 44598733179ULL);
        BOOST_CHECK_EQUAL(arithmetiques::PPCM(456755ULL, 158665ULL), 1114938955);
    }
    
    struct fixure_arithmetiques
    {
        std::vector<size_t> premiers; 
        
        fixure_arithmetiques()
        {
            premiers = std::vector<size_t> { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                             31, 37, 41, 43, 47, 53, 59, 61, 67, 
                                             71, 73, 79, 83, 89, 97};
        }
    };
    
    BOOST_FIXTURE_TEST_CASE(nombre_diviseurs, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::nombre_diviseurs(3246999210ULL, premiers), 640);
    }
    
    BOOST_FIXTURE_TEST_CASE(somme_diviseurs, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::somme_diviseurs(3246999210ULL, premiers), 11708928000ULL);
        BOOST_CHECK_EQUAL(arithmetiques::somme_diviseurs(496ULL, premiers), 992ULL);
    }
    
    BOOST_FIXTURE_TEST_CASE(decomposition, fixure_arithmetiques)
    {
        std::map<size_t, size_t> d1;
        std::map<size_t, size_t> result1 { {2, 1}, {3, 4}, {5, 1}, {7, 3}, {13, 1}, {29, 1}, {31, 1} };
        arithmetiques::decomposition(3246999210ULL, premiers, d1);
        BOOST_CHECK_EQUAL_COLLECTIONS(d1.begin(), d1.end(), result1.begin(), result1.end());
        
        std::map<size_t, size_t> d2;
        std::map<size_t, size_t> result2 { {2, 4}, {31, 1} };
        arithmetiques::decomposition(496ULL, premiers, d2);
        BOOST_CHECK_EQUAL_COLLECTIONS(d2.begin(), d2.end(), result2.begin(), result2.end());
    }
    
    BOOST_FIXTURE_TEST_CASE(radical, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::radical(3246999210ULL, premiers), 2454270ULL);
        BOOST_CHECK_EQUAL(arithmetiques::radical(496ULL, premiers), 62ULL);
    }
    
    BOOST_FIXTURE_TEST_CASE(nombre_facteur, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::nombre_facteur(3246999210ULL, 3ULL), 4ULL);
        BOOST_CHECK_EQUAL(arithmetiques::nombre_facteur(496ULL, 5ULL), 0ULL);
    }
    
    BOOST_FIXTURE_TEST_CASE(phi, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::phi(3246999210ULL, premiers), 640120320);
        BOOST_CHECK_EQUAL(arithmetiques::phi(496ULL, premiers), 240);
    }
    
    BOOST_FIXTURE_TEST_CASE(moebius, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::moebius(3246999210ULL, premiers), 0);
        BOOST_CHECK_EQUAL(arithmetiques::moebius(496ULL, premiers), 0);
        BOOST_CHECK_EQUAL(arithmetiques::moebius(19ULL, premiers), -1);
        BOOST_CHECK_EQUAL(arithmetiques::moebius(15ULL, premiers), 1);
    }
    
    BOOST_FIXTURE_TEST_CASE(facteur_carre, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::facteur_carre(3246999210ULL, premiers), true);
        BOOST_CHECK_EQUAL(arithmetiques::facteur_carre(42315ULL, premiers), false);
    }
    
    BOOST_FIXTURE_TEST_CASE(diviseurs, fixure_arithmetiques)
    {
        auto d = arithmetiques::diviseurs(496ULL, premiers);
        std::vector<size_t> result {1, 2, 4, 8, 16, 31, 62, 124, 248, 496};
        BOOST_CHECK_EQUAL_COLLECTIONS(d.begin(), d.end(), result.begin(), result.end());
    }
    
    BOOST_FIXTURE_TEST_CASE(repunit, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::repunit::A(11ULL), 2);
        BOOST_CHECK_EQUAL(arithmetiques::repunit::A(3ULL), 3);
        BOOST_CHECK_EQUAL(arithmetiques::repunit::A(7ULL), 6);
    }
    
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_chiffres)
    BOOST_AUTO_TEST_CASE(nombre_chiffres)
    {
        BOOST_CHECK_EQUAL(chiffres::nombre_chiffres(123456789ULL), 9);
    }
    
    BOOST_AUTO_TEST_CASE(somme_chiffres)
    {
        BOOST_CHECK_EQUAL(chiffres::somme_chiffres(123456789ULL), 45);
    }
    
    BOOST_AUTO_TEST_CASE(extraire_chiffres)
    {
        auto c = chiffres::extraire_chiffres(123456789ULL);
        std::deque<size_t> r {1, 2, 3, 4, 5, 6, 7, 8, 9};
        BOOST_CHECK_EQUAL_COLLECTIONS( c.begin(), c.end(), r.begin(), r.end());
    }
    
    BOOST_AUTO_TEST_CASE(palindrome)
    {
        BOOST_CHECK_EQUAL(chiffres::palindrome(123456789ULL), false);
        BOOST_CHECK_EQUAL(chiffres::palindrome(123454321ULL), true);
    }
    
    BOOST_AUTO_TEST_CASE(pandigital)
    {
        BOOST_CHECK_EQUAL(chiffres::pandigital(123456789ULL), true);
        BOOST_CHECK_EQUAL(chiffres::pandigital(1234567890ULL), false);
        BOOST_CHECK_EQUAL(chiffres::pandigital(123454321ULL), false);
    }
    
    BOOST_AUTO_TEST_CASE(conversion_nombre)
    {
        std::deque<size_t> c {1, 2, 3, 4, 5, 6, 7, 8, 9};
        BOOST_CHECK_EQUAL(chiffres::conversion_nombre<size_t>(c.begin(), c.end()), 123456789ULL);
    }
    
    BOOST_AUTO_TEST_CASE(permutation_chiffres)
    {
        BOOST_CHECK_EQUAL(chiffres::permutation_chiffres(123456789ULL, 918273645ULL), true);
        BOOST_CHECK_EQUAL(chiffres::permutation_chiffres(123ULL, 1234ULL), true);
    }
    
    BOOST_AUTO_TEST_CASE(inverser_nombre)
    {
        BOOST_CHECK_EQUAL(chiffres::inverser_nombre(123456789ULL), 987654321ULL);
    }
    
    BOOST_AUTO_TEST_CASE(concatener)
    {
        BOOST_CHECK_EQUAL(chiffres::concatener(12ULL, 3456789ULL), 123456789ULL);
        BOOST_CHECK_EQUAL(chiffres::concatener(12ULL, 345ULL, 6789ULL), 123456789ULL);
        BOOST_CHECK_EQUAL(chiffres::concatener(12ULL, 34ULL, 567ULL, 89ULL), 123456789ULL);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_combinatoire)
    BOOST_AUTO_TEST_CASE(coefficient_binomial)
    {
        BOOST_CHECK_EQUAL(combinatoire::coefficient_binomial(7, 3), 35);
        BOOST_CHECK_EQUAL(combinatoire::coefficient_binomial(8, 4), 70);
        BOOST_CHECK_EQUAL(combinatoire::coefficient_binomial(40, 0), 1);
    }
    
    BOOST_AUTO_TEST_CASE(factorielle)
    {
        BOOST_CHECK_EQUAL(combinatoire::factorielle(5), 120);
        BOOST_CHECK_EQUAL(combinatoire::factorielle(6), 720);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_puissance)
    BOOST_AUTO_TEST_CASE(test_puissance_modulaire)
    {
        BOOST_CHECK_EQUAL(puissance::puissance_modulaire(2, 10, 100), 24);
        
    }
    
    BOOST_AUTO_TEST_CASE(test_puissance)
    {
        BOOST_CHECK_EQUAL(puissance::puissance(2, 10), 1024);
    }
BOOST_AUTO_TEST_SUITE_END()

