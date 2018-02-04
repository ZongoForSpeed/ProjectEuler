#include "problemes.h"
#include "arithmetiques.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

ENREGISTRER_PROBLEME(18, "Maximum path sum I") {
    // By starting at the top of the triangle below and moving to adjacent numbers on the row below, 
    // the maximum total from top to bottom is 23.
    //                                             3
    //                                            7 4
    //                                           2 4 6
    //                                          8 5 9 3
    // That is, 3 + 7 + 4 + 9 = 23.
    //
    // Find the maximum total from top to bottom of the triangle below:
    // 
    matrice triangle{
            {75},
            {95, 64},
            {17, 47, 82},
            {18, 35, 87, 10},
            {20, 4,  82, 47, 65},
            {19, 1,  23, 75, 3,  34},
            {88, 2,  77, 73, 7,  63, 67},
            {99, 65, 4,  28, 6,  16, 70, 92},
            {41, 41, 26, 56, 83, 40, 80, 70, 33},
            {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
            {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
            {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
            {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
            {63, 66, 4,  68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
            {4,  62, 98, 27, 23, 9,  70, 98, 73, 93, 38, 53, 60, 4, 23}
    };
    // NOTE: As there are only 16384 routes, it is possible to solve this problem by 
    // trying every route. However, Problem 67, is the same challenge with a triangle containing 
    // one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
    const size_t taille = triangle.size();
    matrice resultat;
    for (size_t i = 0; i < taille; ++i) {
        vecteur ligne;
        if (i == 0)
            ligne.push_back(triangle[i][i]);
        else
            for (size_t j = 0; j <= i; ++j) {
                if (j == 0)
                    ligne.push_back(resultat[i - 1][j] + triangle[i][j]);
                else if (i == j)
                    ligne.push_back(resultat[i - 1][j - 1] + triangle[i][j]);
                else
                    ligne.push_back(std::max(resultat[i - 1][j - 1], resultat[i - 1][j]) + triangle[i][j]);
            }
        resultat.push_back(ligne);
    }
    const auto it = std::max_element(resultat.back().begin(), resultat.back().end());
    return std::to_string(*it);
}
