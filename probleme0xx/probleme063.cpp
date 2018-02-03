#include "problemes.h"
#include "arithmetiques.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(63, "Powerful digit counts") {
    // The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit number, 134217728=8^9, 
    // is a ninth power.
    // 
    // How many n-digit positive integers exist which are also an nth power?
    nombre resultat = 0;
    for (nombre n = 1; n < 10; ++n) {
        resultat += static_cast<nombre>(std::floor(std::log(10) / (std::log(10) - std::log(n))));
    }
    return std::to_string(resultat);
}
