#pragma once

#include <iterator>
#include <vector>
#include <set>
#include <deque>
#include <numeric>
#include <cmath>
#include <algorithm>

namespace puissance
{
    template<typename Nombre1, typename Nombre2, typename Nombre3>
    Nombre1 puissance_modulaire(Nombre1 base, Nombre2 exposant, Nombre3 modulo)
    {
        Nombre1 resultat = 1;
        while (exposant > 0)
        {
            if (exposant%2)
                resultat = (base * resultat)%modulo;
            exposant /= 2;
            base = (base * base)%modulo;
        }
        return resultat;
    }

    template<typename Nombre1, typename Nombre2>
    Nombre1 puissance(Nombre1 base, Nombre2 exposant)
    {
        Nombre1 resultat = 1;
        while (exposant > 0)
        {
            if (exposant%2)
                resultat *= base;
            exposant /= 2;
            base *= base;
        }

        return resultat;
    }
}

namespace arithmetiques
{
    template<typename Nombre>
    Nombre PGCD(Nombre a, Nombre b)
    {
        Nombre pgcd = 0;
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
    
    template<typename Nombre>
    Nombre PPCM(Nombre a, Nombre b)
    {
        return (a*b) / PGCD(a,b);
    }
    
    template<typename Nombre, typename Conteneur>
    Nombre nombre_diviseurs(Nombre n, const Conteneur & premiers)
    {
        Nombre d = 1;
        for (auto p: premiers)
        {
            if (n == 1)
                break;
            if (n%p == 0)
            {
                Nombre compteur = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++compteur;
                }
                d *= compteur + 1;
            }
        }
        
        return d;
    }
    
    template<typename Nombre, typename Conteneur>
    Nombre somme_diviseurs(Nombre n, const Conteneur & premiers)
    {
        Nombre s = 1;
        for (auto p: premiers)
        {
            if (n == 1)
                break;
            if (n%p == 0)
            {
                Nombre compteur = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++compteur;
                }
                s *= (puissance::puissance(p, compteur + 1) - 1)/(p - 1);
            }
        }
        
        return s;
    }
    
    template<typename Nombre, typename Conteneur, typename Dictionnaire>
    void decomposition(Nombre n, const Conteneur & premiers, Dictionnaire & sortie)
    {
        for (auto p: premiers)
        {
            if (n == 1)
                break;
            if (n%p == 0)
            {
                Nombre compteur = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++compteur;
                }
                sortie[p] = compteur;
            }
        }
    }
    
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
    };

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
}

namespace premiers
{
    void internal_crible2(std::size_t taille, std::vector<bool> & test);
    
    void internal_crible23(std::size_t taille, std::vector<bool> & test1, std::vector<bool> & test5);

    template<typename Nombre, class OutputIterator>
    OutputIterator crible(std::size_t taille, OutputIterator sortie)
    {
        std::size_t taille_crible = taille / 2;
        std::vector<bool> test;
        internal_crible2(taille_crible, test);
        
        *sortie = 2;
        ++sortie;
        for (std::size_t p = 1; p < taille_crible; ++p)
        {
            if (test.at(p))
            {
                *sortie = Nombre(2*p + 1);
                ++sortie;    
            }
        }
        
        return sortie;
    }
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible23(std::size_t taille, OutputIterator sortie)
    {
        std::size_t taille_crible = taille / 6;
        std::vector<bool> test1;
        std::vector<bool> test5;
        internal_crible23(taille_crible, test1, test5);

        *sortie = 2;
        ++sortie;
        *sortie = 3;
        ++sortie;
        for (std::size_t p = 0; p < taille_crible; ++p)
        {
            if (test1.at(p))
            {
                *sortie = Nombre(6*p + 1);
                ++sortie;
            }

            if (test5.at(p))
            {
                *sortie = Nombre(6*p + 5);
                ++sortie;
            }
        }

        return sortie;
    }

    void testCrible();
}

namespace bezout
{
    class Bezout
    {
        int _u, _v;
        unsigned int _pgcd;
    public:
        Bezout(unsigned int a, unsigned int b);
        unsigned int pgcd() const { return _pgcd; }
        int u() const { return _u; }
        int v() const { return _v; }
    };
    
    unsigned int inverse_mod(unsigned int a, unsigned int n);
    int chinois(unsigned int a, unsigned int n, unsigned int b, unsigned int m);
}

namespace combinatoire
{
    template<typename Nombre>
    Nombre coefficient_binomial(Nombre n, Nombre p)
    {
        if (p < 1 || n < p)
            return Nombre(1);
        if (p > n/2)
            p = n-p;
        Nombre numerateur = 1;
        Nombre denominateur = 1;
        for (Nombre k = 0; k < p; ++k)
        {
            numerateur *= (n - k);
            denominateur *= (k + 1);
        }
        
        return numerateur / denominateur;
    }
    
    template<typename Nombre>
    Nombre factoriel(Nombre n)
    {
        Nombre resultat = 1;
        for (Nombre k = 2; k <= n; ++k) resultat *= k;
        return resultat;
    }
}

namespace polygonal
{
    template<typename Nombre>
    Nombre triangulaire(Nombre n)
    {
        return n*(n+1)/2;
    }

    template<typename Nombre>
    Nombre pentagonal(Nombre n)
    {
        return n*(3*n-1)/2;
    }

    template<typename Nombre>
    bool est_pentagonal(Nombre n)
    {
        Nombre delta = 1 + 24*n;
        Nombre racine_delta = std::sqrt(delta);
        if (racine_delta*racine_delta != delta)
            return false;
        return (1+racine_delta)%6 == 0;
    }

    template<typename Nombre>
    Nombre hexagonal(Nombre n)
    {
        return n*(2*n-1);
    }

    template<typename Nombre>
    bool est_hexagonal(Nombre n)
    {
        Nombre delta = 1 + 8*n;
        Nombre racine_delta = std::sqrt(delta);
        if (racine_delta*racine_delta != delta)
            return false;
        return (1+racine_delta)%4 == 0;
    }
    
    template<typename Nombre>
    bool est_carre(Nombre n)
    {
        Nombre racine = std::sqrt(n);
        return racine*racine == n;
    }
}
