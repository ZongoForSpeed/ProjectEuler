#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;

ENREGISTRER_PROBLEME(157, "Solving the diophantine equation 1/a+1/b= p/10n") {
    // Consider the diophantine equation 1/a+1/b= p/10^n with a, b, p, n positive integers and a ≤ b.
    // For n=1 this equation has 20 solutions that are listed below:
    // 
    // 1/1+1/1=20/10	1/1+1/2=15/10	1/1+1/5=12/10	1/1+1/10=11/10	1/2+1/2=10/10
    // 1/2+1/5=7/10	    1/2+1/10=6/10	1/3+1/6=5/10	1/3+1/15=4/10	1/4+1/4=5/10
    // 1/4+1/20=3/10	1/5+1/5=4/10	1/5+1/10=3/10	1/6+1/30=2/10	1/10+1/10=2/10
    // 1/11+1/110=1/10	1/12+1/60=1/10	1/14+1/35=1/10	1/15+1/30=1/10	1/20+1/20=1/10
    //
    // How many solutions has this equation for 1 ≤ n ≤ 9?
    vecteur premiers;
    premiers::crible235<nombre>(1000000000ULL, std::back_inserter(premiers));
    nombre limite = 9;
    nombre resultat = 0;
    for (nombre n = 1; n < limite + 1; ++n) {
        nombre m = puissance::puissance(10UL, n);
        vecteur d2;
        vecteur d5;
        for (nombre p = 0; p < n + 1; ++p) {
            d2.push_back(puissance::puissance(2UL, p));
            d5.push_back(puissance::puissance(5UL, p));
        }

        ensemble diviseurs;
        for (nombre i: d2)
            for (nombre j: d5)
                diviseurs.insert(i * j);

        nombre resultat_n = 0;

        for (nombre b: diviseurs)
            for (nombre a: diviseurs) {
                if (a > b)
                    break;
                if (a * b > m)
                    break;

                if (arithmetique::PGCD(a, b) != 1)
                    continue;

                nombre p = m * (a + b) / a / b;
                resultat_n += arithmetique::nombre_diviseurs(p, premiers);
            }
        std::cout << "Solutions(" << n << ") = " << resultat_n << std::endl;
        resultat += resultat_n;
    }

    return std::to_string(resultat);
}
