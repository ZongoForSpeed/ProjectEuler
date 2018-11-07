#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"
#include "multidimension.h"

ENREGISTRER_PROBLEME(341, "Golomb's self-describing sequence")
{
    // The Golomb's self-describing sequence {G(n)} is the only nondecreasing sequence of natural numbers such that n 
    // appears exactly G(n) times in the sequence. The values of G(n) for the first few n are
    //
    //          n   	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	…
    //          G(n)	1	2	2	3	3	4	4	4	5	5	5	6	6	6	6	…
    //
    // You are given that G(10**3) = 86, G(10**6) = 6137.
    // You are also given that ΣG(n**3) = 153506976 for 1 ≤ n < 10**3.
    //
    // Find ΣG(n**3) for 1 ≤ n < 10**6.
    // for G(1) + G(2)+ ... + G(n-1) < k <= G(1) + G(2) + ... + G(n) = somme(n)
    // we have G(k) = n
    const size_t limite = 1'000'000;
    const size_t borne = limite * limite * limite;

    std::vector<size_t> g{0, 1};
    std::vector<size_t> produit{0, 1};
    std::vector<size_t> somme{0, 1};

    for (size_t i = 2;; ++i) {
        g.push_back(1 + g[i - g[g[i - 1]]]);
        somme.push_back(somme[i - 1] + g[i]);
        produit.push_back(produit[i - 1] + i * g[i]);
        if (produit.back() > borne)
            break;
    }    

    // std::cout << "G(10**3) = " << g[1'000] << std::endl;
    // std::cout << "G(10**6) = " << g[1'000'000] << std::endl;
    size_t k = 1;
    size_t resultat = 0;
    for (size_t n = 1; n < limite; ++n) {
        size_t nnn = n*n*n;
        while (produit[k] < nnn) {
            ++k;
        }
        
        auto decalage = arithmetique::plafond(
            (nnn - produit[k - 1]) * (somme[k] - somme[k - 1]), produit[k] - produit[k - 1]);
        // g[nnn] = somme[k - 1] + decalage
        resultat += somme[k - 1] + decalage;
    }

    return std::to_string(resultat);
}
