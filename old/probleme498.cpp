#include <iostream>
#include <cstdlib>
#include "timer.h"
#include <map> 
 
typedef unsigned long long nombre;

typedef std::pair<nombre, nombre> paire;
 
template<nombre p>
class Probleme498
{
    // For positive integers n and m, we define two polynomials F_n(x) = x^n and G_m(x) = (x-1)^m.
    // We also define a polynomial Rn,m(x) as the remainder of the division of F_n(x) by G_m(x).
    // For example, R_6,3(x) = 15x² - 24x + 10.
    //
    // Let C(n, m, d) be the absolute value of the coefficient of the d-th degree term of R_n,m(x).
    // We can verify that C(6, 3, 1) = 24 and C(100, 10, 4) = 227197811615775.
    //
    // Find C(10^13, 10^12, 10^4) mod 999999937.
    nombre n;
    nombre m;
    nombre d;
 
public:
    Probleme498(nombre _n, nombre _m, nombre _d) : n(_n), m(_m), d(_d) {}
 
    nombre addition(nombre a, nombre b)
    {
        return (a+b)%p;
    }
 
    nombre soustraction(nombre a, nombre b)
    {
        if (a > b)
            return (a-b)%p;
        else
            return (p+a-b)%p;
    }
 
    nombre produit(nombre a, nombre b)
    {
        return (a*b)%p;
    }
 
    nombre puissance(nombre a, nombre n)
    {
        nombre r = 1;
        while (n > 0)
        {
            if (n%2)
                r = produit(r, a);
            n /= 2;
            a = produit(a,a);
        }
        return r;
    }
 
    nombre inverse(nombre a)
    {
        return puissance(a, p - 2);
    }
 
    nombre division(nombre a, nombre b)
    {
        return produit(a, inverse(b));
    }
 
    nombre factoriel(nombre n)
    {
        return factoriel2(n).second;
    }
    
    paire factorise(nombre n)
    {
        nombre f = 0;
        while (n % p == 0)
        {
            n /= p;
            ++f;
        }
        
        return std::make_pair(f, n);
    }
    
    paire factoriel2(nombre n)
    {
        nombre i = 0;
        nombre resultat = 1;
        for (nombre i = p; i < n + 1; i += p)
        {
            paire fi = factorise(i);
            i += fi.first;
            resultat = produit(resultat, fi.second);
        }
 
        nombre reste = n % p;
        for (nombre i = 2; i < reste + 1; ++i)
            resultat = produit(resultat, i);
 
        nombre quotient = n / p;
        if (quotient%2)
            resultat = p - resultat;
 
        return std::make_pair(i, resultat);
    }
 
    nombre binomial(nombre n, nombre k)
    {
        paire fn = factoriel2(n);
        paire fk = factoriel2(k);
        paire fnk = factoriel2(n - k);
        if (fn.first > fk.first + fnk.first)
            return 0;
        return division(fn.second, produit(fk.second, fnk.second));
    }
 
    // nombre C(nombre n, nombre m, nombre d)
    // {
    //     nombre resultat = 0;
    //     bool first = true;
    //     nombre u = 0;
    //
    //     for (nombre i = d; i < m; ++i)
    //     {
    //         if (first)
    //         {
    //             u = produit(binomial(n, i), binomial(i, d));
    //             first = false;
    //         }
    //         else
    //         {
    //             u = division(produit(u, n - i + 1), i - d);
    //         }
    //         if ((i - d)%2)
    //             resultat = addition(resultat, u);
    //         else
    //             resultat = soustraction(resultat, u);
    //     }
    //
    //     return resultat;
    // }
 
    void algorithme()
    {
        Timer t("algorithme");
        
        nombre i = d;
        nombre resultat = 0;
        while (i < m)
        {
            nombre j = i;
            nombre u = produit(binomial(n, i), produit(i, d));
            if ((i -d)%2 == 0)
                u = p - u;
            
            nombre s = u;    
            std::cout << "u_" << i << " = " << u << std::endl;
     
            ++i;
            while (i < m)
            {
                nombre numerateur = n - i + 1;
                if ((n - i + 1) % p == 0)
                    break;
                else
                {
                    u = produit(u, n - i + 1);
                    u = division(u, i - d);
                    u = p - u;
                }
     
                s = addition(s, u);
                ++i;
            }
            
            std::cout << "s_" << i << " = " << s << std::endl;
            i = j + p;
            
            resultat = addition(resultat, s);
        }
        
        std::cout << "Resultat = " << resultat << std::endl;
        if (resultat != 0)
            std::cout << " ou " << p - resultat << std::endl;
    }
};
 
 
int main(int argc, char** argv)
{
    Probleme498<3> p3(100, 10, 4);
    std::cout << "227197811615775LL % 3 = " << 227197811615775LL % 3 << std::endl;
    p3.algorithme();

    Probleme498<5> p5(100, 10, 4);
    std::cout << "227197811615775LL % 5 = " << 227197811615775LL % 5 << std::endl;
    p5.algorithme();

    Probleme498<7> p7(100, 10, 4);
    std::cout << "227197811615775LL % 7 = " << 227197811615775LL % 7 << std::endl;
    p7.algorithme();


    // Probleme498<999999937> p(10000000000000LL, 1000000000000LL, 10000);
    // Probleme498 p(10000000000000LL, 10000 + 999999937, 10000, 999999937);
    // p.algorithme();
    return 0;
}