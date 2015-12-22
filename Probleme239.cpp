#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;
// typedef unsigned long long nombre;

typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(239, "Infinite string tour")
{
    Timer timer("probleme 239");
    // A set of disks numbered 1 through 100 are placed in a line in random order.
    //
    // What is the probability that we have a partial derangement such that exactly 22 prime number 
    // discs are found away from their natural positions?
    // (Any number of non-prime disks may also be found in or out of their natural positions.)
    //
    // Give your answer rounded to 12 places behind the decimal point in the form 0.abcdefghijkl.
    const nombre denominateur = combinatoire::factorielle<nombre>(100);

    nombre numerateur = 0;
    for (nombre n = 0; n <= 22; ++n)
    {
        numerateur += (n%2 == 0?1:-1) 
            * combinatoire::coefficient_binomial<nombre>(22, n) 
            * combinatoire::factorielle<nombre>(97-n);
    }
    
    numerateur *= combinatoire::coefficient_binomial<nombre>(25, 22);
    
    boost::multiprecision::mpf_float resultat = numerateur;
    resultat /= denominateur;
    std::cout << std::setprecision(12);
    std::cout << "Solution: " << resultat << std::endl;
}