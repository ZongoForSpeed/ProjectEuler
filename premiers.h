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
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible235(std::size_t taille, OutputIterator sortie)
    {
        std::size_t taille_crible = taille / 30 + 1;
        std::vector<bool> test1, test7, test11, test13, test17, test19, test23, test29;
        internal_crible235(taille_crible, test1, test7, test11, test13, test17, test19, test23, test29);
        *sortie = 2;
        ++sortie;
        *sortie = 3;
        ++sortie;
        *sortie = 5;
        ++sortie;
        for (std::size_t p = 0; p < taille_crible; ++p)
        {
            if (test1.at(p)) { *sortie = Nombre(30*p + 1); ++sortie;}
            if (test7.at(p)) { *sortie = Nombre(30*p + 7); ++sortie; }
            if (test11.at(p)) { *sortie = Nombre(30*p + 11); ++sortie; }
            if (test13.at(p)) { *sortie = Nombre(30*p + 13); ++sortie; }
            if (test17.at(p)) { *sortie = Nombre(30*p + 17); ++sortie; }
            if (test19.at(p)) { *sortie = Nombre(30*p + 19); ++sortie; }
            if (test23.at(p)) { *sortie = Nombre(30*p + 23); ++sortie; }
            if (test29.at(p)) { *sortie = Nombre(30*p + 29); ++sortie; }
        }
        return sortie;
    }
    void testCrible();
}
