#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"
#include "Graphe.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

void probleme111()
{
    Timer t("probleme 111");
    // Considering 4-digit primes containing repeated digits it is clear that they cannot all be the 
    // same: 1111 is divisible by 11, 2222 is divisible by 22, and so on. But there are nine 4-digit 
    // primes containing three ones:
    //
    //                  1117, 1151, 1171, 1181, 1511, 1811, 2111, 4111, 8111
    //
    // We shall say that M(n, d) represents the maximum number of repeated digits for an n-digit prime
    // where d is the repeated digit, N(n, d) represents the number of such primes, and S(n, d) 
    // represents the sum of these primes.
    //
    // So M(4, 1) = 3 is the maximum number of repeated digits for a 4-digit prime where one is the 
    // repeated digit, there are N(4, 1) = 9 such primes, and the sum of these primes is 
    // S(4, 1) = 22275. It turns out that for d = 0, it is only possible to have M(4, 0) = 2 repeated 
    // digits, but there are N(4, 0) = 13 such cases.
    //
    // In the same way we obtain the following results for 4-digit primes.
    //
    //      Digit, d    M(4, d)     N(4, d)     S(4, d)
    //      0           2           13	        67061
    //      1           3	        9	        22275
    //      2           3	        1	        2221
    //      3           3	        12	        46214
    //      4           3	        2	        8888
    //      5           3	        1	        5557
    //      6           3	        1	        6661
    //      7           3	        9       	57863
    //      8           3	        1	        8887
    //      9           3	        7           48073
    // For d = 0 to 9, the sum of all S(4, d) is 273700.
    //
    // Find the sum of all S(10, d).
    nombre limite = puissance::puissance(10ULL, 10);
    
    vecteur premiers;
    {
        Timer t("crible");
        premiers::crible23<nombre>(limite, std::back_inserter(premiers));
    }
    
    std::map<unsigned short, std::map<nombre, vecteur>> ensemble;
    for (nombre p: premiers)
    {
        if (p > limite / 10)
        {
            vecteur chiffres(10, 0);
            chiffres::boucle_chiffre(p, [&chiffres] (nombre d){ chiffres.at(d)++; });
            
            for (size_t n = 0; n < 10; ++n)
            {
                if (chiffres[n] > 5) ensemble[n][chiffres[n]].push_back(p);                
            }
        }
    }
    
    std::cout << limite / 10 << std::endl;
    nombre resultat = 0;
    for (const auto & e: ensemble)
    {
        const std::pair<nombre, vecteur> & p = *std::next(e.second.begin(), e.second.size() - 1);
        nombre somme = std::accumulate(p.second.begin(), p.second.end(), 0ULL);
        resultat += somme;
        std::cout << e.first << "\t" << p.first << "\t" << p.second.size() << "\t" << somme << std::endl;
    }
    
	std::cout << "Solution: " << resultat << std::endl;
}
