#include "premiers.h"
#include "timer.h"

#include <vector>
#include <deque>
#include <cstdlib>
#include <cassert>
#include <numeric>
#include <algorithm>

namespace
{
    template<typename Nombre, class OutputIterator>
    void crible_simple(const std::size_t taille, OutputIterator sortie)
    {
        std::vector<bool> test(taille, true);
        test.at(0) = false;
        test.at(1) = false;
        for (std::size_t p = 2; p * p < taille; ++p)
        {
            if (test.at(p))
            {
                for (std::size_t k = p*p; k < taille; k += p)
                    test.at(k) = false;
            }
        }
        for (std::size_t p = 2; p < taille; ++p)
        {
            if (test.at(p))
            {
                *sortie = Nombre(p);
                ++sortie;
            }
        }
    }  
    
    template<typename Nombre, class OutputIterator>
    OutputIterator super_crible(const std::size_t taille, const std::vector<std::size_t> & roue, OutputIterator sortie)
    {
        typedef std::vector<bool>                   Crible;
        typedef std::pair<std::size_t, std::size_t> Paire;
        typedef std::vector<Paire>                  VecteurPaire;
        typedef std::vector<VecteurPaire>           MatricePaire;
        typedef std::vector<std::size_t>            Vecteur;
        
        const std::size_t produit = std::accumulate(roue.begin(), roue.end(), 1UL, [] (const std::size_t resultat, const std::size_t p){ return resultat*p; });
        const std::size_t taille_crible = taille / produit + 1;
        
        Crible masque(produit, true);
        masque.at(0) = false;
        
        for (const std::size_t p: roue)
        for (std::size_t q = p; q < produit; q += p)
            masque.at(q) = false;
            
        Vecteur restes;
        for (std::size_t p = 0; p < produit; ++p)
            if (masque.at(p)) restes.push_back(p);
            
        const std::size_t profondeur = restes.size();
        std::deque<Crible> test;
        const VecteurPaire ligne(profondeur, std::make_pair(0,0));
        MatricePaire matrice(profondeur, ligne);
        
        for (std::size_t i = 0; i < profondeur; ++i)
        {
            const std::size_t reste = restes.at(i);
            test.push_back(std::vector<bool>());
            test.back().assign(taille_crible, true);
            // std::cout << "p = " << produit << ".k + " << reste << std::endl;
            
            for (std::size_t n = 0; n < produit; n += 2)
            {
                const std::size_t rrnr = reste*reste + n*reste;
                const auto it = std::find (restes.begin(), restes.end(), rrnr%produit);
                if (it != restes.end())
                {
                    // std::cout << "n = " << n << "\t";
                    // std::cout << produit << ".[ " << produit << ".k² + " << 2*reste + n << ".k + " << rrnr/produit << " ] + " << rrnr%produit << std::endl;
                    matrice[i][(size_t)std::distance(restes.begin(),it)] = std::make_pair(2*reste + n, rrnr/produit);
                }
            }
        }
        
        test[0][0] = false;
        for (std::size_t k = 0; produit*k*k < taille_crible; ++k)
        {
            for (std::size_t i = 0; i < profondeur; ++i)
            {
                if (test[i][k]) // Cas où p = produit*k + restes[i]
                {
                    const std::size_t p = produit*k + restes[i];
                    for (std::size_t j = 0; j < profondeur; ++j)
                    {
                        const auto & debut = matrice[i][j];
                        for (std::size_t l = produit*k*k + debut.first * k + debut.second; l < taille_crible; l += p) test[j][l] = false;
                    }
                }
            }
        }
        
        for (const auto p: roue)
        {
            *sortie = Nombre(p);
            ++sortie;
        }
        
        for (std::size_t k = 0; k < taille_crible; ++k)
        {
            for (std::size_t i = 0; i < profondeur; ++i)
            {
                if (test[i][k])
                {
                    *sortie = Nombre(produit*k + restes[i]);
                    ++sortie;
                }
            }
        }
        return sortie;
    }
}

