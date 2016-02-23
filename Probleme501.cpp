#include "Problemes.h"
#include "Premiers.h"
#include "Puissance.h"
#include "Timer.h"

#include <iostream>
#include <vector>

#include <cmath>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

class Probleme501
{
    // The eight divisors of 24 are 1, 2, 3, 4, 6, 8, 12 and 24.
    // The ten numbers not exceeding 100 having exactly eight divisors are 24, 30, 40, 42, 54, 56, 66, 70, 78 and 88.
    // Let f(n) be the count of numbers not exceeding n with exactly eight divisors.
    // You are given f(100) = 10, f(1000) = 180 and f(10^6) = 224427.
    // Find f(10^12).
    nombre limite;
    
    vecteur _premiers;
    vecteur _pi;
public:
    Probleme501(nombre _limite = 1000000000000LL) : limite(_limite) {}
    
    static nombre racine_carre(nombre n)
    {
        return (nombre)sqrt(n);
    }
    
    static nombre racine_cubique(nombre n)
    {
        return (nombre)cbrt(n);
    }
    static nombre racine_septieme(nombre n)
    {
        nombre resultat = (nombre)pow(n, 1.0/7.0);
        auto p7 = puissance::puissance(resultat, 7);
        if (p7 < n)
        {
            do
            {
                ++resultat;
            }
            while (puissance::puissance(resultat, 7) < n);
            return resultat - 1;
        }
        else if (p7 > n)
        {
            do
            {
                --resultat;
            }
            while (puissance::puissance(resultat, 7) > n);
            return resultat + 1;
        }
        
        return resultat;
    }
    
    void crible()
    {
        nombre limite_crible = racine_cubique(limite) + 1;
        limite_crible *= limite_crible;
        premiers::crible<nombre>(limite_crible, std::back_inserter(_premiers));
        
        std::size_t dernier = 0;
        std::size_t compteur = 0;
        for (const auto & p : _premiers)
        {
            std::fill_n(std::back_inserter(_pi), p - dernier, compteur);
            ++compteur;
            dernier = p;
        }
    }
    
    size_t Phi(size_t m, size_t n)
    {
        if (n == 0)
            return m;
        if (m == 0)
            return 0;
            
        size_t pn = _premiers.at(n - 1);
            
        if (m < _pi.size() && pn <= racine_carre(m) && pn >= racine_cubique(m))
            return _pi.at(m) - n + 1 + P2(m, n);
        return Phi(m, n - 1) - Phi(m / pn, n - 1);
    }
    
    size_t pi2(size_t m)
    {
        if (m < _pi.size())
            return _pi.at(m);
        
        auto m3 = racine_cubique(m);
        auto n = _pi.at(m3);
        
        size_t resultat = 0;
        resultat += Phi(m, n);
        resultat += n - 1;
        resultat -= P2(m,n);
        return resultat;
    }
    
    size_t P2(size_t m, size_t n)
    {
        size_t resultat = 0;
        
        auto m2 = racine_carre(m);
        for (size_t i = n;; ++i)
        {
            auto pi = _premiers.at(i);
            if (pi > m2)
                break;
                
            resultat += _pi.at(m/pi) - _pi.at(pi) + 1;
        }
        
        return resultat;
    }
    
    void algorithme()
    {
        {
            Timer t("crible");
            crible();
        }
        
        {
            Timer t("algorithme");
            nombre resultat = 0;
            {
                // Forme p^7
                resultat += pi2(racine_septieme(limite));
            }
            
            {
                // Forme p1^3*p2 ou p1 != p2
                for (const size_t & p : _premiers)
                {
                    size_t p3 = puissance::puissance(p, 3);
                    if (2*p3 > limite)
                        break;
                    
                    auto r = pi2(limite / p3);
                    if (limite > p3 * p) --r;
                    resultat += r;
                }
            }
            
            {
                // Forme p1*p2*p3 ou p1 < p2 < p3
                auto l1 = racine_cubique(limite);
                for (size_t n1 = 0; n1 < _premiers.size(); ++n1)
                {
                    auto p1 = _premiers.at(n1);
                    if (p1 > l1)
                        break;
                
                    auto l2 = racine_carre(limite / p1);
                        
                    for (size_t n2 = n1 + 1; n2 < _premiers.size(); ++n2)
                    {
                        auto p2 = _premiers.at(n2);
                        if (p2 > l2)
                            break;
                            
                        auto l = limite / (p1 * p2);
                        
                        if (l <= p2)
                            break;
                        resultat += pi2(l) - n2 - 1;
                    }
                }
            }
            std::cout << "Resultat = " << resultat << std::endl;
        }
    }
};

ENREGISTRER_PROBLEME(501, "Eight Divisors")
{
    Probleme501 p;
    p.algorithme();
}
