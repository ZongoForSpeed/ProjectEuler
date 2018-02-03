#include <boost/test/unit_test.hpp>

#include "utilitaires.h"

BOOST_AUTO_TEST_SUITE(test_utilitaires)

BOOST_AUTO_TEST_CASE(affiche_vector) {
    const std::vector<int> v{1, 1, 2, 3, 5, 8, 13};
    std::ostringstream oss;
    oss << v;

    BOOST_CHECK_EQUAL("[1 1 2 3 5 8 13]", oss.str());
}

BOOST_AUTO_TEST_CASE(affiche_deque) {
    const std::deque<int> v{1, 1, 2, 3, 5, 8, 13, 21, 34};
    std::ostringstream oss;
    oss << v;

    BOOST_CHECK_EQUAL("[1 1 2 3 5 8 13 21 34]", oss.str());
}

BOOST_AUTO_TEST_CASE(affiche_set) {
    const std::set<int> v{1, 1, 2, 3, 5, 8, 13, 21, 34};
    std::ostringstream oss;
    oss << v;

    BOOST_CHECK_EQUAL("{1 2 3 5 8 13 21 34}", oss.str());
}

BOOST_AUTO_TEST_CASE(affiche_map) {
    const std::map<int, std::string> v{{1,  "1"},
                                       {2,  "3"},
                                       {5,  "8"},
                                       {13, "21"}};
    std::ostringstream oss;
    oss << v;

    const std::string result = "{\n"
            "    1 => 1\n"
            "    2 => 3\n"
            "    5 => 8\n"
            "    13 => 21\n"
            "}\n";

    BOOST_CHECK_EQUAL(result, oss.str());
}

BOOST_AUTO_TEST_SUITE_END()
