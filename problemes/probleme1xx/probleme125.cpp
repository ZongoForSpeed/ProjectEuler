#include "problemes.h"
#include "chiffres.h"
#include "puissance.h"
#include "utilitaires.h"

#include <fstream>
#include <execution>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(125, "Palindromic sums") {
    // The palindromic number 595 is interesting because it can be written as the sum of 
    // consecutive squares: 6² + 7² + 8² + 9² + 10² + 11² + 12².
    //
    // There are exactly eleven palindromes below one-thousand that can be written as 
    // consecutive square sums, and the sum of these palindromes is 4164. Note that 1 = 0² + 1²
    // has not been included as this problem is concerned with the squares of positive integers.
    // 
    // Find the sum of all the numbers less than 10^8 that are both palindromic and can be written 
    // as the sum of consecutive squares.
    auto limite = puissance::puissance<nombre, unsigned>(10, 8);
    vecteur carres;
    for (nombre n = 1; n * n < limite; ++n)
        carres.push_back(n * n);

    std::set<nombre> resultat;
    for (auto it1 = carres.begin(), en = carres.end(); it1 != en; ++it1) {
        nombre somme = *it1;
        for (auto it2 = std::next(it1); it2 != en; ++it2) {
            somme += *it2;
            if (somme >= limite)
                break;
            else if (chiffres::palindrome(somme))
                resultat.insert(somme);
        }
    }

    return std::to_string(std::reduce(std::execution::par, resultat.begin(), resultat.end()));
}
