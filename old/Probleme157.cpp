#include <iostream>
#include <cstdlib>
#include <set>
#include <map>

#include "Timer.h"

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

typedef unsigned long long nombre;
typedef std::set<nombre> ensemble; 

class Probleme157
{
    // Consider the diophantine equation 1/a+1/b= p/10^n with a, b, p, n positive integers and a ≤ b.
    // For n=1 this equation has 20 solutions that are listed below:
    // 
    // 1/1+1/1=20/10	1/1+1/2=15/10	1/1+1/5=12/10	1/1+1/10=11/10	1/2+1/2=10/10
    // 1/2+1/5=7/10	    1/2+1/10=6/10	1/3+1/6=5/10	1/3+1/15=4/10	1/4+1/4=5/10
    // 1/4+1/20=3/10	1/5+1/5=4/10	1/5+1/10=3/10	1/6+1/30=2/10	1/10+1/10=2/10
    // 1/11+1/110=1/10	1/12+1/60=1/10	1/14+1/35=1/10	1/15+1/30=1/10	1/20+1/20=1/10
    //
    // How many solutions has this equation for 1 ≤ n ≤ 9?
    nombre limite;
public:
    Probleme157(nombre limite_) : limite(limite_) {}
    ~Probleme157() {}
    
    nombre puissance(nombre a, nombre p)
    {
        nombre resultat = 1;
        while (p > 0)
        {
            if (p%2 == 1)
                resultat *= a;
            a = a*a;
            p /= 2;
        }
        
        return resultat;
    }
    
    nombre PGCD(nombre a, nombre b)
	{
		nombre pgcd = 0;
		while (true)
		{
			pgcd = a % b;
			if(pgcd == 0)
			{
				pgcd = b;
				break;
			}
			a = b;
			b = pgcd;
		}
		return pgcd;
	}
    
    void affiche(const ensemble & e)
    {
        BOOST_FOREACH(nombre n, e)
        {
            std::cout << n << " ";    
        }
        std::cout << std::endl;
    }
    
    void fusion(const ensemble & e1, const ensemble & e2, ensemble & s)
    {
        s.clear();
        BOOST_FOREACH(nombre n, e1)
        {
            BOOST_FOREACH(nombre m, e2)
            {
                s.insert(n*m);
            }
        }
    }
    
    nombre compte_diviseur(nombre d)
    {
        nombre compteur = 0;
        for (nombre n = 1; n * n < d + 1; ++n)
        {
            if (d%n == 0)
            {
                ++compteur;
                nombre q = d/n;
                if (q != n)
                    ++compteur;
            }
        }
        return compteur;
    }
    
    void algorithme()
    {
        Timer t("algorithme");
        nombre resultat = 0;
        for (nombre n = 1; n < limite + 1; ++n)
        {
            nombre m = puissance(10, n);
            ensemble d2;
            ensemble d5;
            for (nombre p = 0; p < n + 1; ++p)
            {
                d2.insert(puissance(2, p));
                d5.insert(puissance(5, p));
            }
            
            ensemble diviseurs;
            fusion(d2, d5, diviseurs);
            
            nombre resultat_n = 0;
            
            BOOST_FOREACH(nombre b, diviseurs)
            {
                BOOST_FOREACH(nombre a, diviseurs)
                {
                    if (a > b)
                        break;
                    if (a * b > m)
                        break;
                        
                    if (PGCD(a, b) != 1)
                        continue;
                        
                    nombre p = m * (a + b) / a / b;
                    std::cout << "(a,b,p) = (" << a << ", " << b << ", " << p << ")" << std::endl;
                    resultat_n += compte_diviseur(p);
                }
            }
            std::cout << "Solutions(" << n << ") = " << resultat_n << std::endl;
            resultat += resultat_n;
        }
        
        std::cout << "Resultat " << resultat << std::endl;
    }
};

int main(int argc, char** argv)
{
    nombre limite = 0;
    if (argc == 2)
    {
        limite = atol(argv[1]);
    }
    else
    {
        std::cout << "Limite : ";
        std::cin >> limite;
    }
    Probleme157 p(limite);
    p.algorithme();
    return 0;
}

