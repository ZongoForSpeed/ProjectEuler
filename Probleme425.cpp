#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include "Timer.h"
#include "Premiers.h"
#include <boost/foreach.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;
typedef std::map<nombre, ensemble> dictionnaire; 

class Probleme425
{
    // Two positive numbers A and B are said to be connected (denoted by "A ↔ B") if one of these conditions holds:
    // (1) A and B have the same length and differ in exactly one digit; for example, 123 ↔ 173.
    // (2) Adding one digit to the left of A (or B) makes B (or A); for example, 23 ↔ 223 and 123 ↔ 23.
    // 
    // We call a prime P a 2's relative if there exists a chain of connected primes between 2 and P and no prime in the chain exceeds P.
    // 
    // For example, 127 is a 2's relative. One of the possible chains is shown below:
    // 2 ↔ 3 ↔ 13 ↔ 113 ↔ 103 ↔ 107 ↔ 127
    // However, 11 and 103 are not 2's relatives.
    // 
    // Let F(N) be the sum of the primes ≤ N which are not 2's relatives.
    // We can verify that F(103) = 431 and F(104) = 78728.
    //
    // Find F(107).
    nombre limite;
public:
    Probleme425(nombre l) : limite(l) {}
    
    bool test(nombre a, nombre b)
    {
        // (1) A and B have the same length and differ in exactly one digit; for example, 123 ↔ 173.
        // (2) Adding one digit to the left of A (or B) makes B (or A); for example, 23 ↔ 223 and 123 ↔ 23
    
        nombre d = (a > b)?a-b:b-a;
        
        while (d%10 == 0) d /= 10;
        return d < 10;
    }

    void algorithme()
    {
        Timer t("algorithme");
        
        vecteur premier;
        premiers::crible(limite, premier);
        
        dictionnaire dico;
        nombre compteur = 0;
        BOOST_FOREACH(nombre p1, premier)
        {
            BOOST_FOREACH(nombre p2, premier)
            {
                if (p2 >= p1)
                    break;
                if (test(p1, p2))
                {
                    dico[p1].insert(p2);
                    dico[p2].insert(p1);
                    compteur += 2;
                }
            }
        }
        
        std::cout << "compteur : " << compteur << std::endl;
    }
};

int main(int argc, char** argv)
{
    nombre limite = 0;
    if (argc > 1)
    {
        limite = atol(argv[1]);
    }
    else
    {
        std::cout << "Limite : " << std::endl;
        std::cin >> limite;
    }
    
    Probleme425 p(limite);
    p.algorithme();
    return 0;
}
