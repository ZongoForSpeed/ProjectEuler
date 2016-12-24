#pragma once

#include <cstdlib>
#include <vector>
#include <functional>

namespace premiers
{
    void algorithme_crible2(const std::size_t & taille, std::function<void(const std::size_t &)> sortie);
    
    void algorithme_crible23(const std::size_t & taille, std::function<void(const std::size_t &)> sortie);
    
    void algorithme_crible235(const std::size_t & taille, std::function<void(const std::size_t &)> sortie);
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible2(const std::size_t & taille, OutputIterator sortie)
    {
        auto lambda = [&sortie] (const std::size_t & p)
        {
            *sortie++ = Nombre(p);
        };
        
        algorithme_crible2(taille, lambda);
        return sortie;
    }
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible23(const std::size_t & taille, OutputIterator sortie)
    {
        auto lambda = [&sortie] (const std::size_t & p)
        {
            *sortie++ = Nombre(p);
        };
        
        algorithme_crible23(taille, lambda);
        return sortie;
    }
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible235(const std::size_t & taille, OutputIterator sortie)
    {
        auto lambda = [&sortie] (const std::size_t & p)
        {
            *sortie++ = Nombre(p);
        };
        
        algorithme_crible235(taille, lambda);
        return sortie;
    }
}
