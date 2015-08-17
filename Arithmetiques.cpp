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

    /*
    std::size_t internal_decode(const std::size_t & d)
    {
        std::size_t q = d / 8;
        switch(d%8)
        {
        case 0: 
            return (q*30 + 1);
        case 1: 
            return (q*30 + 7);
        case 2: 
            return (q*30 + 11);
        case 3: 
            return (q*30 + 13);
        case 4: 
            return (q*30 + 17);
        case 5: 
            return (q*30 + 19);
        case 6: 
            return (q*30 + 23);
        case 7: 
            return (q*30 + 29);
        default:
            return 0;
        }
    }
        
    std::size_t internal_encode(const std::size_t & n)
    {
        std::size_t q = n / 30;
        switch(n%30)
        {
        case 1: 
            return q*8;
        case 7: 
            return (q*8 + 1);
        case 11: 
            return (q*8 + 2);
        case 13: 
            return (q*8 + 3);
        case 17: 
            return (q*8 + 4);
        case 19: 
            return (q*8 + 5);
        case 23: 
            return (q*8 + 6);
        case 29: 
            return (q*8 + 7);
        default:
            return 0;
        }
    }
    
    template<typename N, class OutputIterator>
    OutputIterator crible235(std::size_t taille, OutputIterator sortie)
    {
        std::size_t taille_crible = (taille / 30 + 1) * 8;
        std::vector<bool> test(taille_crible, true);
        //  1   7   11  13  17  19  23  29
        //  0   1   2   3   4   5   6   7
            
        test.at(0) = false;
        for (std::size_t p = 1; p * p < taille_crible; ++p)
        {
            if (test.at(p))
            {
                std::size_t n = internal_decode(p);
                for (std::size_t k = n * n; k < taille; k += 2*n)
                    test.at(internal_encode(k)) = false;
            }
        }

        *sortie = 2; ++sortie;
        *sortie = 3; ++sortie;
        *sortie = 5; ++sortie;
        for (std::size_t p = 1; p < taille_crible; ++p)
        {
            if (test.at(p))
            {
                std::size_t n = internal_decode(p);
                if (n > taille)
                    break;
                *sortie = n;
                ++sortie;    
            }
        }
        
        return sortie;
    }
    */
    
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
