#include <boost/test/unit_test.hpp>

#include "arithmetiques.h"
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
    
    BOOST_AUTO_TEST_CASE(arrondi)
    {
        BOOST_CHECK_EQUAL(arithmetiques::arrondi(1000, 101), 10);
        BOOST_CHECK_EQUAL(arithmetiques::arrondi(12345678, 48), 257202);
    }
    
    BOOST_AUTO_TEST_CASE(Bezout1)
    {
        long long u, v;
        long long a = 456753LL;
        long long b = 97643LL;
        arithmetiques::Bezout(a, b, u, v);
        
        BOOST_CHECK_EQUAL(u, 18947LL);
        BOOST_CHECK_EQUAL(v, -88630LL);
        BOOST_CHECK_EQUAL(a*u + b*v, 1); // PGCD(a, b) = 1
    }

    BOOST_AUTO_TEST_CASE(Bezout2)
    {
        long long u, v;
        long long a = 456755ULL;
        long long b = 158665ULL;
        arithmetiques::Bezout(a, b, u, v);
        
        BOOST_CHECK_EQUAL(u, 602LL);
        BOOST_CHECK_EQUAL(v, -1733LL);
        BOOST_CHECK_EQUAL(a*u + b*v, 65); // PGCD(a, b) = 65
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

    BOOST_FIXTURE_TEST_CASE(decomposition_1, fixure_arithmetiques)
    {
		std::map<size_t, size_t> decomposition;
		std::map<size_t, size_t> result { {2, 1}, {3, 4}, {5, 1}, {7, 3}, {13, 1}, {29, 1}, {31, 1} };
		arithmetiques::decomposition(3246999210ULL, premiers, decomposition);
		BOOST_CHECK_EQUAL_COLLECTIONS(decomposition.begin(), decomposition.end(), result.begin(), result.end());
    }

    BOOST_FIXTURE_TEST_CASE(decomposition_2, fixure_arithmetiques)
	{
		std::map<size_t, size_t> decomposition;
		std::map<size_t, size_t> result { {2, 4}, {31, 1} };
		arithmetiques::decomposition(496ULL, premiers, decomposition);
		BOOST_CHECK_EQUAL_COLLECTIONS(decomposition.begin(), decomposition.end(), result.begin(), result.end());
	}

    BOOST_FIXTURE_TEST_CASE(radical, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::radical(3246999210ULL, premiers), 2454270ULL);
        BOOST_CHECK_EQUAL(arithmetiques::radical(496ULL, premiers), 62ULL);
    }

    BOOST_AUTO_TEST_CASE(nombre_facteur)
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

    BOOST_AUTO_TEST_CASE(repunit)
    {
        BOOST_CHECK_EQUAL(arithmetiques::repunit::A(11ULL), 2);
        BOOST_CHECK_EQUAL(arithmetiques::repunit::A(3ULL), 3);
        BOOST_CHECK_EQUAL(arithmetiques::repunit::A(7ULL), 6);
    }

    BOOST_FIXTURE_TEST_CASE(inverse, fixure_arithmetiques)
    {
        BOOST_CHECK_EQUAL(arithmetiques::inverse_modulaire<unsigned long>(3, 11, premiers), 4);
        BOOST_CHECK_EQUAL(arithmetiques::inverse_modulaire<unsigned long>(97643, 456753, premiers), 368123);
        BOOST_CHECK_EQUAL(arithmetiques::inverse_modulaire<unsigned long long>(107113, 3246999210ULL, premiers), 180730717ULL);
    }
    
    BOOST_FIXTURE_TEST_CASE(chinois1, fixure_arithmetiques)
    {
        std::vector<unsigned long> modulos { 3, 5, 7 };
        std::vector<unsigned long> restes { 2, 3, 2 };
        
        auto reste = arithmetiques::restes_chinois<unsigned long>(modulos, restes, premiers);
        BOOST_CHECK_EQUAL(reste, 23);
    }
    
    BOOST_FIXTURE_TEST_CASE(chinois2, fixure_arithmetiques)
    {
        std::vector<unsigned long> modulos { 3, 4, 5 };
        std::vector<unsigned long> restes { 2, 3, 1 };
        
        auto reste = arithmetiques::restes_chinois<unsigned long>(modulos, restes, premiers);
        BOOST_CHECK_EQUAL(reste, 11);
    }
    
        
    BOOST_AUTO_TEST_CASE(racine)
    {
        BOOST_CHECK_EQUAL(arithmetiques::racine_carre<unsigned long long>(123456789ULL), 11111ULL);
        BOOST_CHECK_EQUAL(arithmetiques::racine_carre<unsigned long long>(1234567890987654321ULL), 1111111106ULL);
        BOOST_CHECK_EQUAL(arithmetiques::racine_carre<unsigned long long>(15241578750190521ULL), 123456789ULL);
    }
BOOST_AUTO_TEST_SUITE_END()
