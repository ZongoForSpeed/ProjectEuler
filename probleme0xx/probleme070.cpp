#include "problemes.h"
#include "chiffres.h"
#include "premiers.h"
#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(70, "Totient permutation") {
    // Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the 
    // number of positive numbers less than or equal to n which are relatively prime to n. For 
    // example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
    //
    // The number 1 is considered to be relatively prime to every positive number, so φ(1)=1.
    // 
    // Interestingly, φ(87109)=79180, and it can be seen that 87109 is a permutation of 79180.
    // 
    // Find the value of n, 1 < n < 10^7, for which φ(n) is a permutation of n and the ratio n/φ(n) 
    // produces a minimum.
    vecteur premiers;
    premiers::crible23<nombre>(5000, std::back_inserter(premiers));

    fraction min_ratio(std::numeric_limits<nombre>::max());
    nombre min_n = 0;
    for (auto p: premiers) {
        for (auto q: premiers) {
            if (q >= p)
                break;
            const nombre n = p * q;
            if (n > 10000000)
                break;
            const nombre phi = (p - 1) * (q - 1);
            fraction ratio(n, phi);
            if (ratio < min_ratio && chiffres::permutation_chiffres(n, phi)) {
                min_ratio = ratio;
                min_n = n;
            }
        }
    }
    return std::to_string(min_n);
}
