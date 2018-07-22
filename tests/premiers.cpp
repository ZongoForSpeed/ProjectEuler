#include <boost/test/unit_test.hpp>
#include <deque>
#include <numeric>

#include "premiers.h"

/*
 * namespace {
    bool MillerRabin(nombre n, size_t k) {
        nombre d = n - 1;
        size_t r = 0;
        while (d % 2 == 0) {
            d /= 2;
            ++r;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<nombre> dis(2, n - 2);

        while (k > 0) {
            --k;

            nombre a = dis(gen);
            nombre x = puissance::puissance_modulaire(a, d, n);
            if (x == 1 || x == n - 1)
                continue;

            for (size_t i = 0; i < r; ++i) {
                x = (x * x) % n;
                if (x == 1) {
                    return false;
                } else if (x == n - 1)
                    break;
            }

            if (x != n - 1)
                return false;
        }

        return true;
    }
}
 */

BOOST_AUTO_TEST_SUITE(test_premiers)

    BOOST_AUTO_TEST_CASE(crible) {
        const std::vector<size_t> premiers100{2, 3, 5, 7, 11, 13, 17, 19, 23,
                                              29, 31, 37, 41, 43, 47, 53, 59,
                                              61, 67, 71, 73, 79, 83, 89, 97};
        std::deque<size_t> resultat;
        premiers::crible2<size_t>(100ULL, std::back_inserter(resultat));
        BOOST_CHECK_EQUAL_COLLECTIONS(premiers100.begin(), premiers100.end(), resultat.begin(), resultat.end());
    }

    BOOST_AUTO_TEST_CASE(crible23) {
        std::deque<size_t> resultat;
        premiers::crible23<size_t>(10000ULL, std::back_inserter(resultat));

        BOOST_CHECK_EQUAL(resultat.at(1), 3);
        BOOST_CHECK_EQUAL(resultat.at(2), 5);
        BOOST_CHECK_EQUAL(resultat.at(100), 547);
        BOOST_CHECK_EQUAL(resultat.at(1000), 7927);
    }

    BOOST_AUTO_TEST_CASE(crible235) {
        std::deque<size_t> resultat;
        premiers::crible235<size_t>(2'000'000ULL, std::back_inserter(resultat));

        BOOST_CHECK_EQUAL(resultat.at(1), 3);
        BOOST_CHECK_EQUAL(resultat.at(2), 5);
        BOOST_CHECK_EQUAL(resultat.at(100), 547);
        BOOST_CHECK_EQUAL(resultat.at(1000), 7927);
        BOOST_CHECK_EQUAL(resultat.at(10000), 104743);
        BOOST_CHECK_EQUAL(resultat.at(50000), 611957);
        BOOST_CHECK_EQUAL(resultat.at(100000), 1299721);
    }

    BOOST_AUTO_TEST_CASE(crible_simple) {
        const std::vector<size_t> premiers100{2, 3, 5, 7, 11, 13, 17, 19, 23,
                                              29, 31, 37, 41, 43, 47, 53, 59,
                                              61, 67, 71, 73, 79, 83, 89, 97};
        std::vector<bool> crible;
        premiers::crible_simple(100, crible);

        BOOST_CHECK_EQUAL(100, crible.size());

        for (auto p: premiers100) {
            BOOST_CHECK(crible[p]);
        }

        size_t compteur = std::accumulate(crible.begin(), crible.end(), 0ul);
        BOOST_CHECK_EQUAL(25, compteur);
    }

BOOST_AUTO_TEST_SUITE_END()
