#include "problemes.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <functional>

#include <boost/multiprecision/cpp_int.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;

namespace
{
    long double f(long double alpha, nombre n, nombre N)
    {
        return (std::log(N) - n*std::log(1-alpha)) / (std::log(1+2*alpha) - std::log(1-alpha) );
    }
    
    long double recherche(std::function<long double(long double)> & f, 
                          long double gauche, 
                          long double droite, 
                          long double epsilon)
    {
        if (std::abs(gauche - droite) < epsilon)
            return (gauche + droite) / 2;
        long double lr = (gauche * 2 + droite) / 3;
        long double rl = (gauche + droite * 2) / 3;
        if (f(lr) > f(rl))
            return recherche(f, lr, droite, epsilon);
        else
            return recherche(f, gauche, rl, epsilon);
    }
}

ENREGISTRER_PROBLEME(267, "Binary Circles")
{
    // You are given a unique investment opportunity.
    //
    // Starting with £1 of capital, you can choose a fixed proportion, f, of your capital to bet on 
    // a fair coin toss repeatedly for 1000 tosses.
    //
    // Your return is double your bet for heads and you lose your bet for tails.
    //
    // For example, if f = 1/4, for the first toss you bet £0.25, and if heads comes up you win £0.5
    // and so then have £1.5. You then bet £0.375 and if the second toss is tails, you have £1.125.
    // 
    // Choosing f to maximize your chances of having at least £1,000,000,000 after 1,000 flips, what
    // is the chance that you become a billionaire?
    //
    // All computations are assumed to be exact (no rounding), but give your answer rounded to 12 
    // digits behind the decimal point in the form 0.abcdefghijkl.
    const nombre n = 1000;
    const nombre N = puissance::puissance<nombre>(10, 9);
    
    std::function<long double(long double)> lambda_f = [n, N] (long double x) -> long double { return f(x, n, N); };
    
    const nombre alpha = static_cast<nombre>(std::ceil( f(recherche(lambda_f, 0.01, 0.99, 0.000001), n, N)));
    
    std::vector<boost::multiprecision::cpp_int> C { 1 };
    for (nombre k = 1; k < n + 1; ++k)
    {
        C.push_back(C.back() * (n - k + 1) / k);
    }
    
    boost::multiprecision::cpp_int resultat = 0;
    for (nombre k = alpha; k < n + 1; ++k)
    {
        resultat += C[k];
    }
    
    boost::multiprecision::cpp_int puissance = puissance::puissance<boost::multiprecision::cpp_int>(2, n);
    
    return std::to_string(static_cast<long double>(resultat) / static_cast<long double>(puissance), 12);
}
