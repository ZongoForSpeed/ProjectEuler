#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    size_t calcul_position(size_t n)
    {
        std::ostringstream oss;
        for (size_t i = 0; i < n; ++i)
            oss << i;
        const std::string S = oss.str();
        return S.size();
        // for (nombre i = 1; i < 100; ++i)
        // {
        //     const std::string n = std::to_string(i);
        //     size_t position = 0;
        //     size_t compteur = 0;
        //     while (compteur < i)
        //     {
        //         position = S.find(n, position + 1);
        //         ++compteur;
        //     }
        //     std::cout << "f(" << i << ") = " << position << std::endl;
        // }
    }
    
    size_t calcul_position2(size_t n)
    {
        static std::vector<size_t> positions_dizaine;
        if (positions_dizaine.empty())
        {
            positions_dizaine.push_back(1);
            for (size_t i = 1; i < 15; ++i)
            {
                positions_dizaine.push_back(9 * puissance::puissance<size_t>(10, i - 1) * i + positions_dizaine.back());
            }
        }
        
        const size_t c = chiffres::nombre_chiffres(n);
        return positions_dizaine[c-1] + (n - puissance::puissance<size_t>(10, c - 1)) * c;
    }
    
    std::deque<std::pair<size_t, size_t>> split(size_t n)
    {
        std::deque<std::pair<size_t, size_t>> resultat;
        
        for (size_t p = 10; p < n; p *= 10)
        {
            size_t a = n / p;
            size_t b = n % p;
            if (b < p / 10)
                continue;
            
            resultat.push_back(std::make_pair(a, b));
        }
        
        return resultat;
    }
    
    std::deque<std::deque<size_t>> enumeration(size_t n)
    {
        size_t taille = chiffres::nombre_chiffres(n);
        std::deque<std::deque<size_t>> resultat;    
        for (size_t i = 0; i < n; ++i)
        {
            auto chiffres = chiffres::extraire_chiffres(i);
            do
            {
                if (!chiffres.empty())
                    resultat.push_back(chiffres);
                
                chiffres.push_front(0);
            }
            while (chiffres.size() <= taille);
        }
        
        return resultat;
    }
    
    template<typename Iterator1, typename Iterator2>
    size_t fusion(Iterator1 first1, Iterator1 it, Iterator1 last1, Iterator2 first2, Iterator2 last2)
    {
        auto lambda = [](const size_t resultat, const size_t chiffre) { return 10*resultat + chiffre; };
        size_t resultat = chiffres::conversion_nombre<size_t>(first1, it);
        resultat = std::accumulate(first2, last2, resultat, lambda);
        resultat = std::accumulate(it, last1, resultat, lambda);
        return resultat;
    }
    
    template<typename Iterator1, typename Iterator2>
    size_t fusion2(Iterator1 first1, Iterator1 it, Iterator1 last1, Iterator2 first2, Iterator2 last2)
    {
        auto lambda = [](const size_t resultat, const size_t chiffre) { return 10*resultat + chiffre; };
        size_t resultat = chiffres::conversion_nombre<size_t>(it, last1);
        resultat = std::accumulate(first2, last2, resultat, lambda);
        resultat = std::accumulate(first1, it, resultat, lambda);
        return resultat;
    }
    
    size_t f(size_t n)
    {
        const auto e = enumeration(n);
        std::set<size_t> solution;
        
        auto chiffres = chiffres::extraire_chiffres(n);
        for (const auto & c: e)
        {
            for (auto it = c.begin(), en = c.end(); it != en; ++it)
            {
                auto p = fusion(c.begin(), it, c.end(), chiffres.begin(), chiffres.end());
                solution.insert(p);
            }
            
            {
                auto p = fusion(c.begin(), c.end(), c.end(), chiffres.begin(), chiffres.end());
                solution.insert(p);
            }
        }
        
        for (auto it = chiffres.begin(), en = chiffres.end(); it != en; ++it)
        {
            for (const auto & c: e)
            {
                auto p = fusion2(chiffres.begin(), it, chiffres.end(), c.begin(), c.end());
                solution.insert(p);
            }
        }
        
        // solution.resize(n);
        std::cout << solution << std::endl;
        size_t resultat = 0;
        
        return resultat;
    }
}

ENREGISTRER_PROBLEME(305, "Reflexive Position")
{
    // Let's call S the (infinite) string that is made by concatenating the 
    // consecutive positive integers (starting from 1) written down in base 10.
    // Thus, S = 1234567891011121314151617181920212223242...
    //
    // It's easy to see that any number will show up an infinite number of times
    // in S.
    //
    // Let's call f(n) the starting position of the nth occurrence of n in S.
    // For example, f(1)=1, f(5)=81, f(12)=271 and f(7780)=111111365.
    //
    // Find ∑f(3k) for 1≤k≤13.
    const std::vector<size_t> tests {/*10, 100, 1000, */1, 5, 12, /*7780*//*, 10000, 100000*/};
    for (size_t t: tests)
    {
        std::cout << "calcul_position(" << t << ") = " << calcul_position(t) 
            << " ?= " << calcul_position2(t) << std::endl;
        std::cout << "f(" << t << ") = " << f(t) << std::endl;
        std::cout << "split(" << t << ") = " << split(t) << std::endl;
        std::cout << "enumeration(" << t << ")" << enumeration(t) << std::endl;
    }
 
    // 18174995535140
    // size_t limite = 13;
    // for (size_t k = 1; k <= limite; ++k)
    // {
    //     std::cout << puissance::puissance<nombre>(3, k) << std::endl;
    // }
    
    // std::ostringstream oss;
    // for (size_t i = 0; i < 1000000; ++i)
    //     oss << i;
    // const std::string S = oss.str();
    
    // for (nombre i = 1; i < 100; ++i)
    // {
    //     const std::string n = std::to_string(i);
    //     size_t position = 0;
    //     size_t compteur = 0;
    //     while (compteur < i)
    //     {
    //         position = S.find(n, position + 1);
    //         ++compteur;
    //     }
        
    //     std::cout << "f(" << i << ") = " << position << std::endl;
    // }

    nombre resultat = 0;
    return std::to_string(resultat);
}
