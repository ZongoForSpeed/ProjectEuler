#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<std::string, unsigned short> paire;
typedef std::vector<paire> ensemble;

namespace
{
    bool comparer(const paire & p1, const paire & p2)
    {
        if (p1.second != p2.second)
            return p1.second < p2.second;
        return p1.first < p2.first;
    }
    
    template<typename Iterator>
    bool cherche_solution(Iterator debut, Iterator fin, std::vector<std::set<char>> & solutions)
    {
        if (debut == fin)
        {
            for (auto s: solutions)
                if (s.size() != 1)
                    return false;
                    
            return true;
        }
        
        for (auto s: solutions) if (s.size() == 0) return false;
        
        auto essai = *debut;
        
        std::set<size_t> test;
        for (size_t n = 0; n < solutions.size(); ++n)
            test.insert(n);

        for (size_t n = 0; n < solutions.size(); ++n)
        {
            auto s = solutions[n];
            if (solutions[n].size() == 1)
            {
                if (*solutions[n].begin() == essai.first[n])
                {
                    essai.second--;
                    test.erase(n);
                }
            }
            if (s.find(essai.first[n]) == s.end())
            {
                test.erase(n);
            }
        }   
        
        if (test.size() < essai.second)
            return false;
        
        if (essai.second == 0)
        {
            for (size_t n: test)
            {
                solutions[n].erase(essai.first[n]);
            }
            
            return cherche_solution(++debut, fin, solutions);
        }
        else
        {
            std::vector<bool> combinaison(test.size(), true);
            for (size_t n = 0; n < essai.second; ++n)
                combinaison.at(n) = false;
            
            do 
            {
                auto s = solutions;
                bool suivant = false;
                size_t position = 0;
                for (size_t n: test)
                {
                    if (combinaison[position])
                        s[n].erase(essai.first[n]);
                    else if (s[n].find(essai.first[n]) == s[n].end())
                    {
                        suivant = true;
                        break;
                    }
                    else
                        s[n] = { essai.first[n] };
                
                    ++position;
                }
                if (suivant)
                    continue;
                
                if (cherche_solution(std::next(debut), fin, s))
                {
                    std::swap(s, solutions);
                    return true;
                }
            }
            while(std::next_permutation(combinaison.begin(), combinaison.end()));
            return false;
        }
    }

}

ENREGISTRER_PROBLEME(185, "Number Mind")
{
    Timer timer("probleme 185");
    // The game Number Mind is a variant of the well known game Master Mind.
    //
    // Instead of coloured pegs, you have to guess a secret sequence of digits. After each guess you're only told in how many places you've guessed the correct digit. So, if the sequence was 1234 and you guessed 2036, you'd be told that you have one correct digit; however, you would NOT be told that you also have another digit in the wrong place.
    //
    // For instance, given the following guesses for a 5-digit secret sequence,
    //
    //              90342 ;2 correct
    //              70794 ;0 correct
    //              39458 ;2 correct
    //              34109 ;1 correct
    //              51545 ;2 correct
    //              12531 ;1 correct
    //
    // The correct sequence 39542 is unique.
    //
    // Based on the following guesses,
    //
    //              5616185650518293 ;2 correct
    //              3847439647293047 ;1 correct
    //              5855462940810587 ;3 correct
    //              9742855507068353 ;3 correct
    //              4296849643607543 ;3 correct
    //              3174248439465858 ;1 correct
    //              4513559094146117 ;2 correct
    //              7890971548908067 ;3 correct
    //              8157356344118483 ;1 correct
    //              2615250744386899 ;2 correct
    //              8690095851526254 ;3 correct
    //              6375711915077050 ;1 correct
    //              6913859173121360 ;1 correct
    //              6442889055042768 ;2 correct
    //              2321386104303845 ;0 correct
    //              2326509471271448 ;2 correct
    //              5251583379644322 ;2 correct
    //              1748270476758276 ;3 correct
    //              4895722652190306 ;1 correct
    //              3041631117224635 ;3 correct
    //              1841236454324589 ;3 correct
    //              2659862637316867 ;2 correct
    //
    // Find the unique 16-digit secret sequence.
    
    // std::ifstream ifs("data/p185_example.txt");
    std::ifstream ifs("data/p185_number_mind.txt");
    ensemble essais;
    
    size_t taille = 0;
    std::string pattern, correct, ignore;
    while (ifs >> pattern >> correct >> ignore)
    {
        taille = pattern.size();
        essais.push_back(std::make_pair(pattern, correct[1] - '0'));
    }
    
    std::set<char> chiffres { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::vector<std::set<char>> solutions;
    for (size_t n = 0; n < taille; ++n)
        solutions.push_back(chiffres);
    
    cherche_solution(essais.begin(), essais.end(), solutions);
    
    std::ostringstream oss;
    for (auto s: solutions)
        oss << *s.begin();
        
    std::cout << "Solution: " << oss.str() << std::endl;
}
