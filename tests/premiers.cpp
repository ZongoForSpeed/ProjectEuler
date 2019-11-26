#include <boost/test/unit_test.hpp>
#include <deque>

#include "premiers.h"

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

    BOOST_AUTO_TEST_CASE(miller_rabin) {
        boost::multiprecision::cpp_int n("32416189721");
        BOOST_CHECK(premiers::miller_rabin<boost::multiprecision::cpp_int>(n, 25));
        BOOST_CHECK_EQUAL(false, premiers::miller_rabin<boost::multiprecision::cpp_int>(n + 44, 25));

        boost::multiprecision::cpp_int m("2305843009213693951");
        BOOST_CHECK(premiers::miller_rabin<boost::multiprecision::cpp_int>(m, 25));
        BOOST_CHECK_EQUAL(false, premiers::miller_rabin<boost::multiprecision::cpp_int>(m + 44, 25));

        BOOST_CHECK_EQUAL(false, premiers::miller_rabin<boost::multiprecision::cpp_int>(n * m, 25));
        BOOST_CHECK_EQUAL(false, premiers::miller_rabin<boost::multiprecision::cpp_int>(n * m - 2, 25));

        boost::multiprecision::cpp_int p("170141183460469231731687303715884105727");
        BOOST_CHECK(premiers::miller_rabin<boost::multiprecision::cpp_int>(p, 25));
        BOOST_CHECK_EQUAL(false, premiers::miller_rabin<boost::multiprecision::cpp_int>(p - 2, 25));

        size_t ni = 9'074'200'321;
        BOOST_CHECK(premiers::miller_rabin<size_t>(ni, 25));

        BOOST_CHECK(premiers::miller_rabin<size_t>(7, 25));
    }

    BOOST_AUTO_TEST_CASE(suivant) {
        boost::multiprecision::cpp_int n("32416189721");
        BOOST_CHECK_EQUAL(32416189733, premiers::suivant(n));

        boost::multiprecision::cpp_int m("32416189877");
        BOOST_CHECK_EQUAL(32416189909, premiers::suivant(m));

        boost::multiprecision::cpp_int p("2305843009213693951");
        BOOST_CHECK_EQUAL(2305843009213693967, premiers::suivant(p));
        for (boost::multiprecision::cpp_int i = p + 2; i < 2305843009213693967; i += 2) {
            BOOST_CHECK_EQUAL(false, premiers::miller_rabin(i, 25));
        }

        boost::multiprecision::cpp_int r("170141183460469231731687303715884105757");
        boost::multiprecision::cpp_int q("170141183460469231731687303715884105727");
        BOOST_CHECK_EQUAL(r, premiers::suivant(q));
        for (boost::multiprecision::cpp_int i = q + 2; i < r; i += 2) {
            BOOST_CHECK_EQUAL(false, premiers::miller_rabin(i, 25));
        }

        std::vector<size_t> suivants{ 4, 8, 15, 16, 23, 42, 69, 666, 8283, 98084, 730210, 2691418, 80314325, 620283078 };
        for (auto& s : suivants) {
            s = premiers::suivant(s);
        }

        std::vector<size_t> resultats{ 5, 11, 17, 17, 29, 43, 71, 673, 8287, 98101, 730217, 2691421, 80314327, 620283089};
        BOOST_CHECK_EQUAL(resultats, suivants);
    }

BOOST_AUTO_TEST_SUITE_END()
