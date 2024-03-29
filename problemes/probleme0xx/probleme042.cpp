#include "problemes.h"
#include "arithmetique.h"

#include <fstream>
#include <boost/algorithm/string.hpp>
#include <numeric>

#include <execution>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(42, "Coded triangle numbers") {
    // The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:
    //
    //                                      1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
    //
    // By converting each letter in a word to a number corresponding to its alphabetical position and adding these values
    // we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle
    // number then we shall call the word a triangle word.
    //
    // Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?
    std::ifstream ifs("data/p042_words.txt");
    std::string entree;
    ifs >> entree;
    std::vector<std::string> names;
    boost::split(names, entree, boost::is_any_of(","));

    std::set<nombre> triangle;
    for (nombre n = 1; n < 50; ++n)
        triangle.insert(n * (n + 1) / 2);

    auto conversion = [] (char c) -> nombre {
        if (c != '"')
            return 1 + static_cast<nombre>(c - 'A');
        return 0;
    };

    nombre resultat = 0;
    for (const auto &name: names) {
        nombre score = std::transform_reduce(std::execution::par, name.begin(), name.end(),
                                             0ULL,std::plus<nombre>{},conversion);
        if (triangle.find(score) != triangle.end())
            ++resultat;
    }
    return std::to_string(resultat);
}
