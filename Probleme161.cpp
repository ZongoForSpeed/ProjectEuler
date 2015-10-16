#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <map>
#include <set>

#include <boost/multiprecision/gmp.hpp>
#include <boost/optional.hpp>

typedef boost::multiprecision::mpz_int nombre;
// typedef unsigned long long nombre;

typedef std::vector<std::vector<bool>> matrice;
typedef std::pair<size_t, size_t> paire;

namespace
{
    boost::optional<paire> libre(const matrice & m)
    {
        for (size_t i = 0; i < m.size(); ++i)
        {
            const auto & ligne = m[i];
            for (size_t j = 0; j < ligne.size(); ++j)
            {
                if (ligne[j]) return std::make_pair(i, j);
            }
        }
        
        return boost::none;
    }
    
    bool testForme1(const matrice & m, const size_t i, const size_t j)
    {
        if (m.front().size() < j + 3)
            return false;
            
        return m[i][j] && m[i][j+1] && m[i][j+2];
    }
    
    bool testForme2(const matrice & m, const size_t i, const size_t j)
    {
        if (m.size() < i + 3)
            return false;
            
        return m[i][j] && m[i+1][j] && m[i+2][j];
    }
    
    bool testForme3(const matrice & m, const size_t i, const size_t j)
    {
        if (m.size() < i + 2 || m.front().size() < j + 2)
            return false;
            
        return m[i][j] && m[i+1][j] && m[i][j+1];
    }
    
    bool testForme4(const matrice & m, const size_t i, const size_t j)
    {
        if (m.size() < i + 2 || m.front().size() < j + 2)
            return false;
            
        return m[i][j] && m[i+1][j] && m[i+1][j+1];
    }
    
    bool testForme5(const matrice & m, const size_t i, const size_t j)
    {
        if (m.size() < i + 2 || m.front().size() < j + 2)
            return false;
            
        return m[i][j] && m[i][j+1] && m[i+1][j+1];
    }
    
    bool testForme6(const matrice & m, const size_t i, const size_t j)
    {
        if (m.size() < i + 2 || j == 0)
            return false;
            
        return m[i][j] && m[i+1][j] && m[i+1][j-1];
    }
    
    nombre combinaison(const matrice & m)
    {
        static std::map<matrice, nombre> cache;
        auto it = cache.find(m);
        if (it != cache.end())
            return it->second;
            
        nombre resultat = 0;    
        
        if (auto p = libre(m))
        {
            size_t i = p->first;
            size_t j = p->second;
            
            if (testForme1(m, i, j))
            {
                matrice mm = m; 
                mm[i][j] = false;
                mm[i][j+1] = false;
                mm[i][j+2] = false;
                resultat += combinaison(mm);
            }
            
            if (testForme2(m, i, j))
            {
                matrice mm = m; 
                mm[i][j] = false;
                mm[i+1][j] = false;
                mm[i+2][j] = false;
                resultat += combinaison(mm);
            }
            
            if (testForme3(m, i, j))
            {
                matrice mm = m; 
                mm[i][j] = false;
                mm[i+1][j] = false;
                mm[i][j+1] = false;
                resultat += combinaison(mm);
            }
            
            if (testForme4(m, i, j))
            {
                matrice mm = m;    
                mm[i][j] = false;
                mm[i+1][j] = false;
                mm[i+1][j+1] = false;
                resultat += combinaison(mm);
            }
            
            if (testForme5(m, i, j))
            {
                matrice mm = m; 
                mm[i][j] = false;
                mm[i][j+1] = false;
                mm[i+1][j+1] = false;
                resultat += combinaison(mm);
            }
            
            if (testForme6(m, i, j))
            {
                matrice mm = m; 
                mm[i][j] = false;
                mm[i+1][j] = false;
                mm[i+1][j-1] = false;
                resultat += combinaison(mm);
            }
        }
        else
            resultat = 1;
        
        cache[m] = resultat;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(161, "Triominoes")
{
    Timer timer("probleme 161");
	// A triomino is a shape consisting of three squares joined via the edges. There are two basic 
	// forms:
    //
    //              XXX     XX
    //                      X
    //
    // If all possible orientations are taken into account there are six:
    //
    //           X  X        X
    //      XXX  X  XX  XX  XX  XX
    //           X      X        X
    //
    // Any n by m grid for which nxm is divisible by 3 can be tiled with triominoes.
    // If we consider tilings that can be obtained by reflection or rotation from another tiling as 
    // different there are 41 ways a 2 by 9 grid can be tiled with triominoes:
    //
    // In how many ways can a 9 by 12 grid be tiled in this way by triominoes?
    matrice m (9, std::vector<bool>(12, true));
    nombre resultat = combinaison(m);
    std::cout << "Solution: " << resultat << std::endl;
}
