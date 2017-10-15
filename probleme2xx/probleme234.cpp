#include "problemes.h"
#include "premiers.h"
#include "utilitaires.h"

#include <fstream>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(234, "Semidivisible numbers") {
    // For an integer n ≥ 4, we define 
    // the lower prime square root of n, denoted by lps(n), as the largest prime ≤ √n
    // and the upper prime square root of n, ups(n), as the smallest prime ≥ √n.
    //
    // So, for example, lps(4) = 2 = ups(4), lps(1000) = 31, ups(1000) = 37.
    // Let us call an integer n ≥ 4 semidivisible, if one of lps(n) and ups(n) divides n, but not both.
    //
    // The sum of the semidivisible numbers not exceeding 15 is 30, the numbers are 8, 10 and 12.
    // 15 is not semidivisible because it is a multiple of both lps(15) = 3 and ups(15) = 5.
    // As a further example, the sum of the 92 semidivisible numbers up to 1000 is 34825.
    //
    // What is the sum of all semidivisible numbers not exceeding 999966663333 ?
    const nombre limite = 999966663333LL;
    const nombre borne = racine_carre(limite) + 1;

    vecteur premiers;
    premiers::crible235<nombre>(static_cast<size_t>(borne), std::back_inserter(premiers));

    nombre resultat = 0;
    nombre p1 = premiers.front();
    for (nombre p2: premiers) {
        for (nombre n = p1 * p1 + p1; n < std::min(p2 * p2, limite); n += p1) {
            if (n % p2 != 0)
                resultat += n;
        }
        for (nombre n = p2 * p2 - p2; n > p1 * p1; n -= p2) {
            if (n < limite && n % p1 != 0)
                resultat += n;
        }
        p1 = p2;
    }
    return std::to_string(resultat);
}
