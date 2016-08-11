#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <vector>

// typedef unsigned long long nombre;
typedef boost::multiprecision::mpz_int nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    std::string affiche(nombre n)
    {
        std::ostringstream oss;
        for (auto c: chiffres::extraire_chiffres(n, 14))
        {
            switch (static_cast<size_t>(c))
            {
            case 10: 
                oss << 'a';
                break;
            case 11: 
                oss << 'b';
                break;
            case 12: 
                oss << 'c';
                break;
            case 13:
                oss << 'd';
                break;
            default:
                oss << c;
                break;
            }
        }
        
        return oss.str();
    }
}

ENREGISTRER_PROBLEME(284, "Steady Squares")
{
    // The 3-digit number 376 in the decimal numbering system is an example of 
    // numbers with the special property that its square ends with the same 
    // digits: 376² = 141376. Let's call a number with this property a steady 
    // square.
    //
    // Steady squares can also be observed in other numbering systems. In the 
    // base 14 numbering system, the 3-digit number c37 is also a steady square:
    // c37² = aa0c37, and the sum of its digits is c+3+7=18 in the same numbering
    // system. The letters a, b, c and d are used for the 10, 11, 12 and 13 digits
    // respectively, in a manner similar to the hexadecimal numbering system.
    //
    // For 1 ≤ n ≤ 9, the sum of the digits of all the n-digit steady squares in 
    // the base 14 numbering system is 2d8 (582 decimal). Steady squares with 
    // leading 0's are not allowed.
    // 
    // Find the sum of the digits of all the n-digit steady squares in the base 
    // 14 numbering system for 1 ≤ n ≤ 10000 (decimal) and give your answer in 
    // the base 14 system using lower case letters where necessary.
    // vecteur premiers;
    // premiers::crible<nombre>(10, std::back_inserter(premiers));
    const vecteur restes1 { 0, 1 };    
    const vecteur restes2 { 1, 0 }; 
    
    nombre borne = 1;
    vecteur modulos { 2, 7 };
    
    nombre resultat = 1; // Cas n = 1 
    for (size_t k = 1; k < 10000 + 1; ++k)
    {
        // Cas n = 0 mod 2^k and n = 1 mod 7^k
        nombre n1 = arithmetiques::restes_chinois<nombre>(modulos, restes1);
        if (n1 > borne)
            resultat += chiffres::somme_chiffres(n1, 14);
        // Cas n = 1 mod 2^k and n = 0 mod 7^k
        nombre n2 = arithmetiques::restes_chinois<nombre>(modulos, restes2);
        if (n2 > borne)
            resultat += chiffres::somme_chiffres(n2, 14);
        
        borne *= 14;
        modulos.front() *= 2;
        modulos.back() *= 7;
    }
    
    return affiche(resultat);
}
