#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>
typedef boost::multiprecision::mpz_int nombre;

#include <boost/rational.hpp>
#include <boost/optional.hpp>

void probleme168()
{
    Timer timer("probleme 168");
    // Consider the number 142857. We can right-rotate this number by moving the last digit (7) to 
    // the front of it, giving us 714285.
    // It can be verified that 714285=5×142857.
    // This demonstrates an unusual property of 142857: it is a divisor of its right-rotation.
    //
    // Find the last 5 digits of the sum of all integers n, 10 < n < 10^100, that have this property.
    nombre resultat = 0;
    for (nombre puissance = 1; puissance < 101; ++puissance)
    {
        for (nombre a = 1; a < 10; ++a)
        for (nombre n = 1; n < 10; ++n)
        {
            nombre numerateur = a * (puissance::puissance<nombre>(10, puissance) - n);
            nombre denominateur = 10*n - 1;
            
            if (numerateur%denominateur == 0)
            {
                nombre valeur = numerateur/denominateur;
                if (chiffres::nombre_chiffres(valeur) == puissance)
                {
                    valeur = 10*valeur + a;
                    if (chiffres::nombre_chiffres(valeur) <= 100)
                        resultat += valeur;
                }
            }
        }
    }
    std::cout << "Solution: " << resultat%100000 << std::endl;
}
