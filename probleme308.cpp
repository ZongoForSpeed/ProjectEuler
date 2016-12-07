#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace 
{
    nombre conway_premier(nombre n, const vecteur & premiers)
    {
        auto diviseurs = arithmetiques::diviseurs(n, premiers);
        nombre d = diviseurs[diviseurs.size() - 2];
        
        nombre resultat = n+d-2 + (6*n+2)*(n-d);
        for (nombre k = d; k < n; ++k)
        {
            resultat += 2*(n / k);
        }
        
        return resultat;
    }
}

ENREGISTRER_PROBLEME(308, "An amazing Prime-generating Automaton")
{
    // A program written in the programming language Fractran consists of a list of fractions.
    //
    // The internal state of the Fractran Virtual Machine is a positive integer, which is initially set to a seed value. Each iteration of a Fractran program multiplies the state integer by the first fraction in the list which will leave it an integer.
    // 
    // For example, one of the Fractran programs that John Horton Conway wrote for prime-generation consists of the following 14 fractions:
    //
    // 17/91, 78/85, 19/51, 23/38, 29/33, 77/29, 95/23, 
    // 77/19, 1/17, 11/13, 13/11, 15/2, 1/7, 55/1.
    //
    // Starting with the seed integer 2, successive iterations of the program produce
    // the sequence:
    // 15, 825, 725, 1925, 2275, 425, ..., 68, 4, 30, ..., 136, 8, 60, ..., 
    // 544, 32, 240, ...
    //
    // The powers of 2 that appear in this sequence are 2**2, 2**3, 2**5, ...
    //
    // It can be shown that all the powers of 2 in this sequence have prime exponents
    // and that all the primes appear as exponents of powers of 2, in proper order!
    //
    // If someone uses the above Fractran program to solve Project Euler Problem
    // 7 (find the 10001st prime), how many iterations would be needed until the 
    // program produces 2**10001st prime ?
    nombre p = 104743;
    vecteur premiers;
    premiers::crible<nombre>(p, std::back_inserter(premiers));
    
    nombre resultat = 0;
    for (nombre n = 2; n < p + 1; ++n)
    {
        resultat += conway_premier(n, premiers);
    }
    
    return std::to_string(resultat);
}
