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

void probleme099()
{
    Timer t("probleme 99");
    // Comparing two numbers written in index form like 211 and 37 is not difficult, as any calculator
    // would confirm that 2^11 = 2048 < 3^7 = 2187.
    //
    // However, confirming that 632382^518061 > 519432^525806 would be much more difficult, as both 
    // numbers contain over three million digits.
    // 
    // Using base_exp.txt (right click and 'Save Link/Target As...'), a 22K text file containing one 
    // thousand lines with a base/exponent pair on each line, determine which line number has the 
    // greatest numerical value.
    // 
    // NOTE: The first two lines in the file represent the numbers in the example given above.
    std::ifstream ifs("data/p099_base_exp.txt");
    nombre resultat = 0;
    nombre numero_ligne = 1;
    std::string ligne;
    long double maximum = 0;
    while (ifs >> ligne)
    {
        std::vector<std::string> v;
        boost::split(v,ligne,boost::is_any_of(","));
        const long double log = std::log(std::stold(v.front())) * std::stold(v.back()); 
        if (log > maximum)
        {
            resultat = numero_ligne;
            maximum = log;
        }
        ++numero_ligne;
    }
    std::cout << "Solution: " << resultat << std::endl;
}
