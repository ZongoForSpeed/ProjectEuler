#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <map>
#include <set>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(155)
{
    Timer timer("probleme 155");
	// An electric circuit uses exclusively identical capacitors of the same value C. 
	// 
    // The capacitors can be connected in series or in parallel to form sub-units, which can then be
    // connected in series or in parallel with other capacitors or other sub-units to form larger 
    // sub-units, and so on up to a final circuit.
    // 
    // Using this simple procedure and up to n identical capacitors, we can make circuits having a 
    // range of different total capacitances. For example, using up to n=3 capacitors of 60 F each, we can obtain the following 7 distinct total capacitance values:
    //
    //If we denote by D(n) the number of distinct total capacitance values we can obtain when using 
    // up to n equal-valued capacitors and the simple procedure described above, we have: D(1)=1, 
    // D(2)=3, D(3)=7 ...
    // 
    // Find D(18).
    //
    // Reminder : When connecting capacitors C1, C2 etc in parallel, the total capacitance is 
    //                      CT = C1 + C2 +..., 
    // whereas when connecting them in series, the overall capacitance is given by: 
    //                      1/CT = 1/C1 + 1/C2 +...
    std::map<nombre, std::set<fraction>> capacite { {1, {fraction(1)}} };
    
    std::set<fraction> resultat;
    for (nombre n = 2; n < 19; ++n)
    {
        std::set<fraction> & c = capacite[n];
        for (nombre i = 1; i <= n/2; ++i)
        {
            nombre j = n-i;
            for (auto vi: capacite[i])
            for (auto vj: capacite[j])
            {
                c.insert(vi + vj);
                c.insert(1/(1/vi + 1/vj));
            }
        }
        resultat.insert(c.begin(), c.end());
    }
    
    std::cout << "Solution: " << resultat.size() << std::endl;
}
