#include "problemes.h"
#include "polygonal.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>
#include <boost/rational.hpp>

#include <boost/range/adaptor/reversed.hpp>

typedef boost::multiprecision::mpz_int nombre;
typedef boost::rational<nombre> fraction;
typedef std::vector<nombre> vecteur;

typedef std::pair<nombre, nombre> paire;

namespace
{
    bool evaluer(nombre a, nombre b, nombre s)
    {
        return a*a < b*b*s;
    }

    fraction fraction_continue(size_t S, nombre bound)
    {
        paire a(racine_carre(S), 1);
        paire b(a.first + 1, 1);
        
        while (a.second + b.second <= bound)
        {
            paire x (a.first + b.first, a.second + b.second);
            if (evaluer(x.first, x.second, S))
                a = x;
            else
                b = x;
        }
        
        if (evaluer(a.first*b.second + b.first*a.second, 2*a.second*b.second, S))
            return fraction(b.first, b.second);
        else
            return fraction(a.first, a.second);
    }
}

ENREGISTRER_PROBLEME(192, "Best Approximations")
{
    // Let x be a real number.
    // A best approximation to x for the denominator bound d is a rational number r/s in reduced form,
    // with s ≤ d, such that any rational number which is closer to x than r/s has a denominator larger
    // than d:
    //
    //                                |p/q-x| < |r/s-x| ⇒ q > d
    //
    // For example, the best approximation to √13 for the denominator bound 20 is 18/5 and the best
    // approximation to √13 for the denominator bound 30 is 101/28.
    //
    // Find the sum of all denominators of the best approximations to √n for the denominator bound 10^12,
    // where n is not a perfect square and 1 < n ≤ 100000.
    nombre bound = 1000000000000ULL;
    nombre resultat = 0;
    for (size_t n = 1; n <= 100000; ++n)
    {
        if (!polygonal::est_carre(n))
        {
            fraction f = fraction_continue(n, bound);
            // std::cout << n << "\t" << f << std::endl;
            resultat += f.denominator();
        }
    }

    return std::to_string(resultat);
}
