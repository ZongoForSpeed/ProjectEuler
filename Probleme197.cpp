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
typedef std::pair<nombre, nombre> paire;

namespace
{
    long double f(long double x)
    {
        return std::floor(std::pow(2.0L, 30.403243784-x*x)) * 0.000000001;
    }
}

ENREGISTRER_PROBLEME(197, "Investigating the behaviour of a recursively defined sequence")
{
    Timer timer("probleme 197");
    // Given is the function f(x) = ⌊2^(30.403243784-x²)⌋ × 10-9 ( ⌊ ⌋ is the floor-function),
    // the sequence un is defined by u_0 = -1 and u_n+1 = f(u_n).
    // 
    // Find u_n + u_n+1 for n = 1012.
    // Give your answer with 9 digits after the decimal point.
    long double u_n = -1.0;
    long double u_n1 = f(u_n);
    long double resultat = 0.0;
    while (true)
    {
        long double u_n2 = f(u_n1);
        if (u_n2 == u_n)
        {
            resultat = u_n + u_n1;
            break;
        }
        u_n = u_n1;
        u_n1 = u_n2;
    }
    std::cout << std::setprecision(10);
    std::cout << "Solution: " << resultat << std::endl;
}
