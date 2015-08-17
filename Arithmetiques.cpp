#include "Arithmetiques.h"
#include "Timer.h"
#include <vector>
#include <cstdlib>
#include <cassert>
#include <numeric>

namespace premiers
{
    void internal_crible(std::size_t taille, std::vector<bool> & test)
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

    void testCrible(std::size_t taille)
    {
        {
            Timer t("test vecteur");
            std::vector<unsigned long long> premiers;
            crible(10000, premiers);
            std::cout << premiers.back() << std::endl;
        }
        {
            Timer t("test set");
            std::set<unsigned long long> premiers;
            crible(30, premiers);
            for (const auto & p : premiers)
            {
                std::cout << p << " ";
            }
            std::cout << std::endl;
        }
        {
            Timer t("test list");
            std::list<unsigned long long> premiers;
            crible(100, premiers);
            std::cout << std::accumulate(premiers.begin(), premiers.end(), 0) << std::endl;
        }
        {
            std::list<unsigned long long> premiers1;
            std::vector<unsigned long long> premiers2;
            {
                Timer t("test crible vector");
                crible(taille, premiers1);
            }
            
            {
                Timer t("test crible list");
                crible(taille, premiers2);
            }
            
            std::cout << "premiers1.size() = " << premiers1.size() << std::endl;
            std::cout << "premiers2.size() = " << premiers2.size() << std::endl;
            std::cout << "premiers1 == premiers2: " << std::boolalpha << std::equal(premiers1.begin(), premiers1.end(), premiers2.begin()) << std::endl;
            // for (auto it1 = premiers1.begin(), it2 = premiers2.begin(); it1 != premiers1.end() && it2 != premiers2.end(); ++it1, ++it2)
            // {
            //     std::cout << *it1 << " " << *it2 << std::endl;
            // }
        }
    }
}

namespace bezout
{
    Bezout::Bezout(unsigned int a, unsigned int b) 
    {
        _u = 1;
        _v = 0;
    
        int next_u = 0;
        int next_v = 1;
    
        while (b != 0) {
            unsigned int temp = b;
            unsigned int q = a / b;
            b = a % temp;
            a = temp;
    
            temp = _u;
            _u = next_u;
            next_u = temp - q * next_u;
            temp = _v;
            _v = next_v;
            next_v = temp - q * next_v;
        }
        _pgcd = a;
    }
    
    unsigned int inverse_mod(unsigned int a, unsigned int n) 
    {
        Bezout bezout(a, n);
        assert(bezout.pgcd() == 1);
        return  (bezout.u() < 0 ? bezout.u() + n : bezout.u()) % n;
    }
    
    int chinois(unsigned int a, unsigned int n, unsigned int b, unsigned int m) 
    {
        Bezout bezout(n, m);
        assert(bezout.pgcd() == 1);
        return (b * bezout.u() * n + a * bezout.v() * m) % (m*n);
    }
}
