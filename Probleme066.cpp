#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <algorithm>
#include <functional>

#include <boost/multiprecision/cpp_int.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::multiprecision::cpp_int grand_nombre;

ENREGISTRER_PROBLEME(66, "Diophantine equation")
{
    Timer t("probleme 66");
    // Consider quadratic Diophantine equations of the form:
    //
    //                                      x² – Dy² = 1
    //
    // For example, when D=13, the minimal solution in x is 649² – 13×180² = 1.
    //
    // It can be assumed that there are no solutions in positive integers when D is square.
    // 
    // By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:
    //
    //      3² – 2×2² = 1
    //      2² – 3×1² = 1
    //      9² – 5×4² = 1
    //      5² – 6×2² = 1
    //      8² – 7×3² = 1
    //
    // Hence, by considering minimal solutions in x for D ≤ 7, the largest x is obtained when D=5.
    //
    // Find the value of D ≤ 1000 in minimal solutions of x for which the largest value of x is obtained.
    auto fraction_continue = [] (nombre d)
    {
        vecteur resultat;
        nombre d2 = std::sqrt(d);
        unsigned long a = std::sqrt(d), p = 0, q = 1;
        do 
        {
            resultat.push_back(a);
            p = a * q - p;
            q = ( d - p * p ) / q;
            a = ( p + d2 ) /q;
        } 
        while ( q != 1 );
        resultat.push_back( a );
        return resultat;
    };
    
    auto equation_pell = [&fraction_continue] (nombre d) -> grand_nombre
    {
        const auto c = fraction_continue(d);
        size_t l = c.size() - 1;
        size_t per = l % 2 == 0 ? l - 1 :  2 * l - 1;
        grand_nombre a = c[ 0 ];
        grand_nombre a1 = 1;
        grand_nombre b = a;
        grand_nombre b1 = 0;
        for ( size_t i = 1; i <= per; i++ )
        {
            grand_nombre t = a;
            a = c[ ( i - 1 ) % l + 1 ] * a + a1;
            a1 = t;
            t = b;
            b = c[ ( i - 1 ) % l + 1 ] * b + b1;
            b1 = t;
        }
        return a;
    };
    
    grand_nombre maximum = 0;
    nombre resultat = 0;
    for ( nombre d = 2; d <= 1000; ++d )
    {
        if (!polygonal::est_carre(d)) 
        {
            grand_nombre x = equation_pell(d);
            if ( x > maximum ) 
            {
                maximum = x;
                resultat = d;
            }
        }
    }
    std::cout << "Solution: " << resultat << std::endl;
}
