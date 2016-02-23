#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <tuple>

#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int nombre;
typedef std::vector<nombre> vecteur;

namespace
{
	bool est_vide (const std::vector<std::string> & keys)
    {
        for (const auto & key: keys)
        {
            if (!key.empty()) return false;
        }
        
        return true;
    }
    
    char minimum (const std::vector<std::string> & keys)
    {
        std::map<char, size_t> maximum;
        for (auto & key: keys)
        {
            for (size_t n = 0; n < key.size(); ++n)
            {
                const char c = key[n];
                auto it = maximum.find(c);
                if (it != maximum.end())
                    it->second = std::max(n, it->second);
                else
                    maximum[c] = n;
            }
        }
        
        for (const auto & p: maximum)
        {
            if (p.second == 0)
                return p.first;
        }
        
        return ' ';
    }
}

ENREGISTRER_PROBLEME(79, "Passcode derivation")
{
    Timer t("probleme 79");
    // A common security method used for online banking is to ask the user for three random characters 
    // from a passcode. For example, if the passcode was 531278, they may ask for the 2nd, 3rd, and 
    // 5th characters; the expected reply would be: 317.
    //
    // The text file, keylog.txt, contains fifty successful login attempts.
    // 
    // Given that the three characters are always asked for in order, analyse the file so as to 
    // determine the shortest possible secret passcode of unknown length.
    std::ifstream ifs("data/p079_keylog.txt");
    
    std::vector<std::string> keys;
    std::string key;
    while (ifs >> key)
    {
        keys.push_back(key);
    }
    
    std::string mot_de_passe;
    while (!est_vide(keys))
    {
        const char c = minimum(keys);
        mot_de_passe.push_back(c);
        for (auto & k: keys)
        {
            if (!k.empty() && k[0] == c)
                k = k.substr(1);
        }
    }
    
    std::cout << "Solution: " << mot_de_passe << std::endl;
}
