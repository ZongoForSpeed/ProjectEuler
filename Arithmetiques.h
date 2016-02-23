#pragma once

#include <cstdlib>

#include <algorithm>
#include <deque>
#include <map>

#include "Puissance.h"

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
            if (p*p > n)
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
        if (n > 1)
            d *= 2;
        
        return d;
    }
    
    template<typename Nombre, typename Conteneur>
    Nombre somme_diviseurs(Nombre n, const Conteneur & premiers)
    {
        Nombre s = 1;
        for (auto p: premiers)
        {
            if (p*p > n)
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
        if (n > 1)
            s *= (n + 1);
        
        return s;
    }
    
    template<typename Nombre, typename Exposant, typename Conteneur>
    Nombre fonction_diviseur(Nombre n, Exposant a, const Conteneur & premiers)
    {
        // https://fr.wikipedia.org/wiki/Fonction_diviseur
        Nombre s = 1;
        for (auto p: premiers)
        {
            if (p*p > n)
                break;
            if (n%p == 0)
            {
                Nombre compteur = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++compteur;
                }
                s *= (puissance::puissance(p, (compteur + 1)*a) - 1)/(puissance::puissance(p, a) - 1);
            }
        }
        if (n > 1)
            s *= (puissance::puissance(n, a) + 1);
        
        return s;
    }
    
    template<typename Nombre, typename Conteneur, typename Dictionnaire>
    void decomposition(Nombre n, const Conteneur & premiers, Dictionnaire & sortie)
    {
        for (const auto & p: premiers)
        {
            if (p*p > n)
                break;
            if (n%p == 0)
            {
                size_t compteur = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++compteur;
                }
                sortie[p] = compteur;
            }
        }
        if (n > 1)
            sortie[n] = 1;
    }
    
    template<typename Nombre, typename Conteneur>
    Nombre radical(Nombre n, const Conteneur & premiers)
    {
        Nombre resultat = 1;
        for (const auto & p: premiers)
        {
            if (p*p > n)
                break;
            if (n%p == 0)
            {
                while (n%p == 0)
                    n /= p;
                
                resultat *= p;
            }
        }
        if (n > 1)
            resultat *= n;
            
        return resultat;
    }
    
    template<typename Nombre1, typename Nombre2>
    Nombre1 nombre_facteur(Nombre1 n, Nombre2 d)
    {
        Nombre1 i = 0;
        while (n%d == 0)
        {
            n /= d;
            ++i;
        }
        
        return i;
    }
    
    template<typename Nombre, typename Conteneur>
    Nombre phi(Nombre n, const Conteneur & premiers)
    {
        Nombre resultat = n;
        for (const auto p: premiers)
        {
            if (p*p > n)
                break;
            if (n%p == 0)
            {
                resultat = resultat - resultat / p;
                while (n%p == 0) 
                    n /= p;
            }
        }
        if (n > 1)
        {
            resultat = resultat - resultat / n;
        }
        return resultat;
    }
    
    template<typename Nombre, typename Conteneur>
    short moebius(Nombre n, const Conteneur & premiers)
    {
        Nombre facteurs = 0;
        for (const auto & p: premiers)
        {
            if (p*p > n)
                break;
            if (n%p == 0)
            {
                Nombre compteur = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++compteur;
                }
                if (compteur > 1)
                    return 0;
                    
                ++facteurs;
            }
        }
        if (n > 1)
            ++facteurs;
            
        return (facteurs%2 == 0)?1:-1;
    }
    
    template<typename Nombre, typename Conteneur>
    bool facteur_carre(Nombre n, const Conteneur & premiers)
    {
        for (const auto & p: premiers)
        {
            if (p*p > n)
                break;
            if (n%p == 0)
            {
                Nombre compteur = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++compteur;
                }
                if (compteur > 1)
                    return true;
            }
        }
        return false;
    }
    
    template<typename Nombre, typename Conteneur>
    std::deque<Nombre> diviseurs(Nombre n, const Conteneur & premiers)
    {
        std::map<Nombre, size_t> d;
        decomposition<Nombre>(n, premiers, d);
        std::deque<Nombre> resultat { 1 };
        for (auto facteur: d)
        {
            std::deque<Nombre> r = resultat;
            Nombre p = facteur.first;
            for (size_t f = 0; f < facteur.second; ++f)
            {
                for (auto i: resultat)
                    r.push_back(i*p);
                p *= facteur.first;
            }
            
            resultat.swap(r);
        }
        
        std::sort(resultat.begin(), resultat.end());
        return resultat;
    }
    
    namespace repunit
    {
        template<typename Nombre>
        Nombre A(Nombre n, size_t base = 10)
    	{
    		Nombre k = 1;
    		Nombre q = (base - 1)*n;
            for (Nombre p = base%q; p%q != 1; p = (base*p)%q)
            {
                ++k;
            }
            
            return k;
    	}
    }

}
