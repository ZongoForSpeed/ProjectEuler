#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(167, "Investigating Ulam sequences")
{
    Timer timer("probleme 167");
    // For two positive integers a and b, the Ulam sequence U(a,b) is defined by U(a,b)1 = a, 
    // U(a,b)2 = b and for k > 2, U(a,b)k is the smallest integer greater than U(a,b)(k-1) which
    // can be written in exactly one way as the sum of two distinct previous members of U(a,b).
    //
    // For example, the sequence U(1,2) begins with
    // 1, 2, 3 = 1 + 2, 4 = 1 + 3, 6 = 2 + 4, 8 = 2 + 6, 11 = 3 + 8;
    // 5 does not belong to it because 5 = 1 + 4 = 2 + 3 has two representations as the sum of two 
    // previous members, likewise 7 = 1 + 6 = 3 + 4.
    //
    // Find ∑U(2,2n+1)k for 2 ≤ n ≤10, where k = 1011.
    const nombre i = 100000000000ULL;
    nombre resultat = 0;
    for(nombre n = 2; n <= 10; n++) 
    {
        nombre x = 0;
        nombre y = 0;
        std::map<nombre, nombre> m;
        vecteur U {2*n + 1};
        
        do {
            m[U.back() + 2]++;
            if (x != 0)
            {
                m[U.back() + x]++;
            }
            else
            {
                for(size_t j = 0; j < U.size() - 1; j++)
                    m[U.back() + U[j]]++;
            }
            
            if (U.back()%2 == 0) 
            {
                x = U.back(); 
                y = U.size() - 1;
                for (auto & p: m)
                {
                    if (p.first%2 == 0) 
                        p.second++;
                }
            }
            
            auto mit = m.begin();
            while (mit->second > 1) 
                ++mit;
            U.push_back(mit->first);
            m.erase(m.begin(), ++mit);
        
        } 
        while (U.back() - U[U.size() - 2] != x);
        
        nombre periode = U.size() - 2;
        nombre diff = U.back() - U.front();

        nombre s = (i - 3) % periode;
        if (s >= y) s++;
        nombre u = ((i - 3) / periode) * diff + U[s];
        // std::cout << "  U(2, " << U[0] << ")_" << i 
        //     << " = U(2, " << U[0] << ")_" << s + 2 << " + " 
        //     << diff << " * " << (i - 3) / periode << " = " << u << std::endl;
        
        resultat += u;
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
