#include <gtest/gtest.h>

#include "utilitaires.h"

TEST(test_utilitaires, affiche_vector) {
    const std::vector<int> v{1, 1, 2, 3, 5, 8, 13};
    std::ostringstream oss;
    oss << v;

    EXPECT_EQ("[1 1 2 3 5 8 13]", oss.str());
}

TEST(test_utilitaires, affiche_deque) {
    const std::deque<int> v{1, 1, 2, 3, 5, 8, 13, 21, 34};
    std::ostringstream oss;
    oss << v;

    EXPECT_EQ("[1 1 2 3 5 8 13 21 34]", oss.str());
}

TEST(test_utilitaires, affiche_set) {
    const std::set<int> v{1, 1, 2, 3, 5, 8, 13, 21, 34};
    std::ostringstream oss;
    oss << v;

    EXPECT_EQ("{1 2 3 5 8 13 21 34}", oss.str());
}

TEST(test_utilitaires, affiche_map) {
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

    EXPECT_EQ(result, oss.str());
}
