#include "Premiers.h"
#include <vector>

namespace premiers
{
    void internal_crible(std::size_t taille, std::vector<bool> & test)
    {
        test.assign(taille + 1, true);
    	test.at(0) = false;
    	test.at(1) = false;
    
    	for (std::size_t p = 2; p * p < taille + 1; ++p)
    	{
    		if (test.at(p))
    		{
    			for (std::size_t k = p * p; k < taille + 1; k += p) test.at(k) = false;
    		}
    	}
    }
}