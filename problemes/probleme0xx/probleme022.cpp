#include "problemes.h"
#include "arithmetique.h"

#include <fstream>
#include <execution>

#include <boost/algorithm/string.hpp>
#include <numeric>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(22, "Names scores") {
    // Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing 
    // over five-thousand first names, begin by sorting it into alphabetical order. 
    // Then working out the alphabetical value for each name, multiply this value by its alphabetical 
    // position in the list to obtain a name score.
    // 
    // For example, when the list is sorted into alphabetical order, COLIN, which is worth 
    // 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a 
    // score of 938 × 53 = 49714.
    // 
    // What is the total of all the name scores in the file?    
    std::ifstream ifs("data/p022_names.txt");
    std::string entree;
    ifs >> entree;
    std::vector<std::string> names;
    boost::split(names, entree, boost::is_any_of(","));
    std::sort(names.begin(), names.end());
    nombre compteur = 0;
    nombre resultat = 0;

    auto conversion = [] (char c) -> nombre {
        if (c != '"')
            return 1 + static_cast<nombre>(c - 'A');
        return 0;
    };

    for (const auto &name: names) {
        nombre score = std::transform_reduce(std::execution::par, name.begin(), name.end(),
                                       0ULL, std::plus<nombre>{}, conversion);
        resultat += (++compteur * score);
    }
    return std::to_string(resultat);
}
