#pragma once

#include <cstdlib>
#include <vector>
#include <functional>

#include <boost/multiprecision/gmp.hpp>

namespace premiers
{
    void algorithme_crible2(const std::size_t & taille, std::function<void(const std::size_t &)> sortie);
    
    void algorithme_crible23(const std::size_t & taille, std::function<void(const std::size_t &)> sortie);
    
    void algorithme_crible235(const std::size_t & taille, std::function<void(const std::size_t &)> sortie);
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible2(const std::size_t & taille, OutputIterator sortie)
    {
        algorithme_crible2(taille, 
            [&sortie] (const std::size_t & p) { *sortie++ = Nombre(p); });
        return sortie;
    }
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible23(const std::size_t & taille, OutputIterator sortie)
    {
        algorithme_crible23(taille, 
            [&sortie] (const std::size_t & p) { *sortie++ = Nombre(p); });
        return sortie;
    }
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible235(const std::size_t & taille, OutputIterator sortie)
    {
        algorithme_crible235(taille, 
            [&sortie] (const std::size_t & p) { *sortie++ = Nombre(p); });
        return sortie;
    }
    
    bool test(const boost::multiprecision::mpz_int & n, int probabilite);
    
    void suivant(boost::multiprecision::mpz_int & n);
    void suivant(boost::multiprecision::mpz_int & n, const boost::multiprecision::mpz_int & p);

}
