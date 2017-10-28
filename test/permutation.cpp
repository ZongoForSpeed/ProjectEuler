#include <gtest/gtest.h>

#include "utilitaires.h"
#include "permutation.h"
#include "test.h"

TEST(test_permutation, permutation_simple) {
    const std::vector<std::vector<int>> resultat{
            {1, 2, 3},
            {1, 3, 2},
            {2, 1, 3},
            {2, 3, 1},
            {3, 1, 2},
            {3, 2, 1}
    };

    size_t index = 0;
    const std::vector<int> v{1, 2, 3};
    for (auto i: permutation::Permutation<std::vector<int>>(v)) {
        EXPECT_EQ_COLLECTIONS(i.begin(), i.end(),
                              resultat[index].begin(), resultat[index].end());
        ++index;
    }
}

TEST(test_permutation, permutation_doublon) {
    const std::vector<std::vector<int>> resultat{
            {1, 2, 2, 4},
            {1, 2, 4, 2},
            {1, 4, 2, 2},
            {2, 1, 2, 4},
            {2, 1, 4, 2},
            {2, 2, 1, 4},
            {2, 2, 4, 1},
            {2, 4, 1, 2},
            {2, 4, 2, 1},
            {4, 1, 2, 2},
            {4, 2, 1, 2},
            {4, 2, 2, 1}
    };

    size_t index = 0;
    const std::vector<int> v{1, 2, 2, 4};
    for (auto i: permutation::Permutation<std::vector<int>>(v)) {
        EXPECT_EQ_COLLECTIONS(i.begin(), i.end(),
                              resultat[index].begin(), resultat[index].end());
        ++index;
    }
}

TEST(test_permutation, arrangements_simple) {
    const std::vector<std::vector<int>> resultat{
            {1, 2, 3},
            {1, 3, 2},
            {2, 1, 3},
            {2, 3, 1},
            {3, 1, 2},
            {3, 2, 1},
            {1, 2, 4},
            {1, 4, 2},
            {2, 1, 4},
            {2, 4, 1},
            {4, 1, 2},
            {4, 2, 1},
            {1, 3, 4},
            {1, 4, 3},
            {3, 1, 4},
            {3, 4, 1},
            {4, 1, 3},
            {4, 3, 1},
            {2, 3, 4},
            {2, 4, 3},
            {3, 2, 4},
            {3, 4, 2},
            {4, 2, 3},
            {4, 3, 2}
    };

    size_t index = 0;

    std::vector<int> iterable{1, 2, 3, 4};
    for (auto &i: permutation::Arrangements<int>(iterable, 3)) {
        EXPECT_EQ_COLLECTIONS(i.begin(), i.end(),
                              resultat[index].begin(), resultat[index].end());
        ++index;
    }
}

TEST(test_permutation, arrangements_doublon) {
    const std::vector<std::string> resultat{"AB", "BA", "AD", "DA", "BB", "BD", "DB"};

    size_t index = 0;

    std::vector<char> iterable{'A', 'B', 'B', 'D'};
    for (auto &i: permutation::Arrangements<char>(iterable, 2)) {
        EXPECT_EQ_COLLECTIONS(i.begin(), i.end(),
                              resultat[index].begin(), resultat[index].end());
        ++index;
    }
}

TEST(test_permutation, combinaisons_simple) {
    const std::vector<std::vector<int>> resultat{
            {1, 2, 3},
            {1, 2, 4},
            {1, 3, 4},
            {2, 3, 4}
    };

    size_t index = 0;
    std::vector<int> iterable{1, 2, 3, 4};
    for (auto i : permutation::Combinaisons<int>(iterable, 3)) {
        EXPECT_EQ_COLLECTIONS(i.begin(), i.end(),
                              resultat[index].begin(), resultat[index].end());
        ++index;
    }
}

TEST(test_permutation, combinaisons_doublon) {
    const std::vector<std::string> resultat{"AB", "AC", "AD", "BC", "BD", "CD"};

    size_t index = 0;
    std::vector<char> iterable{'A', 'B', 'C', 'D'};
    for (auto i : permutation::Combinaisons<char>(iterable, 2)) {
        EXPECT_EQ_COLLECTIONS(i.begin(), i.end(),
                              resultat[index].begin(), resultat[index].end());
        ++index;
    }
}
