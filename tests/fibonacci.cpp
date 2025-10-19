#include <boost/test/unit_test.hpp>

#include "fibonacci.h"
#include "format/vector.h"
#include "utilitaires.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_fibonacci)

    struct fixture_fibonacci {
        std::vector<size_t> triplets;

        fixture_fibonacci() {
            triplets = std::vector<size_t>{1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
        }
    };

    BOOST_FIXTURE_TEST_CASE(nombres_fibonacci, fixture_fibonacci) {
        Fibonacci<size_t> fibonacci(100);
        std::vector<size_t> resultat;
        for (auto t: fibonacci) {
            resultat.push_back(t);
        }

        std::cout << resultat << std::endl;
        BOOST_CHECK_EQUAL_COLLECTIONS(triplets.begin(), triplets.end(), resultat.begin(), resultat.end());
    }

    BOOST_FIXTURE_TEST_CASE(nombres_fibonacci_start, fixture_fibonacci) {
        Fibonacci<size_t> fibonacci(1, 2, 100);
        std::vector<size_t> resultat{1, 1};
        for (auto t: fibonacci) {
            resultat.push_back(t);
        }

        std::cout << resultat << std::endl;
        BOOST_CHECK_EQUAL_COLLECTIONS(triplets.begin(), triplets.end(), resultat.begin(), resultat.end());
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
