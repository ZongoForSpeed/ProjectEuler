#include <boost/test/unit_test.hpp>

#include "diophantienne.h"

BOOST_AUTO_TEST_SUITE(test_diophantienne)

    BOOST_AUTO_TEST_CASE(pqa1) {
        auto resultat = diophantienne::PQa(11, 108, 13);
        std::vector<long long> fractions{0, 7, 2, 1, 1, 6, 1, 1};
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.first.begin(), resultat.first.end(), fractions.begin(), fractions.end());
        BOOST_CHECK_EQUAL(resultat.second, 5);
    }

    BOOST_AUTO_TEST_CASE(pqa2) {
        auto resultat = diophantienne::PQa(0, 1, 13);
        std::vector<long long> fractions{3, 1, 1, 1, 1, 6};
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.first.begin(), resultat.first.end(), fractions.begin(), fractions.end());
        BOOST_CHECK_EQUAL(resultat.second, 5);
    }

    BOOST_AUTO_TEST_CASE(pell1_min) {
        BOOST_CHECK_EQUAL(diophantienne::pell1_min(13, 1), std::make_pair(649, 180));
        BOOST_CHECK_EQUAL(diophantienne::pell1_min(13, -1), std::make_pair(18, 5));
    }

    BOOST_AUTO_TEST_CASE(pell4_min) {
        BOOST_CHECK_EQUAL(diophantienne::pell4_min(13, 1), std::make_pair(11, 3));
        BOOST_CHECK_EQUAL(diophantienne::pell4_min(13, -1), std::make_pair(3, 1));
    }

    BOOST_AUTO_TEST_CASE(pell1_1) {
        std::vector<std::pair<long long, long long>> resultat;
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(649, 180),
                std::make_pair(842401, 233640)
        };
        auto callback = [&resultat, &solution](long long x, long long y) {
            resultat.push_back(std::make_pair(x, y));
            return resultat.size() != solution.size();
        };

        diophantienne::pell1<long long>(13, 1, callback);
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(pell1_2) {
        std::vector<std::pair<long long, long long>> resultat;
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(18, 5),
                std::make_pair(23382, 6485),
                std::make_pair(30349818, 8417525)
        };
        auto callback = [&resultat, &solution](long long x, long long y) {
            resultat.push_back(std::make_pair(x, y));
            return resultat.size() != solution.size();
        };

        diophantienne::pell1<long long>(13, -1, callback);
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(pell4_1) {
        std::vector<std::pair<long long, long long>> resultat;
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(649, 180),
                std::make_pair(421200, 116820)
        };
        auto callback = [&resultat, &solution](long long x, long long y) {
            resultat.push_back(std::make_pair(x, y));
            return resultat.size() != solution.size();
        };

        diophantienne::pell4<long long>(13, 1, callback);
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(pell4_2) {
        std::vector<std::pair<long long, long long>> resultat;
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(18, 5),
                std::make_pair(5841, 1620),
                std::make_pair(1895386, 525685)
        };
        auto callback = [&resultat, &solution](long long x, long long y) {
            resultat.push_back(std::make_pair(x, y));
            return resultat.size() != solution.size();
        };

        diophantienne::pell4<long long>(13, -1, callback);
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(pell_funds_bf1) {
        auto resultat = diophantienne::pell_funds_bf<long long>(13, 108);
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(11, 1),
                std::make_pair(-11, 1),
                std::make_pair(15, 3),
                std::make_pair(-15, 3),
                std::make_pair(24, 6),
                std::make_pair(-24, 6),
                std::make_pair(41, 11),
                std::make_pair(-41, 11),
                std::make_pair(80, 22),
                std::make_pair(-80, 22),
                std::make_pair(141, 39),
                std::make_pair(-141, 39)
        };
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(pell_funds_bf2) {
        auto resultat = diophantienne::pell_funds_bf<long long>(157, 12);
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(13, 1),
                std::make_pair(-13, 1),
                std::make_pair(10663, 851),
                std::make_pair(-10663, 851),
                std::make_pair(579160, 46222),
                std::make_pair(-579160, 46222)
        };
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(pell_funds_bf3) {
        auto resultat = diophantienne::pell_funds_bf<long long>(13, 27);
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(12, 3),
                std::make_pair(-12, 3),
                std::make_pair(40, 11),
                std::make_pair(-40, 11)
        };
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(pell_bf1) {
        auto resultat = diophantienne::pell_bf<long long>(13, 108, 1000);
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(11, 1),
                std::make_pair(15, 3),
                std::make_pair(24, 6),
                std::make_pair(41, 11),
                std::make_pair(80, 22),
                std::make_pair(141, 39),
                std::make_pair(249, 69),
                std::make_pair(440, 122),
                std::make_pair(869, 241)
        };
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(pell_bf2) {
        auto resultat = diophantienne::pell_bf<long long>(157, 12, 100000000);
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(13, 1),
                std::make_pair(10663, 851),
                std::make_pair(579160, 46222)
        };
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(pell_bf3) {
        auto resultat = diophantienne::pell_bf<long long>(13, 27, 1000);
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(12, 3),
                std::make_pair(40, 11),
                std::make_pair(220, 61),
                std::make_pair(768, 213)
        };
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(quad_s) {
        auto resultat = diophantienne::quad_s<long long>(8, 9, 72, 1000);
        std::vector<std::pair<long long, long long>> solution{
                std::make_pair(3, 0),
                std::make_pair(9, 8),
                std::make_pair(51, 48),
                std::make_pair(297, 280)
        };
        BOOST_CHECK_EQUAL_COLLECTIONS(resultat.begin(), resultat.end(), solution.begin(), solution.end());
    }

    BOOST_AUTO_TEST_CASE(iterateur_diophantienne1) {
        // 10x + 84y + 16 = 0
        long long int A = 10, B = 84, C = 16;
        size_t compteur = 0;
        for (auto s : diophantienne::equation_lineaire(A, B, C)) {
            ++compteur;
            if (compteur > 10) {
                break;
            }
            BOOST_CHECK_EQUAL(A * s.first + B * s.second + C, 0);
        }
    }

    BOOST_AUTO_TEST_CASE(iterateur_diophantienne2) {
        // 10x + 84y - 16 = 0
        long long int A = 10, B = 84, C = -16;
        size_t compteur = 0;
        for (auto s : diophantienne::equation_lineaire(A, B, C)) {
            ++compteur;
            if (compteur > 10) {
                break;
            }
            BOOST_CHECK_EQUAL(A * s.first + B * s.second + C, 0);
        }
    }

BOOST_AUTO_TEST_SUITE_END()
