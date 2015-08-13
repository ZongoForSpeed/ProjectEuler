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
 
void probleme156 ()
{
    // I used this formula:
    // Let M = 10^5, then for b < M
    //      f[Ma+b] = M*f[a-1] + a*f[M-1] + (b+1)*(f[a]-f[a-1]) + f[b]
    // So if Ma+b = f[Ma+b], we would have: Ma - M*f[a-1] - a*f[M-1] = (b+1)*(f[a]-f[a-1]) + f[b] - b (*)
    // I stored all the values of g = (b+1)*x + f[b] - b for 0 <= x <= 7, 0 <= b < M, where M=10^5 in hashmaps for easy lookup,
    // that is given g and x, I can look up the values of b that satisfy this equation.
    // Then I just iterated through 1 <= a < 10^7, and check for each value of a,
    // how many values of b satisfy equation (*) using the map lookup.
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