namespace premiers
{
    void internal_crible2(std::size_t taille, std::vector<bool> & test)
    {
        test.assign(taille, true);
        test.at(0) = false;
        for (std::size_t p = 1; p * p < taille / 2; ++p)
        {
            if (test.at(p))
            {
                for (std::size_t k = 2*(p*p + p); k < taille; k += 2*p + 1)
                    test.at(k) = false;
            }
        }
    }
    
    void internal_crible23(std::size_t taille, std::vector<bool> & test1, std::vector<bool> & test5)
    {
        test1.assign(taille, true);
        test1.at(0) = false;
        test5.assign(taille, true);
        for (std::size_t k = 0; 6*k*k < taille; ++k)
        {
            // Cas p = 6*k + 1
            if (test1.at(k))
            {
                const std::size_t p = 6*k + 1;
                for (std::size_t l = 6*k*k + 2*k; l < taille; l+=p)
                    test1.at(l) = false;
                for (std::size_t l = 6*k*k + 6*k; l < taille; l+=p)
                    test5.at(l) = false;
            }
            // Cas p = 6*k + 5
            if (test5.at(k))
            {
                const std::size_t p = 6*k + 5;
                for (std::size_t l = 6*k*k + 10*k + 4; l < taille; l+=p)
                    test1.at(l) = false;
                for (std::size_t l = 6*k*k + 12*k + 5; l < taille; l+=p)
                    test5.at(l) = false;
            }
        }
    }
    
