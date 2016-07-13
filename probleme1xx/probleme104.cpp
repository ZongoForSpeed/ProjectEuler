#include "problemes.h"
#include "chiffres.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<nombre, nombre> paire;

namespace
{
    bool test_premier_chiffres(long double f)
    {
        const nombre chiffres = static_cast<nombre>(std::log10(f));
        if (chiffres < 9)
            return false;
            
        nombre debut = static_cast<nombre>(f / puissance::puissance(10.0L, chiffres - 8));
        return chiffres::pandigital(debut);
    }
    
    bool test_dernier_chiffres(nombre n)
    {
        return chiffres::pandigital(n);
    }
}

ENREGISTRER_PROBLEME(104, "Pandigital Fibonacci ends")
{
    // The Fibonacci sequence is defined by the recurrence relation:
    //
    // Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
    // It turns out that F541, which contains 113 digits, is the first Fibonacci number for which the
    // last nine digits are 1-9 pandigital (contain all the digits 1 to 9, but not necessarily in order).
    // And F2749, which contains 575 digits, is the first Fibonacci number for which the first nine digits
    // are 1-9 pandigital.
    //
    // Given that Fk is the first Fibonacci number for which the first nine digits AND the last nine digits
    // are 1-9 pandigital, find k.
    const long double sqrt5 = std::sqrt(5.0L);
    const long double phi = (1.0L + sqrt5) / 2.0L;
    
    const nombre masque = puissance::puissance(10ULL, 9);

    long double fd = phi / sqrt5;
    nombre fn1 = 0;
    nombre fn2 = 1;
    
    nombre resultat = 0;

    std::cout << std::setprecision(10) << std::boolalpha;
    for (nombre n = 2;; ++n)
    {
        fd *= phi;
        if (fd > masque * masque)
            fd /= masque;
        std::tie(fn1, fn2) = paire(fn2, (fn1 + fn2)%masque);
        if (test_premier_chiffres(fd) && test_dernier_chiffres(fn2))
        {
            resultat = n;
            break;
        }
    }
    
    return std::to_string(resultat);
}
