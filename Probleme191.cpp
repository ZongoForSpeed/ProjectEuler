#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    nombre sequence(nombre n, nombre absence, bool retard)
    {
        if (n == 0)
            return 1;
            
        static std::map<std::tuple<nombre, nombre, bool>, nombre> cache;
        auto it = cache.find(std::make_tuple(n, absence, retard));
        if (it != cache.end())
            return it->second;
            
        nombre resultat = sequence(n - 1, 0, retard);
        if (!retard)
            resultat += sequence(n - 1, 0, true);
            
        if (absence < 2)
            resultat += sequence(n - 1, absence + 1, retard);
            
        cache[std::make_tuple(n, absence, retard)] = resultat;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(191, "Prize Strings")
{
    Timer timer("probleme 191");
    // A particular school offers cash rewards to children with good attendance and punctuality. 
    // If they are absent for three consecutive days or late on more than one occasion then they 
    // forfeit their prize.
    //
    // During an n-day period a trinary string is formed for each child consisting of L's (late), 
    // O's (on time), and A's (absent).
    //
    // Although there are eighty-one trinary strings for a 4-day period that can be formed, exactly 
    // forty-three strings would lead to a prize:
    //
    //       OOOO OOOA OOOL OOAO OOAA OOAL OOLO OOLA OAOO OAOA
    //       OAOL OAAO OAAL OALO OALA OLOO OLOA OLAO OLAA AOOO
    //       AOOA AOOL AOAO AOAA AOAL AOLO AOLA AAOO AAOA AAOL
    //       AALO AALA ALOO ALOA ALAO ALAA LOOO LOOA LOAO LOAA
    //       LAOO LAOA LAAO
    //
    // How many "prize" strings exist over a 30-day period?
    nombre resultat = sequence(30, 0, false);
    
    std::cout << "Solution: " << resultat << std::endl;
}
