#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <stack>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;

ENREGISTRER_PROBLEME(198, "Ambiguous Numbers")
{
    Timer timer("probleme 198");
    // A best approximation to a real number x for the denominator bound d is a rational number r/s 
    // (in reduced form) with s ≤ d, so that any rational number p/q which is closer to x than r/s 
    // has q > d.
    //
    // Usually the best approximation to a real number is uniquely determined for all denominator 
    // bounds. However, there are some exceptions, e.g. 9/40 has the two best approximations 1/4 and
    // 1/5 for the denominator bound 6. We shall call a real number x ambiguous, if there is at least
    // one denominator bound for which x possesses two best approximations. Clearly, an ambiguous 
    // number is necessarily rational.
    //
    // How many ambiguous numbers x = p/q, 0 < x < 1/100, are there whose denominator q does not 
    // exceed 10^8?
    nombre limite = 100000000ULL;
    nombre borne = 100;
    
    nombre m = (nombre)std::sqrt(limite / 2);
    std::stack<nombre> s;
    for (nombre i = borne; i < m; ++i)
        s.push(i);

    nombre a = m;
    nombre resultat = limite / 2 - borne / 2;
    while (!s.empty())
    {
        nombre b = s.top();
        if (2*a*b > limite)
        {
            a = b;
            s.pop();
        }
        else
        {
            ++resultat;
            s.push(a+b);
        }
    }
        
    std::cout << "Solution: " << resultat << std::endl;
}
