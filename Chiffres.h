#pragma once

#include <algorithm>
#include <deque>
#include <numeric>
#include <sstream>
#include <vector>

namespace chiffres
{
    template<typename Nombre, class Operation>
    void boucle_chiffre(Nombre n, Operation op, std::size_t base = 10)
    {
        while (n != 0)
        {
            op(n%base);
            n /= base;
        }
    }
    
    template<typename Nombre>
    Nombre nombre_chiffres(Nombre n, std::size_t base = 10)
    {
        Nombre d = 0;
        boucle_chiffre(n, [&d](Nombre) { ++d; }, base);
        return d;
    }
     
    template<typename Nombre>
    Nombre somme_chiffres(Nombre n, std::size_t base = 10)
    {
        Nombre resultat = 0;
        boucle_chiffre(n, [&resultat] (Nombre d){ resultat = resultat + d; }, base);
        return resultat;
    }
    
    template<typename Nombre>
    std::deque<Nombre> extraire_chiffres(Nombre n, std::size_t base = 10)
    {
        std::deque<Nombre> resultat;
        boucle_chiffre(n, [&resultat](Nombre d){ resultat.push_front(d); }, base);
        return resultat;
    }
    template<typename Nombre>
    bool palindrome(Nombre n, std::size_t base = 10)
    {
        const auto chiffres = extraire_chiffres(n, base);
        return std::equal(chiffres.begin(), chiffres.begin() + chiffres.size()/2, chiffres.rbegin());
    }
    template<typename Nombre>
    bool pandigital(const Nombre & n, std::size_t base = 10)
    {
        std::vector<std::size_t> chiffres(base + 1, 0);
        boucle_chiffre(n, [&chiffres](Nombre d){ chiffres[d]++; }, base);
        if (chiffres[0] != 0)
            return false;
        for (auto c: chiffres)
            if (c > 1) return false;
        return true;
    }
    
    template<typename Nombre, class InputIterator1, class InputIterator2>
    Nombre conversion_nombre(InputIterator1 debut, InputIterator2 fin, std::size_t base = 10)
    {
        return std::accumulate(debut, fin, Nombre(0), [&base](const Nombre resultat, const Nombre chiffre) { return resultat*base + chiffre;});
    }
    
    template<typename Nombre>
    bool permutation_chiffres(Nombre n, Nombre m, std::size_t base = 10)
    {
        auto chiffres_n = extraire_chiffres(n, base);
        auto chiffres_m = extraire_chiffres(m, base);
        return std::is_permutation(chiffres_n.begin(), chiffres_n.end(), chiffres_m.begin());
    }
    
    // template<typename Nombre>
    // Nombre inverser_nombre(Nombre n, std::size_t base = 10)
    // {
    //     auto chiffres = extraire_chiffres(n, base);
    //     return conversion_nombre<Nombre>(chiffres.rbegin(), chiffres.rend(), base);
    // }
    
    template<typename Nombre>
    Nombre inverser_nombre(Nombre n, std::size_t base = 10)
    {
        Nombre resultat = 0;
        boucle_chiffre(n, [&resultat, &base] (Nombre d){ resultat = base*resultat + d; }, base);
        return resultat;
    }
    
    template<typename Nombre>
    Nombre concatener(Nombre a, Nombre b)
    {
        std::stringstream ss;
        ss << a << b;
        Nombre r;
        ss >> r;
        return r;
    }
    
    template<typename Nombre>
    Nombre concatener(Nombre a, Nombre b, Nombre c)
    {
        std::stringstream ss;
        ss << a << b << c;
        Nombre r;
        ss >> r;
        return r;
    }
        
    template<typename Nombre>
    Nombre concatener(Nombre a, Nombre b, Nombre c, Nombre d)
    {
        std::stringstream ss;
        ss << a << b << c << d;
        Nombre r;
        ss >> r;
        return r;
    }
}
