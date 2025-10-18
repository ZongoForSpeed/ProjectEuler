#include "problemes.h"
#include "arithmetique.h"

#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(62, "Cubic permutations") {
    // The cube, 41063625 (345^3), can be permuted to produce two other cubes: 56623104 (384^3) and 
    // 66430125 (405^3). In fact, 41063625 is the smallest cube which has exactly three permutations 
    // of its digits which are also cube.
    //
    // Find the smallest cube for which exactly five permutations of its digits are cube.
    std::vector<std::string> cubes;
    nombre n = 1;
    nombre taille = 1;
    std::vector<std::string> resultat;
    while (resultat.empty()) {
        std::string s = std::to_string(n * n * n);
        if (s.size() != taille) {
            for (auto it1 = cubes.begin(), en = cubes.end(); it1 != en; ++it1) {
                resultat.push_back(*it1);
                for (auto it2 = std::next(it1); it2 != en; ++it2) {
                    if (std::is_permutation(it1->begin(), it1->end(), it2->begin()))
                        resultat.push_back(*it2);
                }
                if (resultat.size() > 4)
                    break;
                else
                    resultat.clear();
            }
            cubes.clear();
            taille = s.size();
        }
        cubes.push_back(s);
        ++n;
    }
    std::cout << resultat << std::endl;
    return resultat.front();
}
