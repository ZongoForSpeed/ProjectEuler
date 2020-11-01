#include "problemes.h"
#include "arithmetique.h"
#include "polygonal.h"

#include <fstream>
#include <numeric>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(141, "Investigating progressive numbers, n, which are also square") {
    // A positive integer, n, is divided by d and the quotient and remainder are q and r respectively. 
    // In addition d, q, and r are consecutive positive integer terms in a geometric sequence, but not necessarily in
    // that order.
    //
    // For example, 58 divided by 6 has quotient 9 and remainder 4. It can also be seen that 4, 6, 9 are consecutive
    // terms in a geometric sequence (common ratio 3/2).
    // We will call such numbers, n, progressive.
    //
    // Some progressive numbers, such as 9 and 10404 = 102², happen to also be perfect squares.
    // The sum of all progressive perfect squares below one hundred thousand is 124657.
    //
    // Find the sum of all progressive perfect squares below one trillion (1012).
    nombre limite = 1000000000000ULL;
    std::set<nombre> solutions;


    // m^2 = v*t*(s^3*v+t);
    for (nombre t = 1; t * t * (1 + t * t) < limite; ++t) {
        for (nombre s = t + 1; t * (t + s * s * s) < limite; ++s)
            if (arithmetique::PGCD(s, t) == 1) {
                nombre s_cube = s * s * s;
                for (nombre v = 1; v * t * (t + s_cube * v) < limite; ++v) {
                    nombre n = v * t * (t + s_cube * v);
                    if (polygonal::est_carre(n))
                        solutions.insert(n);
                }
            }
    }

    nombre resultat = std::reduce(solutions.begin(), solutions.end());
    return std::to_string(resultat);
}

