#pragma once

#include <cstdlib>
#include <vector>

namespace premiers
{
    void internal_crible2(std::size_t taille, std::vector<bool> & test);
    
    void internal_crible23(std::size_t taille, std::vector<bool> & test1, std::vector<bool> & test5);
    
    void internal_crible235(std::size_t taille, std::vector<bool> & test1, 
                                                std::vector<bool> & test7, 
                                                std::vector<bool> & test11, 
                                                std::vector<bool> & test13, 
                                                std::vector<bool> & test17, 
                                                std::vector<bool> & test19, 
                                                std::vector<bool> & test23, 
                                                std::vector<bool> & test29);
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible(std::size_t taille, OutputIterator sortie)
    {
        std::size_t taille_crible = taille / 2;
        std::vector<bool> test;
        internal_crible2(taille_crible, test);
        
        *sortie++ = 2;
        for (std::size_t p = 1; p < taille_crible; ++p)
        {
            if (test.at(p))
            {
                *sortie++ = Nombre(2*p + 1);
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
        *sortie++ = 2;
        *sortie++ = 3;
        for (std::size_t p = 0; p < taille_crible; ++p)
        {
            if (test1.at(p))
            {
                *sortie++ = Nombre(6*p + 1);
            }
            if (test5.at(p))
            {
                *sortie++ = Nombre(6*p + 5);
            }
        }
        return sortie;
    }
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible235(std::size_t taille, OutputIterator sortie)
    {
        std::size_t taille_crible = taille / 30 + 1;
        std::vector<bool> test1, test7, test11, test13, test17, test19, test23, test29;
        internal_crible235(taille_crible, test1, test7, test11, test13, test17, test19, test23, test29);
        *sortie++ = 2;
        *sortie++ = 3;
        *sortie++ = 5;
        for (std::size_t p = 0; p < taille_crible; ++p)
        {
            if (test1.at(p)) { *sortie++ = Nombre(30*p + 1); }
            if (test7.at(p)) { *sortie++ = Nombre(30*p + 7); }
            if (test11.at(p)) { *sortie++ = Nombre(30*p + 11); }
            if (test13.at(p)) { *sortie++ = Nombre(30*p + 13); }
            if (test17.at(p)) { *sortie++ = Nombre(30*p + 17); }
            if (test19.at(p)) { *sortie++ = Nombre(30*p + 19); }
            if (test23.at(p)) { *sortie++ = Nombre(30*p + 23); }
            if (test29.at(p)) { *sortie++ = Nombre(30*p + 29); }
        }
        return sortie;
    }
}