    void internal_crible235(std::size_t taille, std::vector<bool> & test1, std::vector<bool> & test7, std::vector<bool> & test11, std::vector<bool> & test13, std::vector<bool> & test17, std::vector<bool> & test19, std::vector<bool> & test23, std::vector<bool> & test29)
    {
        const std::size_t limite = taille;
        test1.assign(taille, true);
        test1.at(0) = false;
        test7.assign(taille, true);
        test11.assign(taille, true);
        test13.assign(taille, true);
        test17.assign(taille, true);
        test19.assign(taille, true);
        test23.assign(taille, true);
        test29.assign(taille, true);
        for (std::size_t k = 0; 30*k*k < taille; ++k)
        {
            if (test1.at(k))
            {
                const std::size_t p = 30*k+1;
                for (std::size_t l = 30*k*k + 2*k + 0; l < limite; l += p) test1.at(l) = false;
                for (std::size_t l = 30*k*k + 8*k + 0; l < limite; l += p) test7.at(l) = false;
                for (std::size_t l = 30*k*k + 12*k + 0; l < limite; l += p) test11.at(l) = false;
                for (std::size_t l = 30*k*k + 14*k + 0; l < limite; l += p) test13.at(l) = false;
                for (std::size_t l = 30*k*k + 18*k + 0; l < limite; l += p) test17.at(l) = false;
                for (std::size_t l = 30*k*k + 20*k + 0; l < limite; l += p) test19.at(l) = false;
                for (std::size_t l = 30*k*k + 24*k + 0; l < limite; l += p) test23.at(l) = false;
                for (std::size_t l = 30*k*k + 30*k + 0; l < limite; l += p) test29.at(l) = false;
            }
            if (test7.at(k))
            {
                const std::size_t p = 30*k+7;
                for (std::size_t l = 30*k*k + 14*k + 1; l < limite; l += p) test19.at(l) = false;
                for (std::size_t l = 30*k*k + 18*k + 2; l < limite; l += p) test17.at(l) = false;
                for (std::size_t l = 30*k*k + 20*k + 3; l < limite; l += p) test1.at(l) = false;
                for (std::size_t l = 30*k*k + 24*k + 3; l < limite; l += p) test29.at(l) = false;
                for (std::size_t l = 30*k*k + 26*k + 4; l < limite; l += p) test13.at(l) = false;
                for (std::size_t l = 30*k*k + 30*k + 5; l < limite; l += p) test11.at(l) = false;
                for (std::size_t l = 30*k*k + 36*k + 6; l < limite; l += p) test23.at(l) = false;
                for (std::size_t l = 30*k*k + 38*k + 7; l < limite; l += p) test7.at(l) = false;
            }
            if (test11.at(k))
            {
                const std::size_t p = 30*k+11;
                for (std::size_t l = 30*k*k + 22*k + 4; l < limite; l += p) test1.at(l) = false;
                for (std::size_t l = 30*k*k + 24*k + 4; l < limite; l += p) test23.at(l) = false;
                for (std::size_t l = 30*k*k + 28*k + 6; l < limite; l += p) test7.at(l) = false;
                for (std::size_t l = 30*k*k + 30*k + 6; l < limite; l += p) test29.at(l) = false;
                for (std::size_t l = 30*k*k + 34*k + 8; l < limite; l += p) test13.at(l) = false;
                for (std::size_t l = 30*k*k + 40*k + 10; l < limite; l += p) test19.at(l) = false;
                for (std::size_t l = 30*k*k + 42*k + 11; l < limite; l += p) test11.at(l) = false;
                for (std::size_t l = 30*k*k + 48*k + 13; l < limite; l += p) test17.at(l) = false;
            }
            if (test13.at(k))
            {
                const std::size_t p = 30*k+13;
                for (std::size_t l = 30*k*k + 26*k + 5; l < limite; l += p) test19.at(l) = false;
                for (std::size_t l = 30*k*k + 30*k + 7; l < limite; l += p) test11.at(l) = false;
                for (std::size_t l = 30*k*k + 32*k + 8; l < limite; l += p) test7.at(l) = false;
                for (std::size_t l = 30*k*k + 36*k + 9; l < limite; l += p) test29.at(l) = false;
                for (std::size_t l = 30*k*k + 42*k + 12; l < limite; l += p) test17.at(l) = false;
                for (std::size_t l = 30*k*k + 44*k + 13; l < limite; l += p) test13.at(l) = false;
                for (std::size_t l = 30*k*k + 50*k + 16; l < limite; l += p) test1.at(l) = false;
                for (std::size_t l = 30*k*k + 54*k + 17; l < limite; l += p) test23.at(l) = false;
            }
            if (test17.at(k))
            {
                const std::size_t p = 30*k+17;
                for (std::size_t l = 30*k*k + 34*k + 9; l < limite; l += p) test19.at(l) = false;
                for (std::size_t l = 30*k*k + 36*k + 10; l < limite; l += p) test23.at(l) = false;
                for (std::size_t l = 30*k*k + 40*k + 13; l < limite; l += p) test1.at(l) = false;
                for (std::size_t l = 30*k*k + 46*k + 16; l < limite; l += p) test13.at(l) = false;
                for (std::size_t l = 30*k*k + 48*k + 17; l < limite; l += p) test17.at(l) = false;
                for (std::size_t l = 30*k*k + 54*k + 20; l < limite; l += p) test29.at(l) = false;
                for (std::size_t l = 30*k*k + 58*k + 23; l < limite; l += p) test7.at(l) = false;
                for (std::size_t l = 30*k*k + 60*k + 24; l < limite; l += p) test11.at(l) = false;
            }
            if (test19.at(k))
            {
                const std::size_t p = 30*k+19;
                for (std::size_t l = 30*k*k + 38*k + 12; l < limite; l += p) test1.at(l) = false;
                for (std::size_t l = 30*k*k + 42*k + 14; l < limite; l += p) test17.at(l) = false;
                for (std::size_t l = 30*k*k + 48*k + 18; l < limite; l += p) test11.at(l) = false;
                for (std::size_t l = 30*k*k + 50*k + 19; l < limite; l += p) test19.at(l) = false;
                for (std::size_t l = 30*k*k + 56*k + 23; l < limite; l += p) test13.at(l) = false;
                for (std::size_t l = 30*k*k + 60*k + 25; l < limite; l += p) test29.at(l) = false;
                for (std::size_t l = 30*k*k + 62*k + 27; l < limite; l += p) test7.at(l) = false;
                for (std::size_t l = 30*k*k + 66*k + 29; l < limite; l += p) test23.at(l) = false;
            }
            if (test23.at(k))
            {
                const std::size_t p = 30*k+23;
                for (std::size_t l = 30*k*k + 46*k + 17; l < limite; l += p) test19.at(l) = false;
                for (std::size_t l = 30*k*k + 52*k + 22; l < limite; l += p) test7.at(l) = false;
                for (std::size_t l = 30*k*k + 54*k + 23; l < limite; l += p) test23.at(l) = false;
                for (std::size_t l = 30*k*k + 60*k + 28; l < limite; l += p) test11.at(l) = false;
                for (std::size_t l = 30*k*k + 64*k + 31; l < limite; l += p) test13.at(l) = false;
                for (std::size_t l = 30*k*k + 66*k + 32; l < limite; l += p) test29.at(l) = false;
                for (std::size_t l = 30*k*k + 70*k + 36; l < limite; l += p) test1.at(l) = false;
                for (std::size_t l = 30*k*k + 72*k + 37; l < limite; l += p) test17.at(l) = false;
            }
            if (test29.at(k))
            {
                const std::size_t p = 30*k+29;
                for (std::size_t l = 30*k*k + 58*k + 28; l < limite; l += p) test1.at(l) = false;
                for (std::size_t l = 30*k*k + 60*k + 29; l < limite; l += p) test29.at(l) = false;
                for (std::size_t l = 30*k*k + 66*k + 35; l < limite; l += p) test23.at(l) = false;
                for (std::size_t l = 30*k*k + 70*k + 39; l < limite; l += p) test19.at(l) = false;
                for (std::size_t l = 30*k*k + 72*k + 41; l < limite; l += p) test17.at(l) = false;
                for (std::size_t l = 30*k*k + 76*k + 45; l < limite; l += p) test13.at(l) = false;
                for (std::size_t l = 30*k*k + 78*k + 47; l < limite; l += p) test11.at(l) = false;
                for (std::size_t l = 30*k*k + 82*k + 51; l < limite; l += p) test7.at(l) = false;
                for (std::size_t l = 30*k*k + 88*k + 57; l < limite; l += p) test1.at(l) = false;
            }
        }
    }

    void testCrible()
    {
        std::size_t taille = 1000000000;
        std::deque<unsigned long long> premiers, premiers2, premiers23, premiers235, super_crible_premiers;
        {
            Timer t("test crible simple");
            crible_simple<unsigned long long>(taille, std::back_inserter(premiers));
            std::cout << "premiers.size() = " << premiers.size() << std::endl;
        }
        {
            Timer t("test crible2");
            crible<unsigned long long>(taille, std::back_inserter(premiers2));
            std::cout << "premiers2.size() = " << premiers2.size() << std::endl;
        }
        {
            Timer t("test crible23");
            crible23<unsigned long long>(taille, std::back_inserter(premiers23));
            std::cout << "premiers23.size() = " << premiers23.size() << std::endl;
        }
        {
            Timer t("test crible235");
            crible23<unsigned long long>(taille, std::back_inserter(premiers235));
            std::cout << "premiers235.size() = " << premiers235.size() << std::endl;
        }
        {
            Timer t("test super_crible");
            std::vector<std::size_t> roue {2, 3, 5};
            super_crible<unsigned long long>(taille, roue, std::back_inserter(super_crible_premiers));
            std::cout << "super_crible_premiers.size() = " << super_crible_premiers.size() << std::endl;
        }
    }
}
