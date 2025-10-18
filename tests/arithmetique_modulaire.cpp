#include <boost/test/unit_test.hpp>

#include "utilitaires.h"
#include "arithmetique_modulaire.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_arithmetique_modulaire)

    struct fixure_arithmetiques {
        std::vector<size_t> premiers;

        explicit fixure_arithmetiques() {
            premiers = std::vector<size_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                           31, 37, 41, 43, 47, 53, 59, 61, 67,
                                           71, 73, 79, 83, 89, 97};
        }

        ~fixure_arithmetiques() = default;
    };

    BOOST_FIXTURE_TEST_CASE(inverse1, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique_modulaire::inverse_modulaire<unsigned long>(3, 11, premiers), 4);
        BOOST_CHECK_EQUAL(arithmetique_modulaire::inverse_modulaire<unsigned long long>(97643, 456753, premiers),
                          368123);
        BOOST_CHECK_EQUAL(
                arithmetique_modulaire::inverse_modulaire<unsigned long long>(107113, 3246999210ULL, premiers),
                180730717ULL);
    }

    BOOST_FIXTURE_TEST_CASE(inverse2, fixure_arithmetiques) {
        BOOST_CHECK_EQUAL(arithmetique_modulaire::inverse_modulaire<long>(3, 11), 4);
        BOOST_CHECK_EQUAL(arithmetique_modulaire::inverse_modulaire<long long>(97643, 456753), 368123);
        BOOST_CHECK_EQUAL(arithmetique_modulaire::inverse_modulaire<long long>(107113, 3246999210LL),
                          180730717LL);
    }

    BOOST_FIXTURE_TEST_CASE(chinois1, fixure_arithmetiques) {
        std::vector<unsigned long> modulos{3, 5, 7};
        std::vector<unsigned long> restes{2, 3, 2};

        auto reste = arithmetique_modulaire::restes_chinois<unsigned long>(modulos, restes, premiers);
        BOOST_CHECK_EQUAL(reste, 23);
    }

    BOOST_FIXTURE_TEST_CASE(chinois2, fixure_arithmetiques) {
        std::vector<unsigned long> modulos{3, 4, 5};
        std::vector<unsigned long> restes{2, 3, 1};

        auto reste = arithmetique_modulaire::restes_chinois<unsigned long>(modulos, restes, premiers);
        BOOST_CHECK_EQUAL(reste, 11);
    }

    BOOST_FIXTURE_TEST_CASE(chinois3, fixure_arithmetiques) {
        std::vector<long> modulos{3, 5, 7};
        std::vector<long> restes{2, 3, 2};

        auto reste = arithmetique_modulaire::restes_chinois<long>(modulos, restes);
        BOOST_CHECK_EQUAL(reste, 23);
    }

    BOOST_FIXTURE_TEST_CASE(chinois4, fixure_arithmetiques) {
        std::vector<long> modulos{3, 4, 5};
        std::vector<long> restes{2, 3, 1};

        auto reste = arithmetique_modulaire::restes_chinois<long>(modulos, restes);
        BOOST_CHECK_EQUAL(reste, 11);
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
