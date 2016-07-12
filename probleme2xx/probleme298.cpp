#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"
#include "timer.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include <boost/bimap.hpp>
#include <boost/foreach.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    class Etat
    {
    public:
        Etat() {}
        
        std::deque<unsigned short> memoire_larry;
        std::deque<unsigned short> memoire_robin;
        
        short suivant(const unsigned short tirage)
        {
            short score = 0;
            // Larry's strategy is to remove the number that hasn't been called 
            // in the longest time.
            auto it = std::find(memoire_larry.begin(), memoire_larry.end(), tirage);
            if (it != memoire_larry.end())
            {
                ++score;
                memoire_larry.erase(it);
                memoire_larry.push_front(tirage);
            }
            else
            {
                memoire_larry.push_front(tirage);
                if (memoire_larry.size() > 5)
                    memoire_larry.pop_back();
            }
            
            // Robin's strategy is to remove the number that's been in the memory 
            // the longest time.
            it = std::find(memoire_robin.begin(), memoire_robin.end(), tirage);
            if (it != memoire_robin.end())
            {
                --score;
            }
            else
            {
                memoire_robin.push_front(tirage);
                if (memoire_robin.size() > 5)
                    memoire_robin.pop_back();
            }
            
            std::map<unsigned short, unsigned short> echange;
            unsigned short compteur = 0;
            for (auto & n: memoire_robin)
            {
                if (echange.find(n) == echange.end())
                    echange[n] = ++compteur;
                
                n = echange[n];
            }
            
            for (auto & n: memoire_larry)
            {
                if (echange.find(n) == echange.end())
                    echange[n] = ++compteur;
                
                n = echange[n];
            }
            
            return score;
        }
        
        bool operator<(const Etat & e) const
        {
            if (memoire_larry != e.memoire_larry)
                return memoire_larry < e.memoire_larry;
                
            return memoire_robin < e.memoire_robin;
        }
    };
    
    // std::ostream & operator<<(std::ostream & os, const Etat & e)
    // {
    //     os << "Larry " << e.memoire_larry << ", Robin " << e.memoire_robin;
    //     return os;
    // }
}

ENREGISTRER_PROBLEME(298, "Selective Amnesia")
{
    // Larry and Robin play a memory game involving of a sequence of random 
    // numbers between 1 and 10, inclusive, that are called out one at a time. 
    // Each player can remember up to 5 previous numbers. When the called number
    // is in a player's memory, that player is awarded a point. If it's not, the 
    // player adds the called number to his memory, removing another number if 
    // his memory is full.
    //  
    // Both players start with empty memories. Both players always add new missed
    // numbers to their memory but use a different strategy in deciding which 
    // number to remove:
    //      - Larry's strategy is to remove the number that hasn't been called 
    //        in the longest time.
    //      - Robin's strategy is to remove the number that's been in the memory 
    //        the longest time.
    //
    // Example game:
    // 
    //      Turn	Called 	    Larry's Larry's     Robin's Robin's
    //              number      memory  score       memory  score
    //         1	     1	          1	      0	          1	      0
    //         2	     2	        1,2	      0	        1,2	      0
    //         3	     4	      1,2,4	      0	      1,2,4	      0
    //         4	     6	    1,2,4,6	      0	    1,2,4,6	      0
    //         5	     1	    1,2,4,6	      1	    1,2,4,6	      1
    //         6	     8	  1,2,4,6,8	      1	  1,2,4,6,8	      1
    //         7	    10	 1,4,6,8,10	      1	 2,4,6,8,10	      1
    //         8	     2	 1,2,6,8,10	      1	 2,4,6,8,10	      2 
    //         9	     4	 1,2,4,8,10	      1	 2,4,6,8,10	      3
    //        10	     1	 1,2,4,8,10	      2	 1,4,6,8,10	      3
    //
    // Denoting Larry's score by L and Robin's score by R, what is the expected 
    // value of |L-R| after 50 turns? Give your answer rounded to eight decimal 
    // places using the format x.xxxxxxxx.
    typedef boost::bimap<Etat, unsigned short> bimap_t;
    typedef std::tuple<unsigned short/*etat*/, 
                       short/*score*/, 
                       long double/*probabilite*/> tuple_t;

    std::map<unsigned short/*etat*/, std::deque<tuple_t>> graphe;

    unsigned short compteur = 0;
    bimap_t relation;
    relation.insert(bimap_t::value_type(Etat(), compteur++));
    
    std::set<Etat> a_voir { Etat() };
    while (!a_voir.empty())
    {
        const auto it = a_voir.begin();
        const unsigned short origine = relation.left.find(*it)->second;
        
        std::deque<tuple_t> suivants;
        
        for (unsigned short tirage = 0; tirage < 10; ++tirage)
        {
            Etat nouvel_etat = *it;
            short score = nouvel_etat.suivant(tirage);
            
            unsigned short suivant = 0;
            
            auto it2 = relation.left.find(nouvel_etat);
            
            if (it2 == relation.left.end())
            {
                suivant = compteur;
                relation.insert(bimap_t::value_type(nouvel_etat, compteur++));
                a_voir.insert(nouvel_etat);
            }
            else
            {
                suivant = it2->second;
            }
            
            bool found = false;
            for (tuple_t & t: suivants)
            {
                if (std::get<0>(t) == suivant && std::get<1>(t) == score)
                {
                    std::get<2>(t) += 0.1;
                    found = true;
                }
            }
            
            if (!found)
            {
                suivants.push_back(std::make_tuple(suivant, score, 0.1));
            }
        }
        
        graphe.insert(std::make_pair(origine, suivants));
        a_voir.erase(it);
    }
    
    std::deque<std::map<short/*score*/, long double/*probabilite*/>> dp(compteur);
    dp.front().insert(std::make_pair(0, 1.0));
    
    for (unsigned short tour = 0; tour < 50; ++tour)
    {
        std::deque<std::map<short/*score*/, long double/*probabilite*/>> suivant(compteur);
        for (unsigned short etat = 0; etat < compteur; ++etat)
        {
            const auto & etats = graphe[etat];
            for (auto p: dp[etat])
            {
                const short score = p.first;
                const long double probabilite = p.second;
                for (const auto & t: etats)
                {
                    suivant[std::get<0>(t)][score + std::get<1>(t)] += std::get<2>(t) * probabilite;
                }
            }
        }
        std::swap(suivant, dp);
    }
    
    long double resultat = 0.0;
    for (const auto & p: dp)
    for (const auto & etat: p)
    {
        resultat += std::abs(etat.first) * etat.second;
    }
    
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Solution: " << resultat << std::endl;
}
