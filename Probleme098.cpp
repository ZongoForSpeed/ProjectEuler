#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <tuple>

#include <boost/algorithm/string.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

ENREGISTRER_PROBLEME(98)
{
    Timer t("probleme 98");
    // By replacing each of the letters in the word CARE with 1, 2, 9, and 6 respectively, we form 
    // a square number: 1296 = 36². What is remarkable is that, by using the same digital 
    // substitutions, the anagram, RACE, also forms a square number: 9216 = 96². We shall call CARE 
    // (and RACE) a square anagram word pair and specify further that leading zeroes are not permitted,
    // neither may a different letter have the same digital value as another letter.
    //
    // Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly 
    // two-thousand common English words, find all the square anagram word pairs (a palindromic word
    // is NOT considered to be an anagram of itself).
    // 
    // What is the largest square number formed by any member of such a pair?
    // 
    // NOTE: All anagrams formed must be contained in the given text file.
    std::map<nombre, std::set<vecteur>> anagrammes;
    vecteur chiffres = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    do 
    {
        if (chiffres.front() != 0)
        {
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), std::next(chiffres.begin(), 1))))
                anagrammes[1].insert(vecteur(chiffres.begin(), std::next(chiffres.begin(), 1)));
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), std::next(chiffres.begin(), 2))))
                anagrammes[2].insert(vecteur(chiffres.begin(), std::next(chiffres.begin(), 2)));
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), std::next(chiffres.begin(), 3))))
                anagrammes[3].insert(vecteur(chiffres.begin(), std::next(chiffres.begin(), 3)));
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), std::next(chiffres.begin(), 4))))
                anagrammes[4].insert(vecteur(chiffres.begin(), std::next(chiffres.begin(), 4)));
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), std::next(chiffres.begin(), 5))))
                anagrammes[5].insert(vecteur(chiffres.begin(), std::next(chiffres.begin(), 5)));
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), std::next(chiffres.begin(), 6))))
                anagrammes[6].insert(vecteur(chiffres.begin(), std::next(chiffres.begin(), 6)));
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), std::next(chiffres.begin(), 7))))
                anagrammes[7].insert(vecteur(chiffres.begin(), std::next(chiffres.begin(), 7)));
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), std::next(chiffres.begin(), 8))))
                anagrammes[8].insert(vecteur(chiffres.begin(), std::next(chiffres.begin(), 8)));
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), std::next(chiffres.begin(), 9))))
                anagrammes[9].insert(vecteur(chiffres.begin(), std::next(chiffres.begin(), 9)));
            if (polygonal::est_carre(chiffres::conversion_nombre<nombre>(chiffres.begin(), chiffres.end())))
                anagrammes[10].insert(chiffres);
        }
    } 
    while(std::next_permutation(chiffres.begin(), chiffres.end()));
    
    std::vector<std::string> mots;
    std::ifstream ifs("data/p098_words.txt");
    std::string ligne;
    while (ifs >> ligne)
    {
        std::vector<std::string> v;
        boost::split(v,ligne,boost::is_any_of(",\""));
        mots.insert(mots.end(), v.begin(), v.end());
    }
    
    nombre resultat = 0;
    for (auto it1 = mots.begin(), en = mots.end(); it1 != en; ++it1)
    {
        const auto & mot1 = *it1;
        for (auto it2 = std::next(it1); it2 != en; ++it2)
        {
            const auto & mot2 = *it2;
            if (mot1.size() == mot2.size() && is_permutation(mot1.begin(), mot1.end(), mot2.begin()))
            {
                for (const auto & anagramme: anagrammes[mot1.size()])
                {
                    std::map<char, nombre> decode;
                    for (nombre n = 0; n < mot1.size(); ++n)
                        decode[mot1.at(n)] = anagramme.at(n);
                    
                    vecteur v;
                    for (char c: mot2)
                        v.push_back(decode[c]);
                        
                    if (v.front() != 0)
                    {
                        nombre n1 = chiffres::conversion_nombre<nombre>(anagramme.begin(), anagramme.end());
                        nombre n2 = chiffres::conversion_nombre<nombre>(v.begin(), v.end());
                        if (polygonal::est_carre(n2))
                        {
                            // std::cout << "(" << mot1 << ", " << mot2 << ") ==>" << n1 << " " <<  n2 << std::endl;
                            resultat = std::max(n1, resultat);
                            resultat = std::max(n2, resultat);
                        }
                    }
                }
            }
        }
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
