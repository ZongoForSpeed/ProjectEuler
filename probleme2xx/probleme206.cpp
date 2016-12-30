#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"
#include "nombre.h"

#include <fstream>

typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;
typedef std::map<nombre, nombre> dictionnaire;

namespace
{
    bool test(nombre n)
    {
        auto chiffres = chiffres::extraire_chiffres(n);
        return chiffres[0] == 1 && chiffres[2] == 2 && chiffres[4] == 3 && chiffres[6] == 4 && chiffres[8] == 5 
            && chiffres[10] == 6 && chiffres[12] == 7 && chiffres[14] == 8 && chiffres[16] == 9 && chiffres[18] == 0;
    }
}

ENREGISTRER_PROBLEME(206, "Concealed Square")
{
    // Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0,
    // where each “_” is a single digit.
    nombre minimum = racine_carre(102030405060708LL); // 0900
    nombre maximum = racine_carre(192939495969798LL); // 9900
    
    nombre resultat = 0;
    for (nombre n = minimum; n < maximum; ++n)
    {
        nombre carre3 = (n*100 + 30) * (n*100 + 30);
        if (test(carre3))
        {
            resultat = n*100 + 30;
            break;
        }
        
        nombre carre7 = (n*100 + 70) * (n*100 + 70);
        if (test(carre7))
        {
            resultat = n*100 + 70;
            break;
        }
    }
     
    return resultat.to_string();
}
