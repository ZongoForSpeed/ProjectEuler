#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"

#include <iostream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(17, "Number letter counts")
{
    Timer t("probleme 17");
    // If the numbers 1 to 5 are written out in words: one, two, three, four, five, 
    // then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
    // 
    // If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, 
    // how many letters would be used?
    // 
    // NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) 
    // contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
    // The use of},and" when writing out numbers is in compliance with British usage.
    const vecteur unite {0,3,3,5,4,4,3,5,5,4,3,6,6,8,8,7,7,9,8,8};
    const vecteur dizaine {0,3,6,6,5,5,5,7,6,6};
    const nombre centaine = 7; // hundred
    const nombre et = 3; // and
    
    nombre resultat = 11; // onethousand
    for (nombre n = 1; n < 1000; ++n)
    {
        if (n%100 != 0)
        {
            const nombre c = n%100;
            if (c < 20)
                resultat += unite[c];
            else
                resultat += dizaine[c/10] + unite[c%10];
        }
        if (n >= 100)
        {
            resultat += unite[n/100] + centaine;
            if (n%100 != 0) resultat += et;
        }
    }
    std::cout << "Solution: " << resultat << std::endl;
}
