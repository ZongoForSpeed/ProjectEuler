#include "Problemes.h"
#include "Premiers.h"
#include "Polygonal.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;

ENREGISTRER_PROBLEME(128, "Hexagonal tile differences")
{
    Timer t("probleme 128");
    // A hexagonal tile with number 1 is surrounded by a ring of six hexagonal tiles, starting at 
    // "12 o'clock" and numbering the tiles 2 to 7 in an anti-clockwise direction.
    //
    // New rings are added in the same fashion, with the next rings being numbered 8 to 19, 20 to 37, 
    // 38 to 61, and so on. The diagram below shows the first three rings.
    //
    // By finding the difference between tile n and each of its six neighbours we shall define PD(n) 
    // to be the number of those differences which are prime.
    // 
    // For example, working clockwise around tile 8 the differences are 12, 29, 11, 6, 1, and 13. 
    // So PD(8) = 3.
    // 
    // In the same way, the differences around tile 17 are 1, 17, 16, 1, 11, and 10, hence PD(17) = 2.
    // 
    // It can be shown that the maximum value of PD(n) is 3.
    // 
    // If all of the tiles for which PD(n) = 3 are listed in ascending order to form a sequence, 
    // the 10th tile would be 271.
    // 
    // Find the 2000th tile in this sequence.
    nombre limite = 20000000ULL;
    std::set<nombre> premiers;
    premiers::crible235<nombre>(limite, std::inserter(premiers, premiers.begin()));
    t.etape("fin crible");

    nombre objectif = 2000;
    
    nombre compteur = 0;
    nombre resultat = 0;
    for (nombre n = 1;; ++n)
    {
        nombre taille = 6*n;
        if (premiers.find(taille+1) != premiers.end()
            && premiers.find(taille-1) != premiers.end()
            && premiers.find(2*taille+5) != premiers.end())
        {
            ++compteur;
            if (compteur == objectif)
            {
                resultat = 2 + 6*polygonal::triangulaire(n - 1);
                
                break;
            }
        }
        
        if (premiers.find(taille-1) != premiers.end()
            && premiers.find(taille+5) != premiers.end()
            && premiers.find(2*taille-7) != premiers.end())
        {
            ++compteur;
            if (compteur == objectif)
            {
                resultat = 1 + 6*polygonal::triangulaire(n);
                break;
            }
        }
    }

    std::cout << "Solution: " << resultat << std::endl;
}
