#include "problemes.h"
#include "premiers.h"
#include "polygonal.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(46, "Goldbach's other conjecture") {
    // It was proposed by Christian Goldbach that every odd composite number can be written as the 
    // sum of a prime and twice a square.
    //
    // 9 = 7 + 2×1²
    // 15 = 7 + 2×2²
    // 21 = 3 + 2×3²
    // 25 = 7 + 2×3²
    // 27 = 19 + 2×2²
    // 33 = 31 + 2×1²
    // 
    // It turns out that the conjecture was false.
    //
    // What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
    std::set<nombre> premiers;
    premiers::crible235<nombre>(10000, std::inserter(premiers, premiers.begin()));
    nombre resultat = 0;
    nombre n = 9;
    bool trouve = false;
    while (!trouve) {
        if (premiers.find(n) == premiers.end()) {
            for (nombre p: premiers) {
                if (p > n) {
                    resultat = n;
                    trouve = true;
                    break;
                } else if ((n - p) % 2 == 0 && polygonal::est_carre((n - p) / 2)) {
                    break;
                }
            }
        }

        n += 2;
    }
    return std::to_string(resultat);
}
