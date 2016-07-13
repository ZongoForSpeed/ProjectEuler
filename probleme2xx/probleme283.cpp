#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(283, "Integer sided triangles for which the area/perimeter ratio is integral")
{
    // Consider the triangle with sides 6, 8 and 10. It can be seen that the 
    // perimeter and the area are both equal to 24. So the area/perimeter ratio 
    // is equal to 1.
    //
    // Consider also the triangle with sides 13, 14 and 15. The perimeter equals 
    // 42 while the area is equal to 84. So for this triangle the area/perimeter
    // ratio is equal to 2.
    //
    // Find the sum of the perimeters of all integer sided triangles for which 
    // the area/perimeter ratios are equal to positive integers not exceeding 
    // 1000.
    nombre limite = 1000;
    
    vecteur premiers;
    premiers::crible235<nombre>(10000000, std::back_inserter(premiers));
    
    nombre resultat = 0;
    // Cas des triangles rectangles 
    // for (nombre m = 1; m < limite + 1; ++m)
    // {
    //     nombre produit = 8*m*m;
    //     auto diviseurs = arithmetiques::diviseurs(produit, premiers);
    //    
    //     for (nombre delta1: diviseurs)
    //     {
    //         if (delta1*delta1 > produit)
    //             break;
    //      
    //         nombre delta2 = produit / delta1;
    //         nombre a = delta1 + 4*m;
    //         nombre b = delta2 + 4*m;
    //         nombre c = delta1 + delta2 + 4*m;
    //        
    //         resultat += a + b + c;
    //        
    //         std::cout << "(a, b, c) = " << std::make_tuple(a, b, c) << std::endl;
    //     }
    //    
    //     std::cout << "m = " << m << ", " << resultat << std::endl;
    // }
    
    // cf. article http://forumgeom.fau.edu/FG2007volume7/FG200718.pdf
    for (nombre m = 1; m < limite + 1; ++m)
    {
        // Pour un m donné, toutes les solutions du problème A = m.P sont déterminées
        // par:
        // Pout tous tous les diviseurs u de 2.m et v premier avec u tel que 
        // 1 ≤ v ≤ sqrt(3)*u
        // Il y a une identité : 
        // 4m²(u² + v²) = [v/(a - 2mv / u - 2mu].[v/(b - 2mv / u - 2mu]
        // avec c = a + b - 4mv/u
        for (nombre u: arithmetiques::diviseurs(2*m, premiers))
        {
            nombre borne_v = racine_carre(3*u*u);
            for (nombre v = 1; v <= borne_v; ++v)
            {
                if (arithmetiques::PGCD(u, v) == 1)
                {
                    // Toutes les factorisations de 4m²(u² + v²) = δ1 · δ2 va 
                    // produire des solutions de la forme :
                    //
                    // a = (δ1 + 2mu) / v + 2mv / u;
                    // b = (δ2 + 2mu) / v + 2mv / u;
                    // c = (δ1 + δ2 + 4mu) / v;
                    // 
                    // avec v | δ1 + 2mu and v | δ2 + 2mu
                    nombre produit = 4*m*m*(u*u + v*v);
                    auto diviseurs = arithmetiques::diviseurs(produit, premiers);
                    
                    for (nombre delta1: diviseurs)
                    {
                        // δ1 ≤ 2m.sqrt(u² + v²)
                        if (delta1 * delta1 > produit)
                            break;
                            
                        nombre delta2 = produit / delta1;
                        // 4m²(u² + v²) = δ1 · δ2,
                        if ((2*m*u + delta1)%v == 0 && (2*m*u + delta2)%v == 0)
                        {
                            // v | δ1 + 2mu and v | δ2 + 2mu
                            nombre a = (delta1 + 2*m*u) / v + 2*m*v / u;
                            nombre b = (delta2 + 2*m*u) / v + 2*m*v / u;
                            nombre c = (delta1 + delta2 + 4*m*u) / v;
                            
                            if (a <= c && b <= c)
                                resultat += a + b + c;
                        }
                    }
                }
            }
        }
    }
    
    return std::to_string(resultat);
}
