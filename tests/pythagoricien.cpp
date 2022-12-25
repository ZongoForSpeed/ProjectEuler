#include <boost/test/unit_test.hpp>

#include "pythagoricien.h"
#include "utilitaires.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"

BOOST_AUTO_TEST_SUITE(test_pythagoricien)

    struct fixture_pythagoricien {
        std::set<std::tuple<size_t, size_t, size_t>> triplets;

        fixture_pythagoricien() {
            triplets = std::set<std::tuple<size_t, size_t, size_t>>
                    {
                            std::make_tuple(3, 4, 5),
                            std::make_tuple(5, 12, 13),
                            std::make_tuple(8, 15, 17),
                            std::make_tuple(7, 24, 25),

                            std::make_tuple(20, 21, 29),
                            std::make_tuple(12, 35, 37),
                            std::make_tuple(9, 40, 41),
                            std::make_tuple(28, 45, 53),

                            std::make_tuple(11, 60, 61),
                            std::make_tuple(16, 63, 65),
                            std::make_tuple(33, 56, 65),
                            std::make_tuple(48, 55, 73),

                            std::make_tuple(13, 84, 85),
                            std::make_tuple(36, 77, 85),
                            std::make_tuple(39, 80, 89),
                            std::make_tuple(65, 72, 97)
                    };
        }
    };

    BOOST_FIXTURE_TEST_CASE(nombres_pythagoricien, fixture_pythagoricien) {
        Pythagoricien pythagoricien(100);
        std::set<std::tuple<size_t, size_t, size_t>> resultat;
        for (auto t: pythagoricien) {
            resultat.insert(t);
        }

        BOOST_CHECK_EQUAL_COLLECTIONS(triplets.begin(), triplets.end(), resultat.begin(), resultat.end());
    }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
