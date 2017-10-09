#include <boost/test/unit_test.hpp>

#include "utilitaires.h"
#include "permutation.h"

#include <iostream>
#include <vector>

BOOST_AUTO_TEST_SUITE(test_permutation)
    BOOST_AUTO_TEST_CASE(permutation_simple)
    {
        const std::vector<std::vector<int>> resultat {
            {1, 2, 3},
            {1, 3, 2},
            {2, 1, 3},
            {2, 3, 1},
            {3, 1, 2},
            {3, 2, 1}
        };
        
        size_t index = 0;
        const std::vector<int> v {1, 2, 3};
        for (auto i: permutation::Permutation<std::vector<int>>(v)) {
            BOOST_CHECK_EQUAL_COLLECTIONS(i.begin(), i.end(), 
                                          resultat[index].begin(), resultat[index].end());
            ++index;
        }
    }
    
    BOOST_AUTO_TEST_CASE(permutation_doublon)
    {
        const std::vector<std::vector<int>> resultat {
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
        const std::vector<int> v {1, 2, 2, 4};
        for (auto i: permutation::Permutation<std::vector<int>>(v)) {
            BOOST_CHECK_EQUAL_COLLECTIONS(i.begin(), i.end(), 
                                          resultat[index].begin(), resultat[index].end());
            ++index;
        }
    }
BOOST_AUTO_TEST_SUITE_END()
