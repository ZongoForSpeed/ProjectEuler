#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(214, "Totient Chains")
{
    Timer timer("probleme 214");
    // Let φ be Euler's totient function, i.e. for a natural number n, φ(n) is the number of k, 
    // 1 ≤ k ≤ n, for which gcd(k,n) = 1.
    // 
    // By iterating φ, each positive integer generates a decreasing chain of numbers ending in 1.
    // E.g. if we start with 5 the sequence 5,4,2,1 is generated.
    // Here is a listing of all chains with length 4:
    // 
    //                                      5,4,2,1
    //                                      7,6,2,1
    //                                      8,4,2,1
    //                                      9,6,2,1
    //                                      10,4,2,1
    //                                      12,4,2,1
    //                                      14,6,2,1
    //                                      18,6,2,1
    //
    // Only two of these chains start with a prime, their sum is 12.
    //
    // What is the sum of all primes less than 40000000 which generate a chain of length 25?
    nombre limite = 40000000;
    nombre chaine = 25;
    vecteur premiers;
    premiers::crible235<nombre>(limite, std::back_inserter(premiers));
    
    nombre resultat = 0;
    for (nombre p: premiers)
    {
        if (p >= limite)
            break;
        
        nombre longueur = 1;
        nombre m = p;
        while(m != 1 && longueur < chaine)
        {
            m = arithmetiques::phi(m, premiers);
            ++longueur;
        }    
        
        if (m == 1 && longueur == chaine)
            resultat += p;
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
