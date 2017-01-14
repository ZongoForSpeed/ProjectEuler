#include "problemes.h"
#include "utilitaires.h"
#include "grand_nombre.h"
#include "arithmetiques.h"
#include "premiers.h"

typedef grand_nombre nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    nombre N(size_t i, const vecteur & premiers) {
        std::map<nombre, size_t> d;
        arithmetiques::decomposition(grand_nombre::factorielle(i), premiers, d);
        for (auto & e: d) {
            e.second *= 1234567890;
        }
        
        std::cout << d << std::endl;
        
        return 0;
    }    
}

ENREGISTRER_PROBLEME(320, "Factorials divisible by a huge integer")
{
    // Let N(i) be the smallest integer n such that n! is divisible by (i!)**1234567890
    //
    // Let S(u)=∑N(i) for 10 ≤ i ≤ u.
    //
    // S(1000)=614538266565663.
    //
    // Find S(1 000 000) mod 10**18.
    vecteur premiers;
    premiers::crible235<nombre>(1000000000, std::back_inserter(premiers));
    
    nombre resultat = N(10, premiers);
    return resultat.to_string();
}
