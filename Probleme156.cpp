#include "Problemes.h"
#include "Timer.h"
#include <iostream>
#include <map>
#include <set>
 
typedef long long nombre;
 
nombre compte(nombre n, nombre d)
{
    nombre resultat = 0;
    while (n > 0)
    {
        if (n%10 == d)
            ++resultat;
        n = n/10;
    }
 
    return resultat;
}
 
ENREGISTRER_PROBLEME(156, "Counting Digits")
{
    // Starting from zero the natural numbers are written down in base 10 like this: 
    // 
    //                              0 1 2 3 4 5 6 7 8 9 10 11 12....
    //
    // Consider the digit d=1. After we write down each number n, we will update the number of ones 
    // that have occurred and call this number f(n,1). The first values for f(n,1), then, are as 
    // follows:
    //
    //                                      n	f(n,1)
    //                                      0	0
    //                                      1	1
    //                                      2	1
    //                                      3	1
    //                                      4	1
    //                                      5	1
    //                                      6	1
    //                                      7	1
    //                                      8	1
    //                                      9	1
    //                                      10	2
    //                                      11	4
    //                                      12	5
    //
    // Note that f(n,1) never equals 3. 
    // So the first two solutions of the equation f(n,1)=n are n=0 and n=1. The next solution is 
    // n=199981.
    //
    // In the same manner the function f(n,d) gives the total number of digits d that have been written 
    // down after the number n has been written. 
    // In fact, for every digit d ≠ 0, 0 is the first solution of the equation f(n,d)=n.
    //
    // Let s(d) be the sum of all the solutions for which f(n,d)=n. 
    // You are given that s(1)=22786974071.
    //
    // Find ∑ s(d) for 1 ≤ d ≤ 9.
    //
    // Note: if, for some n, f(n,d)=n for more than one value of d this value of n is counted again for
    // every value of d for which f(n,d)=n.
    nombre limite = 1000000000000;
    nombre m = 100000;
 
    nombre resultat = 0;
    {
    	Timer t("algorithme");
        for (nombre d = 1; d < 10; ++d)
        {
            std::map< std::pair<nombre, nombre>, std::set<nombre> > gn;
            nombre f = 0;
            
            nombre s = 0;
            for (nombre b = 0; b < m; ++b)
            {
                f = f + compte(b, d);
                for (nombre x = 0; x < 10; ++x)
                {
                    nombre g = (b+1)*x + f - b;
                    gn[std::make_pair(g, x)].insert(b);
                }
                
                if (f == b)
                    s += b;
            }
            
            nombre fa = 0;
            for (nombre a = 1; a < limite / m; ++a)
            {
                nombre x = compte(a, d);
                nombre g = m*a - m*fa - a*f;
                fa += x;
                auto find = gn.find(std::make_pair(g, x));
                if (find != gn.end())
                {
                    for (const auto & b : find->second)
                    {
                        s += m*a + b;
                    }
                }
            }
            std::cout << "s(" << d << ") = " << s << std::endl;
            resultat += s;
        }
    }
    std::cout << "Resultat = " << resultat << std::endl;
}
