#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

void probleme068()
{
    Timer t("probleme 68");
    // Consider the following "magic" 3-gon ring, filled with the numbers 1 to 6, and each line 
    // adding to nine.
    //
    // Working clockwise, and starting from the group of three with the numerically lowest external 
    // node (4,3,2 in this example), each solution can be described uniquely. For example, the above
    // solution can be described by the set: 4,3,2; 6,2,1; 5,1,3.
    //
    // It is possible to complete the ring with four different totals: 9, 10, 11, and 12. There are 
    // eight solutions in total.
    // 
    // Total    Solution Set
    // 9        4,2,3; 5,3,1; 6,1,2
    // 9        4,3,2; 6,2,1; 5,1,3
    // 10       2,3,5; 4,5,1; 6,1,3
    // 10       2,5,3; 6,3,1; 4,1,5
    // 11       1,4,6; 3,6,2; 5,2,4
    // 11	    1,6,4; 5,4,2; 3,2,6
    // 12       1,5,6; 2,6,4; 3,4,5
    // 12       1,6,5; 3,5,4; 2,4,6
    //
    // By concatenating each group it is possible to form 9-digit strings; the maximum string for a 
    // 3-gon ring is 432621513.
    //
    // Using the numbers 1 to 10, and depending on arrangements, it is possible to form 16- and 17-digit
    // strings. What is the maximum 16-digit string for a "magic" 5-gon ring?
    std::vector<nombre> arrangements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    nombre max_solution = 0;
    do
    {
        const nombre k = arrangements[0] + arrangements[1] + arrangements[6];
        if (arrangements[1] + arrangements[2] + arrangements[7] == k
            && arrangements[2] + arrangements[3] + arrangements[8] == k
            && arrangements[3] + arrangements[4] + arrangements[9] == k
            && arrangements[4] + arrangements[0] + arrangements[5] == k
            && arrangements[5] < arrangements[6]
            && arrangements[5] < arrangements[7]
            && arrangements[5] < arrangements[8]
            && arrangements[5] < arrangements[9]
            )
            {
                std::stringstream oss;
                oss << arrangements[5] << arrangements[0] << arrangements[4]
                    << arrangements[9] << arrangements[4] << arrangements[3]
                    << arrangements[8] << arrangements[3] << arrangements[2]
                    << arrangements[7] << arrangements[2] << arrangements[1]
                    << arrangements[6] << arrangements[1] << arrangements[0];
                if (oss.str().size() == 16)
                {
                    nombre solution;
                    oss >> solution;
                    max_solution = std::max(max_solution, solution);  
                }
                
            }
    }
    while(std::next_permutation(arrangements.begin(), arrangements.end()));
    std::cout << "Solution: " << max_solution << std::endl;
}