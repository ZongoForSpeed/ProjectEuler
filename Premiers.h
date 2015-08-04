#pragma once
#include <vector>
#include <set>
#include <list>

namespace premiers
{
    void internal_crible(std::size_t taille, std::vector<bool> & test);
    
    template<typename N>
    void crible(std::size_t taille, std::vector<N> & premiers)
    {
    	std::vector<bool> test;
    	internal_crible(taille, test);
    	
    	for (std::size_t p = 0; p < taille + 1; ++p)
    	{
    		if (test.at(p)) premiers.push_back(p);
    	}
    }
    
    template<typename N>
    void crible(std::size_t taille, std::list<N> & premiers)
    {
    	std::vector<bool> test;
    	internal_crible(taille, test);
    	
    	for (std::size_t p = 0; p < taille + 1; ++p)
    	{
    		if (test.at(p)) premiers.push_back(p);
    	}
    }

    template<typename N>
    void crible(std::size_t taille, std::set<N> & premiers)
    {
    	std::vector<bool> test;
    	internal_crible(taille, test);
    	
    	for (std::size_t p = 0; p < taille + 1; ++p)
    	{
    		if (test.at(p)) premiers.insert(p);
    	}
    }    
}
