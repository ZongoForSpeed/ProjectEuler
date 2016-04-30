#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;

typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(238, "Infinite string tour")
{
    // Create a sequence of numbers using the "Blum Blum Shub" pseudo-random number generator:
    //
    //              s0      =	14025256
    //              sn+1	=	sn² mod 20300713
    //
    // Concatenate these numbers  s0s1s2… to create a string w of infinite length.
    // Then, w = 14025256741014958470038053646…
    //
    // For a positive integer k, if no substring of w exists with a sum of digits equal to k, p(k)
    // is defined to be zero. If at least one substring of w exists with a sum of digits equal to k,
    // we define p(k) = z, where z is the starting position of the earliest such substring.
    //
    // For instance:
    //
    // The substrings 1, 14, 1402, … 
    // with respective sums of digits equal to 1, 5, 7, …
    // start at position 1, hence p(1) = p(5) = p(7) = … = 1.
    //
    // The substrings 4, 402, 4025, …
    // with respective sums of digits equal to 4, 6, 11, …
    // start at position 2, hence p(4) = p(6) = p(11) = … = 2.
    //
    // The substrings 02, 0252, …
    // with respective sums of digits equal to 2, 9, …
    // start at position 3, hence p(2) = p(9) = … = 3.
    // 
    // Note that substring 025 starting at position 3, has a sum of digits equal to 7, but there was 
    // an earlier substring (starting at position 1) with a sum of digits equal to 7, so p(7) = 1, not 3.
    //
    // We can verify that, for 0 < k ≤ 10^3, ∑ p(k) = 4742.
    //
    // Find ∑ p(k), for 0 < k ≤ 2·10^15.
    const nombre s0 = 14025256;
    const nombre modulo = 20300713;
    const nombre limite = 2e15;
    
    nombre sn = s0;
    std::vector<unsigned short> w;
    do
    {
        auto chiffres = chiffres::extraire_chiffres(sn);
        w.insert(w.end(), chiffres.begin(), chiffres.end());
        sn = (sn * sn) % modulo;
    }
    while (sn != s0);

    const nombre somme = std::accumulate(w.begin(), w.end(), 0ULL);
    
    vecteur p(somme, 0);
    nombre compteur = 0;
    for (size_t i = 0; i < w.size() && compteur <= somme; ++i)
    {
        for (size_t j = 0, as = w[i]; j < w.size() && compteur <= somme; as += w[ (++j + i) % w.size() ])
        {
            if (p[as] != 0)
                continue;
            p[as] = i + 1;
            ++compteur;
        }
    }
    
    nombre resultat = limite / somme;
    for (nombre x = 1; x < somme; ++x)
        resultat += p[x] * (1 + ( (limite - x) / somme ));

    std::cout << "Solution: " << resultat << std::endl;
}
