#include "problemes.h"
#include "arithmetiques.h"

#include <fstream>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(89, "Roman numerals") {
    // For a number written in Roman numerals to be considered valid there are basic rules which must be followed. Even
    // though the rules allow some numbers to be expressed in more than one way there is always a "best" way of writing
    // a particular number.
    //
    // For example, it would appear that there are at least six ways of writing the number sixteen:
    // 
    //      IIIIIIIIIIIIIIII
    //      VIIIIIIIIIII
    //      VVIIIIII
    //      XIIIIII
    //      VVVI
    //      XVI
    //
    // However, according to the rules only XIIIIII and XVI are valid, and the last example is considered to be the most
    // efficient, as it uses the least number of numerals.
    // 
    // The 11K text file, roman.txt (right click and 'Save Link/Target As...'), contains one thousand numbers written in
    // valid, but not necessarily minimal, Roman numerals; see About... Roman Numerals for the definitive rules for this
    // problem.
    // 
    // Find the number of characters saved by writing each of these in their minimal form.
    // 
    // Note: You can assume that all the Roman numerals in the file contain no more than four consecutive identical
    // units.
    std::map<char, nombre> valeur = {{'I', 1},
                                     {'V', 5},
                                     {'X', 10},
                                     {'L', 50},
                                     {'C', 100},
                                     {'D', 500},
                                     {'M', 1000}};
    const std::vector<std::string> unite = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    const std::vector<std::string> dizaine = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const std::vector<std::string> centaine = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const std::vector<std::string> millier = {"", "M", "MM", "MMM", "MMMM", "MMMMM", "MMMMMM", "MMMMMMM", "MMMMMMMM",
                                              "MMMMMMMMM"};

    std::ifstream ifs("data/p089_roman.txt");
    nombre resultat = 0;
    std::string ligne;
    while (ifs >> ligne) {
        nombre n = 0;
        for (auto it = ligne.cbegin(), en = ligne.cend(); it != en; ++it) {
            nombre r = valeur[*it];
            if (std::find_if(it + 1, en, [&r, &valeur](char c) { return valeur[c] > r; }) == en)
                n += r;
            else
                n -= r;
        }

        std::ostringstream oss;
        oss << millier[static_cast<size_t>(n / 1000)];
        n = n % 1000;
        oss << centaine[static_cast<size_t>(n / 100)];
        n = n % 100;
        oss << dizaine[static_cast<size_t>(n / 10)];
        n = n % 10;
        oss << unite[static_cast<size_t>(n)];

        resultat += ligne.size() - oss.str().size();
    }

    return std::to_string(resultat);
}
