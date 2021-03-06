#include "problemes.h"
#include "premiers.h"
#include "timer.h"

#include <algorithm>
#include <set>
#include <iterator>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(58, "Spiral primes") {
    // Starting with 1 and spiralling anticlockwise in the following way, a square spiral 
    // with side length 7 is formed.
    //
    //                      37 36 35 34 33 32 31
    //                      38 17 16 15 14 13 30
    //                      39 18  5  4  3 12 29
    //                      40 19  6  1  2 11 28
    //                      41 20  7  8  9 10 27
    //                      42 21 22 23 24 25 26
    //                      43 44 45 46 47 48 49
    //
    // It is interesting to note that the odd squares lie along the bottom right diagonal, 
    // but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; 
    // that is, a ratio of 8/13 ≈ 62%.
    //
    // If one complete new layer is wrapped around the spiral above, a square spiral with side length 
    // 9 will be formed. If this process is continued, what is the side length of the square spiral 
    // for which the ratio of primes along both diagonals first falls below 10%?
    std::set<nombre> premiers;
    {
        Timer t_crible("crible");
        premiers::crible235<nombre>(1000000000, std::inserter(premiers, premiers.begin()));
    }
    nombre nbPremiers = 0;
    nombre nbDiagonales = 1;
    nombre n = 1;
    nombre resultat;
    while (true) {
        nombre difference = ((n + 2) * (n + 2) - n * n) / 4;
        nbDiagonales += 4;
        for (nombre k = 1; k < 4; ++k) {
            if (premiers.find(n * n + difference * k) != premiers.end()) ++nbPremiers;
        }
        n += 2;
        if (10 * nbPremiers < nbDiagonales) {
            resultat = n;
            break;
        }
    }
    return std::to_string(resultat);
}
