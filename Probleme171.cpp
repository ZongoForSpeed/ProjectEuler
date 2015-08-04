#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>

#include "Timer.h"

typedef unsigned char nombre;
typedef std::multiset<nombre> vecteur;
typedef std::set<vecteur> ensemble;
typedef std::map<size_t, ensemble> dictionnaire;

class Probleme171
{
    // For a positive integer n, let f(n) be the sum of the squares of the digits (in base 10) of n, e.g.
    //
    // f(3) = 3² = 9,
    // f(25) = 2² + 5² = 4 + 25 = 29,
    // f(442) = 4² + 4² + 2² = 16 + 16 + 4 = 36
    //
    // Find the last nine digits of the sum of all n, 0 < n < 10^20, such that f(n) is a perfect square.
    size_t limite;
public:
    static bool carre(size_t n)
    {
        auto r = sqrt(n);
        return r*r == n;
    }

    Probleme171(size_t _limite) : limite(_limite) {}
    
    void suivant(dictionnaire & d)
    {
        dictionnaire s;
        for (const auto & kv : d)
        {
            for (size_t n = 0; n < 10; ++n)
            {
                for (auto v : kv.second)
                {
                    v.insert(n);
                    s[kv.first+n*n].insert(v);
                }
            }
        }
        
        std::swap(s, d);
    }
    
    void affiche(const vecteur & v)
    {
        std::cout << "(";
        bool first = true;
        for (const auto & n : v)
        {
            if (!first)
                std::cout << ", ";
            else
                first = false;
            std::cout << std::to_string(n);
        }
        std::cout << ")";
    }
    
    void affiche(const ensemble & e)
    {
        std::cout << "[";
        bool first = true;
        for (const auto & v : e)
        {
            if (!first)
                std::cout << ", ";
            else
                first = false;
            affiche(v);
        }
        std::cout << "]";
    }
    
    void affiche(const dictionnaire & d)
    {
        for (const auto & kv : d)
        {
            std::cout << kv.first << " ==> ";
            affiche(kv.second);
            std::cout << std::endl;
        }
    }
    
    void algorithme()
    {
        dictionnaire d;
        {
            Timer t("algorithme");
            for (nombre n = 0; n < 10; ++n)
            {
                vecteur v;
                v.insert(n);
                d[n*n].insert(v);
            }
            
            affiche(d);
            
            for (size_t n = 1; n < limite; ++n)
                suivant(d);

            affiche(d);
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
    
    Probleme171 p(limite);
    p.algorithme();
    
    return 0;
}
