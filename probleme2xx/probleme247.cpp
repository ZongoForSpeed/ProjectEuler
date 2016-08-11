#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"
#include "polygonal.h"

#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    class Square
    {
    public:
        std::pair<long double, long double> coordonnees;
        std::pair<nombre, nombre> index;
        long double taille;
        
        std::pair<Square, Square> suivant() const
        {
            Square s1(*this);
            s1.index.first++;
            s1.coordonnees.first += taille;
            s1.calcul_taille();
            
            Square s2(*this);
            s2.index.second++;
            s2.coordonnees.second += taille;
            s2.calcul_taille();
            
            return std::make_pair(s1, s2);
        }
        
        void calcul_taille()
        {
            // x² + (x_a - y_b).x - 1 = 0
            const long double b = (coordonnees.second - coordonnees.first);
            const long double delta = b*b + 4.0L;
            if (delta > 0)
            {
                taille = (std::sqrt(delta) - b) / 2.0L - coordonnees.first;
            }
            else
            {
                taille = std::numeric_limits<long double>::quiet_NaN();
            }
        }
        
        bool operator<(const Square & s) const
        {
            return taille > s.taille;
        }
    };
    
    std::ostream& operator <<(std::ostream& os, const Square & s)
    {
        os << s.coordonnees << " " << s.index << " = " << s.taille;
        return os;
    }
} 

ENREGISTRER_PROBLEME(247, "Squares under a hyperbola")
{
    // Consider the region constrained by 1 ≤ x and 0 ≤ y ≤ 1/x.
    //
    // Let S1 be the largest square that can fit under the curve.
    // Let S2 be the largest square that fits in the remaining area, and so on. 
    // Let the index of Sn be the pair (left, below) indicating the number of 
    // squares to the left of Sn and the number of squares below Sn.
    //
    // The diagram shows some such squares labelled by number. 
    // S2 has one square to its left and none below, so the index of S2 is (1,0).
    // It can be seen that the index of S32 is (1,1) as is the index of S50. 
    // 50 is the largest n for which the index of Sn is (1,1).
    //
    // What is the largest n for which the index of Sn is (3,3)?
    const std::pair<nombre, nombre> objectif(3, 3);
    Square s1;
    s1.coordonnees = std::make_pair(1.0, 0.0);
    s1.index = std::make_pair(0, 0);
    s1.calcul_taille();
    
    std::set<Square> squares { s1 };
    
    nombre resultat = 0;
    nombre compteur = 1;
    while (compteur > 0)
    {
        ++resultat;
        Square sn = *(squares.begin());
        
        if (sn.index.first <= objectif.first && sn.index.second <= objectif.second)
            --compteur;
        squares.erase(squares.begin());
        
        auto suivant = sn.suivant();
        
        if (suivant.first.index.first <= objectif.first && suivant.first.index.second <= objectif.second)
            ++compteur;
            
        
        if (suivant.first.index.first <= objectif.first && suivant.first.index.second <= objectif.second)
            ++compteur;
        
        squares.insert(suivant.first);
        squares.insert(suivant.second);
        
        if (/*sn.index == objectif || */compteur == 0)
        {
            std::cout << "S_" << resultat << " = " << sn << std::endl;
        }
    }

    return std::to_string(resultat);
}
