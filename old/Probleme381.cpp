#include <iostream>
#include <set>

#include "Timer.h"
#include "Premiers.h"

#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int nombre;

class Probleme381
{
    // For a prime p let S(p) = (Sum(p-k)!) mod(p) for 1 ≤ k ≤ 5.
    //
    // For example, if p=7,
    // (7-1)! + (7-2)! + (7-3)! + (7-4)! + (7-5)! = 6! + 5! + 4! + 3! + 2! = 720+120+24+6+2 = 872.
    // As 872 mod(7) = 4, S(7) = 4.
    //
    // It can be verified that Sum S(p) = 480 for 5 ≤ p < 100.
    //
    // Find SumS(p) for 5 ≤ p < 108.
    
    size_t limite;
public:
    Probleme381(size_t _limite) : limite(_limite) { }
    
    static nombre factoriel(size_t n, size_t p)
    {
        nombre resultat = 1;
        for (size_t i = 1; i < n + 1; ++i)
            resultat *= i;
            
        return resultat % p;
    }
    
    static nombre S(size_t p)
    {
        if (p < 5)
            return 0;
        
        size_t f = p - 1;
        // std::cout << p - 1 << "! mod " << p << " = " << f << std::endl;
        nombre resultat = f;
        for (size_t n = 2; n < 6; ++n)
        {
            f *= puissance(p - n + 1, p - 2, p);
            f %= p;
            // std::cout << p - n << "! mod " << p << " = " << f << std::endl;
            resultat += f;
        }
        
        return resultat % p;
    }
    
    static size_t puissance(size_t a, size_t n, size_t p)
    {
        size_t resultat = 1;
        while (n > 0)
        {
            if (n%2)
                resultat = (resultat * a)%p;
            
            a = (a * a)%p;
            n /= 2;
        }
        
        return resultat;
    }
    
    void algorithme()
    {
        std::vector<size_t> premiers;
        {
            Timer t("crible");
            premiers::crible(limite, premiers);
        }
        
        {
            Timer t("algorithme");
            nombre resultat = 0;
            for (const size_t & p : premiers)
            // for (size_t i = 5; i < limite; ++i)
            {
                nombre s = S(p);
                resultat += s;
                // std::cout << p << " = " << s << std::endl;
            }
            
            std::cout << "Resultat = " << resultat << std::endl;
        }   
    }
};

int main(int argc, char** argv)
{
    size_t limite = 0;
    if (argc > 1)
    {
        limite = atol(argv[1]);
    }
    else
    {
        std::cout << "Limite : " << std::endl;
        std::cin >> limite;
    }
    
    std::cout << "2^5 % 5 = " << Probleme381::puissance(2, 5, 5) << std::endl;
    
    Probleme381 p(limite);
    p.algorithme();
    return 0;
}
