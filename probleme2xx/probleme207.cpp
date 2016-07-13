#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(207, "Integer partition equations")
{
    // For some positive integers k, there exists an integer partition of the form 4^t = 2^t + k,
    // where 4t, 2t, and k are all positive integers and t is a real number.
    //
    // The first two such partitions are 4^1 = 2^1 + 2 and 4^1.5849625... = 2^1.5849625... + 6.
    //
    // Partitions where t is also an integer are called perfect.
    // For any m ≥ 1 let P(m) be the proportion of such partitions that are perfect with k ≤ m.
    // Thus P(6) = 1/2.
    //
    // In the following table are listed some values of P(m)
    //
    //   P(5) = 1/1
    //   P(10) = 1/2
    //   P(15) = 2/3
    //   P(20) = 1/2
    //   P(25) = 1/2
    //   P(30) = 2/5
    //   ...
    //   P(180) = 1/4
    //   P(185) = 3/13
    //
    // Find the smallest m for which P(m) < 1/12345
    nombre limite = 12345;
    // P(x*(x-1)) = floor(log_2(x)) / (x-1)
    // ==> k / (2^k - 1) < 1 / 12345
    nombre resultat = 0;
    for (nombre k = 0, x = 1;; ++k, x*=2)
    {
        if (limite * k < x - 1)
        {
            --k;
            resultat = (limite*k + 2)*(limite*k + 1);
            break;
        }
    }

    return std::to_string(resultat);
}
