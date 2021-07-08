#include "problemes.h"
#include "numerique.h"
#include "premiers.h"
#include "timer.h"

namespace {
    size_t A(size_t k, size_t n, size_t modulo) {
        std::vector<size_t> factoriels(k + 1, 0);
        size_t f = factoriels[0] = 1;
        for (size_t i = 1; i <= k; ++i){
            factoriels[i] = f = f * i % modulo;
        }
        size_t P = n / k; // nombre de périodes
        size_t deux_P = puissance::puissance_modulaire<size_t>(2, P, modulo);
        size_t deux_2P = deux_P * deux_P % modulo;
        size_t deux_Px = (k & 1) ? deux_P : 1;
        size_t resultat = 0;
        for (size_t x = k & 1; x <= k; x += 2) { // nombre de colonnes avec somme = 1
            size_t y = (k - x) / 2;              // nombre de colonnes avec somme = 2
            size_t denominateur = factoriels[y] * factoriels[y] % modulo * factoriels[x] % modulo;
            size_t b = factoriels[k] * puissance::puissance_modulaire(denominateur, modulo - 2, modulo) % modulo;
            resultat = (resultat + b * deux_Px) % modulo;
            deux_Px = deux_Px * deux_2P % modulo;
        }
        return resultat;
    }
}

ENREGISTRER_PROBLEME(743, "Window into a Matrix") {
    // A window into a matrix is a contiguous sub matrix.
    //
    // Consider a 2 * n matrix where every entry is either 0 or 1.
    //
    // Let A(k,n) be the total number of these matrices such that the sum of the entries in every
    // 2 * k window is k.
    //
    // You are given that A(3,9) = 560 and A(4,20) = 1060870.
    //
    // Find A(10^8,10^{16}). Give your answer modulo 1,000,000,007.
    std::cout << "A(3,9) = " << A(3, 9, 1'000'000'007) << std::endl;
    std::cout << "A(4,20) = " << A(4, 20, 1'000'000'007) << std::endl;

    size_t resultat = A(100'000'000, 10'000'000'000'000'000, 1'000'000'007);
    std::cout << "A(10^8,10^{16}) = " << resultat << std::endl;

    return std::to_string(resultat);
}
