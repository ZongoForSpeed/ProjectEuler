#include <numeric>
#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "mp_nombre.h"

typedef std::vector<mp_nombre> vecteur;
typedef std::pair<mp_nombre, mp_nombre> paire;

ENREGISTRER_PROBLEME(203, "Squarefree Binomial Coefficients") {
    // The binomial coefficients nCk can be arranged in triangular form, Pascal's triangle, like this:
    //
    //                                              1	
    //                                          1		1	
    //                                      1		2		1	
    //                                  1		3		3		1	
    //                              1		4		6		4		1	
    //                          1		5		10		10		5		1	
    //                      1		6		15		20		15		6		1	
    //                  1		7		21		35		35		21		7		1
    //                                          .........
    // 
    // It can be seen that the first eight rows of Pascal's triangle contain twelve distinct numbers: 
    // 1, 2, 3, 4, 5, 6, 7, 10, 15, 20, 21 and 35.
    //
    // A positive integer n is called squarefree if no square of a prime divides n. Of the twelve distinct numbers in
    // the first eight rows of Pascal's triangle, all except 4 and 20 are squarefree. The sum of the distinct squarefree
    // numbers in the first eight rows is 105.
    //
    // Find the sum of the distinct squarefree numbers in the first 51 rows of Pascal's triangle.
    size_t limite = 50;
    vecteur premiers;
    premiers::crible2<mp_nombre>(limite, std::back_inserter(premiers));

    std::set<mp_nombre> square_free;
    for (unsigned long n = 0; n <= limite; ++n)
        for (unsigned long p = 0; p <= n; ++p) {
            mp_nombre Cnp = mp_nombre::coefficient_binomial(n, p);
            if (!arithmetiques::facteur_carre(Cnp, premiers))
                square_free.insert(Cnp);
        }

    mp_nombre resultat = std::accumulate(square_free.begin(), square_free.end(), mp_nombre(0));
    return resultat.to_string();
}
