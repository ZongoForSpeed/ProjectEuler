#include "Problemes.h"
#include "Arithmetiques.h"
#include "Premiers.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::mpz_int nombre;
// typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(221, "Alexandrian Integers")
{
    Timer timer("probleme 221");
    // We shall call a positive integer A an "Alexandrian integer", if there exist integers p, q, r 
    // such that:
    //
    //      A = p · q · r       and        1/A = 1/p + 1/q + 1/r
    //
    // For example, 630 is an Alexandrian integer (p = 5, q = −7, r = −18). In fact, 630 is the 6th 
    // Alexandrian integer, the first 6 Alexandrian integers being: 6, 42, 120, 156, 420 and 630.
    //
    // Find the 150000th Alexandrian integer.
    size_t limite = 150000;
    vecteur premiers;
    {
        Timer timer_crible("crible");
        premiers::crible235<nombre>(1000000000ULL, std::back_inserter(premiers));
    }
    
    vecteur Alexandrian;
    for (nombre p = 1; p < limite * 2 / 3; ++p)
    {
        nombre pp = p * p + 1;
        const auto diviseurs = arithmetiques::diviseurs<nombre>(pp, premiers);
        for (size_t n = 0; 2*n < diviseurs.size(); ++n)
        {
            auto d = diviseurs[n];
            nombre A = p * (p + d) * (p + pp / d);
            Alexandrian.push_back(A);
        }
    }
    
    std::sort(Alexandrian.begin(), Alexandrian.end());

    nombre resultat = Alexandrian[limite - 1];
    std::cout << "Solution: " << resultat << std::endl;
}
