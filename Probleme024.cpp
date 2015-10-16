#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <vector>
#include <algorithm>

ENREGISTRER_PROBLEME(24)
{
    // A permutation is an ordered arrangement of objects. For example, 3124 is one possible 
    // permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically 
    // or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
    //
    //                                    012   021   102   120   201   210
    // 
    // What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
    Timer t("probleme 24");
    std::vector<unsigned short> v{0,1,2,3,4,5,6,7,8,9};
    for (size_t n = 1; n < 1000000; ++n)
        std::next_permutation(v.begin(), v.end());
        
    std::cout << "Solution: ";
    for (const auto n : v)
        std::cout << n;
    std::cout << std::endl;
}