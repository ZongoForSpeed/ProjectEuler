#include "problemes.h"
#include "premiers.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(516, "5-smooth totients") {
    // 5-smooth numbers are numbers whose largest prime factor doesn't exceed 5.
    // 5-smooth numbers are also called Hamming numbers.
    // Let S(L) be the sum of the numbers n not exceeding L such that Euler's totient function φ(n) is a Hamming number.
    // S(100)=3728.
    //
    // Find S(10**12). Give your answer modulo 2**32.
    nombre limite = 1'000'000'000'000;
    nombre modulo = 1ull << 32;

    std::vector<nombre> premiersHamming;
    // Recherche des nombres premiers de la forme 2**a * 3**b * 5**c + 1
    for (nombre a = 1; a < limite; a *= 2)
    for (nombre b = a; b < limite; b *= 3)
    for (nombre c = b; c < limite; c *= 5) {
        if (premiers::miller_rabin(c + 1, 25)) {
            premiersHamming.push_back(c + 1);
        }
    }

    std::sort(premiersHamming.begin(), premiersHamming.end());
    // On retire 2, 3, 5 de la liste des nombre premiers
    premiersHamming.erase(premiersHamming.begin(), premiersHamming.begin() + 3);

    std::vector<nombre> facteurs{1};
    // Recherche des nombres de la forme pi * ... * pk (sans exposant)
    for (auto p: premiersHamming) {
        std::vector<nombre> f1;
        for (auto f: facteurs) {
            nombre n = p * f;
            if (n > limite) {
                break;
            }
            f1.push_back(n);
        }

        std::vector<nombre> f2;
        std::merge(facteurs.begin(), facteurs.end(), f1.begin(), f1.end(), std::back_inserter(f2));
        std::swap(f2, facteurs);
    }

    // Recherche de tous les nombre de la forme 2**a * 3**b * 5**c * pi * ... * pk
    nombre resultat = 0;
    for (auto f: facteurs) {
        for (nombre a = f; a < limite + 1; a *= 2)
            for (nombre b = a; b < limite + 1; b *= 3)
                for (nombre c = b; c < limite + 1; c *= 5) {
                    resultat += c;
                    resultat %= modulo;
                }
    }

    resultat %= modulo;
    return std::to_string(resultat);
}
