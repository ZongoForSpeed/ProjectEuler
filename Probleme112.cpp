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

void probleme112()
{
    Timer t("probleme 112");
    // Working from left-to-right if no digit is exceeded by the digit to its left it is called an 
    // increasing number; for example, 134468.
    //
    // Similarly if no digit is exceeded by the digit to its right it is called a decreasing number;
    // for example, 66420.
    // 
    // We shall call a positive integer that is neither increasing nor decreasing a "bouncy" number; 
    // for example, 155349.
    // 
    // Clearly there cannot be any bouncy numbers below one-hundred, but just over half of the numbers
    // below one-thousand (525) are bouncy. In fact, the least number for which the proportion of 
    // bouncy numbers first reaches 50% is 538.
    // 
    // Surprisingly, bouncy numbers become more and more common and by the time we reach 21780 the 
    // proportion of bouncy numbers is equal to 90%.
    //
    // Find the least number for which the proportion of bouncy numbers is exactly 99%.
    fraction limite (99, 100);
    nombre ratio_numerateur = 0;
    nombre ratio_denominateur = 0;
    
    nombre resultat = 0;
    for (nombre n = 1;; ++n)
    {
        const auto chiffres = arithmetiques::extraire_chiffres(n);
        ++ratio_denominateur;
        if (!std::is_sorted(chiffres.begin(), chiffres.end())
            && !std::is_sorted(chiffres.rbegin(), chiffres.rend()))
            ++ratio_numerateur;
        if (ratio_numerateur >= limite * ratio_denominateur)
        {
            resultat = n;
            break;
        }
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
