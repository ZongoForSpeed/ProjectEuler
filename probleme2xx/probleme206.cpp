#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"
#include "mp_nombre.h"

#include <fstream>

typedef std::vector<mp_nombre> vecteur;
typedef std::pair<mp_nombre, mp_nombre> paire;
typedef std::map<mp_nombre, mp_nombre> dictionnaire;

namespace
{
    bool test(mp_nombre n)
    {
        auto chiffres = n.extraire_chiffres();
        return chiffres[0] == 1 && chiffres[2] == 2 && chiffres[4] == 3 && chiffres[6] == 4 && chiffres[8] == 5 
            && chiffres[10] == 6 && chiffres[12] == 7 && chiffres[14] == 8 && chiffres[16] == 9 && chiffres[18] == 0;
    }
}

ENREGISTRER_PROBLEME(206, "Concealed Square")
{
    // Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0,
    // where each “_” is a single digit.
    mp_nombre minimum = racine_carre(102030405060708LL); // 0900
    mp_nombre maximum = racine_carre(192939495969798LL); // 9900
    
    mp_nombre resultat = 0;
    for (mp_nombre n = minimum; n < maximum; ++n)
    {
        mp_nombre carre3 = (n*100 + 30) * (n*100 + 30);
        if (test(carre3))
        {
            resultat = n*100 + 30;
            break;
        }
        
        mp_nombre carre7 = (n*100 + 70) * (n*100 + 70);
        if (test(carre7))
        {
            resultat = n*100 + 70;
            break;
        }
    }
     
    return resultat.to_string();
}
